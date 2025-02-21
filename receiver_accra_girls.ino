#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

const int leftMotorPin1 = 3;
const int leftMotorPin2 = 5;
const int rightMotorPin1 = 9;
const int rightMotorPin2 = 6;

RF24 radio(10, 8);  // nRF24L01(+) radio attached using Getting Started board

RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 00;   // Address of our node in Octal format (04, 031, etc)
const uint16_t other_node = 01;  // Address of the other node in Octal format

float xin = 0;
float yin = 0;

float data_packet[] = { xin, yin };


void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    // some boards need this because of native USB capability
  }
  Serial.println(F("RF24Network/examples/helloworld_rx/"));

  if (!radio.begin()) {
    Serial.println(F("Radio hardware not responding!"));
    while (1) {
      // hold in infinite loop
    }
  }
  radio.setChannel(90);
  network.begin(/*node address*/ this_node);

  // put your setup code here, to run once:
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
}

void loop(void) {

  network.update();  // Check the network regularly

  while (network.available()) {  // Is there anything ready for us?

    RF24NetworkHeader header;  // If so, grab it and print it out
    network.read(header, &data_packet, sizeof(data_packet));

    xin = data_packet[0];
    yin = data_packet[1];

    xin = map(xin, -10.00, 10.00, 0, 180.00);
    yin = map(yin, -10.00, 10.00, 0, 180.00);

    Serial.print(xin);
    Serial.print(",");
    Serial.println(yin);
    delay(10);






    if (xin < 80 || xin > 100 || yin < 80 || yin > 100) {
      move_car(xin, yin);
    } else {
      stopRobot();
    }
  }
}


void move_car(float x, float y) {
  if (x < 80) {
    turnLeft(x);
  }
  if (x > 100) {
    turnRight(x);
  }
  if (y < 80) {
    moveBackward(y);
  }

  if (y > 100) {
    moveForward(y);
  }

  if (!(x < 80) && !(y < 80) && !(x > 100) && !(y > 100)) {
    stopRobot();
  }
}

// Function to make the robot turn left
void turnLeft(float a) {
  int A = map(a, 80, 0, 0, 255);
  digitalWrite(leftMotorPin1, LOW);   // Left motor forward
  analogWrite(leftMotorPin2, A);      // Left motor backward
  analogWrite(rightMotorPin1, A);     // Right motor forward
  digitalWrite(rightMotorPin2, LOW);  // Right motor backward
}

// Function to make the robot turn right
void turnRight(float a) {
  int A = map(a, 100, 180, 0, 255);
  analogWrite(leftMotorPin1, A);      // Left motor forward
  digitalWrite(leftMotorPin2, LOW);   // Left motor backward
  digitalWrite(rightMotorPin1, LOW);  // Right motor forward
  analogWrite(rightMotorPin2, A);     // Right motor backward
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void moveForward(float a) {
  int A = map(a, 100, 180, 0, 255);
  analogWrite(leftMotorPin1, A);      // Left motor forward
  digitalWrite(leftMotorPin2, LOW);   // Left motor backward
  analogWrite(rightMotorPin1, A);     // Right motor forward
  digitalWrite(rightMotorPin2, LOW);  // Right motor backward
}

// Function to make the robot move backward
void moveBackward(float a) {
  int A = map(a, 80, 0, 0, 255);
  digitalWrite(leftMotorPin1, LOW);   // Left motor backward
  analogWrite(leftMotorPin2, A);      // Left motor forward
  digitalWrite(rightMotorPin1, LOW);  // Right motor backward
  analogWrite(rightMotorPin2, A);     // Right motor forward
}
