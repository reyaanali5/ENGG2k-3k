#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display(); 
  delay(2000);

  display.clearDisplay(); // Clear the buffer
  display.display(); // Show initial display buffer contents (clear display)

  // Set text color to white
  display.setTextColor(SSD1306_WHITE);
  // Set text size
  display.setTextSize(2);
}

void loop() {
  display.clearDisplay(); // Clear the buffer

  display.setCursor(0, 0); // Set cursor to the top-left corner
  display.print(F("T1_Box 1"));

  display.setCursor(0, 16);  // Vertical position changes, might need to be changed based on display
  display.print(F("Teams: Comms_4, Motions_5, Struct_1"));

  display.display(); // Display the content of the buffer

  delay(2000); // Wait for 2 seconds before clearing the display again
}