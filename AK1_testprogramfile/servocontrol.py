import serial
import tkinter as tk

# 請將此改為你實際的 Arduino 序列埠
SERIAL_PORT = 'COM7'
BAUD_RATE = 9600

# 初始化序列連線
try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
except Exception as e:
    print(f"Error opening serial port {SERIAL_PORT}: {e}")
    arduino = None

def send_servo_command(channel, angle):
    """將 (channel, angle) 透過 Serial 傳給 Arduino"""
    if arduino is None:
        print("Arduino serial port not open.")
        return

    # 角度夾在 0~180，避免意外
    angle = max(0, min(180, angle))

    # 以兩個 byte 表示角度
    high_byte = (angle >> 8) & 0xFF
    low_byte  = angle & 0xFF

    data = bytes([channel, high_byte, low_byte])
    arduino.write(data)

    print(f"Sent -> ch={channel}, angle={angle}")

def create_servo_buttons(channel):
    """替指定的 channel 建立一排按鈕: 0°,45°,90°,135°,180°"""
    frame = tk.Frame(root, pady=5)
    frame.pack()

    label = tk.Label(frame, text=f"Servo CH{channel}")
    label.grid(row=0, column=0, columnspan=5)

    angles = [0, 45, 90, 135, 180]
    for i, angle in enumerate(angles):
        btn = tk.Button(
            frame, 
            text=f"{angle}°", 
            width=6,
            command=lambda ch=channel, ang=angle: send_servo_command(ch, ang)
        )
        btn.grid(row=1, column=i, padx=2)

# 建立主視窗
root = tk.Tk()
root.title("Servo Motor Control (Button Version)")

# 建立前 8 通道 (CH0 ~ CH7)
for i in range(8):
    create_servo_buttons(i)

root.mainloop()
