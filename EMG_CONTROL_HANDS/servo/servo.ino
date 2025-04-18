#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // 預設 0x40

#define SERVOMIN  150  // 對應 0 度
#define SERVOMAX  600  // 對應 180 度

void setup() {
  Serial.begin(9600);

  Serial.println("==== Arduino Setup Start ====");
  Wire.begin();
  Serial.println("I2C Wire.begin() done.");

  pwm.begin();
  pwm.setPWMFreq(50);  // 50 Hz for servos
  Serial.println("PCA9685 init done. Frequency set to 50 Hz.");
  Serial.println("==== Arduino Setup End ====");
}

void loop() {
  // 如果序列緩衝區資料量>=3 才進行讀取
  // [channel (1 byte)] + [angle_high (1 byte)] + [angle_low (1 byte)]
  if (Serial.available() >= 3) {
    int channel     = Serial.read();         
    int angle_high  = Serial.read();     
    int angle_low   = Serial.read();      
    int angle       = (angle_high << 8) | angle_low;

    // Debug: 印出接收到的資料
    Serial.print("[DEBUG] Received channel=");
    Serial.print(channel);
    Serial.print(", angle=");
    Serial.println(angle);

    if (channel >= 0 && channel < 16) {  
      // 避免超出 PCA9685 16 通道範圍，這裡設置成 0~15
      int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(channel, 0, pulse);

      // Debug: 印出實際傳送的pulse
      Serial.print("[DEBUG] PWM channel=");
      Serial.print(channel);
      Serial.print(" => pulse=");
      Serial.println(pulse);
    } else {
      // channel 非法，丟棄
      Serial.println("[ERROR] Channel out of range (0~15).");
    }
  }
}
