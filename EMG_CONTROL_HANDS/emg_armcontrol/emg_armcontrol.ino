#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PWM 控制設定
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#define SERVOMIN  150
#define SERVOMAX  600
#define SAMPLE_RATE 500
#define INPUT_PIN A0

// EMG 判斷門檻
#define EMG_HIGH_THRESHOLD 100
#define EMG_LOW_THRESHOLD 50
#define TARGET_ANGLE_HIGH 135
#define TARGET_ANGLE_LOW 0

// 控制狀態
int current_angle = 0;
int target_angle = 0;
unsigned long last_high_time = 0;
bool waiting_to_reset = false;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);

  Serial.println("System Init...");
  
  // 所有馬達初始回到 0 度
  for (int ch = 0; ch < 16; ch++) {
    setServoAngle(ch, 0);
  }

  delay(1000);
  Serial.println("Ready.");
}

void loop() {
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  static long timer = 0;
  timer -= interval;

  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;

    float sensor_value = analogRead(INPUT_PIN);
    float signal = EMGFilter(sensor_value);

    // 控制邏輯：根據 EMG 決定目標角度
    if (signal > EMG_HIGH_THRESHOLD) {
      target_angle = TARGET_ANGLE_HIGH;
      last_high_time = millis();
      waiting_to_reset = true;
    } else if (signal < EMG_LOW_THRESHOLD && waiting_to_reset) {
      if (millis() - last_high_time >= 1000) {
        target_angle = TARGET_ANGLE_LOW;
        waiting_to_reset = false;
      }
    }

    // 平滑改變角度（每次改變最多 3 度）
    if (current_angle < target_angle) {
      current_angle += 3;
      if (current_angle > target_angle) current_angle = target_angle;
      updateAllServos(current_angle);
    } else if (current_angle > target_angle) {
      current_angle -= 3;
      if (current_angle < target_angle) current_angle = target_angle;
      updateAllServos(current_angle);
    }
  }
}

// === Servo 控制 ===
void setServoAngle(int channel, int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(channel, 0, pulse);
}

void updateAllServos(int angle) {
  for (int ch = 0; ch < 8; ch++) {
    setServoAngle(ch, angle);
  }
}

// === EMG 濾波器 ===
float EMGFilter(float input)
{
  float output = input;
  {
    static float z1, z2;
    float x = output - 0.05159732 * z1 - 0.36347401 * z2;
    output = 0.01856301 * x + 0.03712602 * z1 + 0.01856301 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2;
    float x = output - -0.53945795 * z1 - 0.39764934 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2;
    float x = output - 0.47319594 * z1 - 0.70744137 * z2;
    output = 1.00000000 * x + 2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2;
    float x = output - -1.00211112 * z1 - 0.74520226 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}
