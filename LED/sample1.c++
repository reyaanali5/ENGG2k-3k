#include <Adafruit_NeoPixel.h> //add to Tinker

#define SENSOR_PIN     2   // Define the pin where the IR receiver is connected
#define LED_PIN        6   // Define the pin where the data line is connected to the NeoPixel strip
#define NUMPIXELS      10  // Define the number of NeoPixels

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();  
  strip.show();   
  
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int sensorState = digitalRead(SENSOR_PIN);
  
  if (sensorState == LOW) {  // Assuming LOW means the beam is broken
    setColor(strip.Color(0, 0, 255));  // Set to blue color
  } else {
    setColor(0);  // Turn off
  }
  
  strip.show();
  delay(10);
}

void setColor(uint32_t color) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
}