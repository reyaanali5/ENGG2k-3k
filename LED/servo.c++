#define SENSOR_PIN 2
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
boolean last_sensor_state = false;

int pos = 0;    // variable to store the servo position

void sensor_triggered()
{
  last_sensor_state = true;
}

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensor_triggered, FALLING);
}

void loop() {
  // Rotate to 0 degrees (initial position)
if(last_sensor_state) {
    Serial.println("Object detected!");
    last_sensor_state = false;

    delay(800); //chnage for later, tinker, delaying for opening
  // wait for 1 second
     myservo.write(90);
  delay(700); //change for later, tinker, delaying for closing
  
  
  // Rotate to 90 degrees
  myservo.write(0);
  //delay(700);  // wait for 1
        // Draw scrolling text
  }
 sensor_triggered;// The CPU is free to do other things in the meantime

}