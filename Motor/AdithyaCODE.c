// Include the Arduino library
#include <Arduino.h>

// Define the motor control pins
const int motorEnablePin = 9;
const int motorIn1Pin = 7;
const int motorIn2Pin = 8;

void setup() {
  // Set the motor control pins as outputs
  pinMode(motorEnablePin, OUTPUT);
  pinMode(motorIn1Pin, OUTPUT);
  pinMode(motorIn2Pin, OUTPUT);

  // Initialize serial communication (optional)
  Serial.begin(9600);
}

void loop() {
  // Set the motor direction (clockwise)
  digitalWrite(motorIn1Pin, HIGH);
  digitalWrite(motorIn2Pin, LOW);

  // Set the motor speed (0-255)
  int motorSpeed = 150; // Adjust as needed
  analogWrite(motorEnablePin, motorSpeed);

  // Print the motor speed to serial monitor (optional)
  Serial.print("Motor Speed: ");
  Serial.println(motorSpeed);

  // Delay for a while (e.g., 2 seconds)
  delay(2000);

  // Stop the motor
  analogWrite(motorEnablePin, 0);

  // Reverse the motor direction (counter-clockwise)
  digitalWrite(motorIn1Pin, LOW);
  digitalWrite(motorIn2Pin, HIGH);

  // Set a new motor speed
  motorSpeed = 200;
  analogWrite(motorEnablePin, motorSpeed);

  // Print the motor speed to serial monitor (optional)
  Serial.print("Motor Speed: ");
  Serial.println(motorSpeed);

  // Delay for a while
  delay(2000);

  // Stop the motor
  analogWrite(motorEnablePin, 0);
}
