#include <Servo.h>

Servo servo;
char data;
int servoPin=9;
int pos=90;
byte motorPin1=5;
byte motorPin2=6;
byte motorSpeed=0;
byte motorSpeedLow=0;
byte motorSpeedHigh=255;
int switchPin=2;
int switchVal;
int xPin=0;
int yPin=1;
int xValues;
int yValues;
int xRight=1023;
int xLeft=0;
int xIdleLow=540;
int xIdleHigh=580;
int yUp=200; //default 0
int yDown=800; //default 1023

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(90);
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(switchPin,INPUT);
  digitalWrite(switchPin,HIGH);
}

void loop() {
  //if(Serial.available()){
    data=Serial.read();
    analogWrite(motorPin1,motorSpeed);
    analogWrite(motorPin2,motorSpeed);
    
    xValues=analogRead(xPin);
    if((xValues>xIdleHigh) or (data=='R')) {
      motorSpeed=map(xValues,xIdleHigh,xRight,motorSpeedLow,motorSpeedHigh);
      analogWrite(motorPin1,motorSpeed);
      analogWrite(motorPin2,motorSpeedLow);
      Serial.print("TURNING RIGHT...");
      Serial.print("\n");
      delay(50);
    } 
    
    xValues=analogRead(xPin);
    if((xValues<xIdleLow) or (data=='L')) {
      motorSpeed=map(xValues,xIdleLow,xLeft,motorSpeedLow,motorSpeedHigh);
      analogWrite(motorPin1,motorSpeedLow);
      analogWrite(motorPin2,motorSpeed);
      Serial.print("TURNING LEFT...");
      Serial.print("\n");
      delay(50);
    }
    
    yValues=analogRead(yPin);
    if((yValues<=yUp) or (data=='U')) {
      if(pos<150) {
        pos+=1;
      }
      Serial.print("BARREL UP");
      Serial.print("\n");
      delay(50);
    } else if((yValues>=yDown) or (data=='D')) {
      if(pos>30) {
        pos-=1; 
      }
      Serial.print("BARREL DOWN");
      Serial.print("\n");
      delay(50);
    }
    servo.write(pos);
    delay(50);

    switchVal=digitalRead(switchPin);
    if(switchVal==0) {
      Serial.print("SHOOTING");
      Serial.print("\n");
      delay(50);
    }
  //}
}