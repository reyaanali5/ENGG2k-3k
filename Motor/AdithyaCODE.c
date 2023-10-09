// Define the Arduino pins connected to the motor driver
const int enablePin = 9; // PWM pin for motor speed control
const int in1Pin = 8;    // Motor input 1
const int in2Pin = 7;    // Motor input 2

void setup() {
  // Set the motor control pins as outputs
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  // Initialize the serial communication for debugging (optional)
  Serial.begin(9600);

  // Set the initial motor direction and speed (0-255)
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, 0); // Set speed to 0 initially
}

void loop() {
  // Forward direction
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, 150); // Set motor speed (0-255)

  // Wait for a few seconds
  delay(5000);

  // Reverse direction
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enablePin, 150); // Set motor speed (0-255)

  // Wait for a few seconds
  delay(5000);

  // Stop the motor
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, 0); // Set speed to 0 (stop)

  // Wait for a few seconds
  delay(5000);
}
