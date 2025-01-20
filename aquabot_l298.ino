#include <Servo.h>

const int m1 = 4;
const int m2 = 5;

const int m3 = 7;
const int m4 = 8;

const int ena = 3;
const int enb = 6;

const int servoPin = 9; // Choose the appropriate pin for your servo
Servo servoMotor;

char bt = 'S';
unsigned long lastBluetoothTime = 0;
const unsigned long bluetoothTimeout = 1000; // Adjust the timeout value as needed (in milliseconds)

int mspeed = 0;

void setMotorSpeed(int speed) {
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void setMotorDirection(int m1State, int m2State, int m3State, int m4State) {
  digitalWrite(m1, m1State);
  digitalWrite(m2, m2State);
  digitalWrite(m3, m3State);
  digitalWrite(m4, m4State);
}

void stopAllMotors() {
  setMotorSpeed(0);
  setMotorDirection(LOW, LOW, LOW, LOW);
}

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  servoMotor.attach(servoPin);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    bt = Serial.read();
    lastBluetoothTime = millis(); // Update the time when Bluetooth data is received

    switch (bt) {
      case '0':
        mspeed = 0;
        break;
      case '1' ... '9':
        mspeed = (bt - '0') * 25.5;
        break;
      case 'q':
        mspeed = 255;
        break;
      case 'F':
        setMotorSpeed(mspeed);
        setMotorDirection(HIGH, LOW, HIGH, LOW);
        break;
      case 'B':
        setMotorSpeed(mspeed);
        setMotorDirection(LOW, HIGH, LOW, HIGH);
        break;
      case 'L':
        setMotorSpeed(mspeed);
        setMotorDirection(LOW, HIGH, HIGH, LOW);
        break;
      case 'R':
        setMotorSpeed(mspeed);
        setMotorDirection(HIGH, LOW, LOW, HIGH);
        break;
      case 'G':
        setMotorSpeed(mspeed);
        setMotorDirection(LOW, LOW, HIGH, LOW);
        break;
      case 'I':
        setMotorSpeed(mspeed);
        setMotorDirection(HIGH, LOW, LOW, LOW);
        break;
      case 'H':
        setMotorSpeed(mspeed);
        setMotorDirection(LOW, LOW, LOW, HIGH);
        break;
      case 'J':
        setMotorSpeed(mspeed);
        setMotorDirection(LOW, HIGH, LOW, LOW);
        break;
      case 'S':
        setMotorSpeed(mspeed);
        setMotorDirection(LOW, LOW, LOW, LOW);
        break;
      case 'W':
        servoMotor.write(90); // Adjust the angle as needed
        break;
      case 'w':
        servoMotor.write(0); // Adjust the angle as needed
        break;
      case 'U':
        servoMotor.write(120); // Adjust the angle as needed
        break;
      case 'u':
        servoMotor.write(0); // Adjust the angle as needed
        break;
      case 'V':
        servoMotor.write(150); // Adjust the angle as needed
        break;
      case 'v':
        servoMotor.write(0); // Adjust the angle as needed
        break;

      case 'X':
        servoMotor.write(180); // Adjust the angle as needed
        break;

      case 'x':
        servoMotor.write(0); // Adjust the angle as needed
        break;
    }
  }

  // Check if Bluetooth connection is lost
  if (millis() - lastBluetoothTime > bluetoothTimeout) {
    stopAllMotors();
    servoMotor.write(90); // Reset the servo position if connection is lost
    lastBluetoothTime = millis(); // Reset the timer to avoid repeated stopping
  }
}
