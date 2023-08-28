#include <Servo.h>

// Pin assignments for motor driver control
const int motorPin1 = 2;  // Motor driver input pin 1
const int motorPin2 = 3;  // Motor driver input pin 2

// Pin assignment for servo control
const int servoPin = 9;  // Servo signal pin

// Pin assignment for sensor input
const int sensorPin = 4;  // Sensor input pin

Servo gateServo;  // Create a servo object

void setup() {
  // Initialize motor driver pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Attach servo to the pin
  gateServo.attach(servoPin);

  // Initialize sensor pin
  pinMode(sensorPin, INPUT);

  // Initial state: Close the gate
  closeGate();
}

void loop() {
  int sensorValue = digitalRead(sensorPin);

  if (sensorValue == HIGH) {
    openGate();
    delay(2000);  // Keep the gate open for 2 seconds
    closeGate();
  }
}

void openGate() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  gateServo.write(90);  // Move servo to open position (90 degrees)
}

void closeGate() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  gateServo.write(0);  // Move servo to closed position (0 degrees)
}
