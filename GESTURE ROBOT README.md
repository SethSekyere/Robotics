📌 Overview
This project demonstrates a gesture-controlled robot using an MPU6050 accelerometer and gyroscope sensor along with nRF24L01 wireless communication modules. 
The transmitter detects hand gestures and sends movement commands to the receiver, which controls the robot's motors.

🛠️ Features
✅ Wireless control via hand gestures
✅ Smooth motor movement using PWM
✅ Real-time accelerometer data transmission
✅ Bidirectional motion (Forward, Backward, Left, Right, Stop)


📜 Components Required
Electronics:
Arduino Uno/Nano (x2) – One for transmitter, one for receiver
MPU6050 Accelerometer & Gyroscope
nRF24L01 Wireless Module (x2)
L298N Motor Driver (or any H-Bridge module)
DC Motors & Wheels
Li-Po Battery / Power Source




**First install required libraries in Libraries.ino**






**Step 2: Upload the Code**
Upload transmitter.ino to the Arduino connected to MPU6050.
Upload receiver.ino to the Arduino controlling the motors.
Step 3: Power Up & Test
Turn on both Arduinos.
Tilt the transmitter to move the robot accordingly.
If everything is working correctly, the robot should move in response to hand gestures!

📌 How It Works
The MPU6050 reads accelerometer values.
The nRF24L01 transmits data packets wirelessly.
The receiver decodes the signal and drives the motors.
The robot moves based on tilt direction (Forward, Backward, Left, Right).




🔧 Troubleshooting
Issue: Robot is not moving?
✅ Check power connections for both transmitter and receiver.
✅ Ensure the nRF24L01 modules are wired correctly.
✅ Try switching channels in radio.setChannel(90);
✅ Use Serial Monitor for debugging values.

📜 License
This project is open-source. Feel free to modify and improve it!
