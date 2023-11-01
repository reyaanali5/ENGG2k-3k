#include <Adafruit_NeoPixel.h>
#define SENSOR_PIN 2
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


// Motor A connections
int enA = 5;
int in1 = 6;
int in2 = 7;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

boolean last_sensor_state = false;

class Strip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset(){
    
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct Loop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
};

Strip strip_0(60, 8, 60, NEO_GRB + NEO_KHZ800);
struct Loop strip0loop0(1, false, 1);

void strips_loop() {
  if(strip0_loop0() & 0x01)
    strip_0.strip.show();
}

uint8_t strip0_loop0() {
  uint8_t ret = 0x00;
  switch(strip0loop0.currentChild) {
    case 0: 
           ret = strip0_loop0_eff0();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
      strip0loop0.currentChild = 0;
      if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
    }
    else {
      strip0loop0.currentChild++;
    }
  };
  return ret;
}

uint8_t strip0_loop0_eff0() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 60
    // Steps: 60 - Delay: 20
    // Colors: 3 (255.0.0, 0.255.0, 0.0.255)
    // Options: rainbowlen=60, toLeft=false, 
  if(millis() - strip_0.effStart < 20 * (strip_0.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<60;j++) {
    ind = 60 - (uint16_t)(strip_0.effStep - j * 1) % 60;
    switch((int)((ind % 60) / 20)) {
      case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 20) / 20);
              factor2 = (float)((int)(ind - 0) % 60) / 20;
              strip_0.strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 20) / 20);
              factor2 = (float)((int)(ind - 20) % 60) / 20;
              strip_0.strip.setPixelColor(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 20) / 20);
              factor2 = (float)((int)(ind - 40) % 60) / 20;
              strip_0.strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              break;
    }
  }
  if(strip_0.effStep >= 60) {strip_0.Reset(); return 0x03; }
  else strip_0.effStep++;
  return 0x01;
}

int marbleCount = 0; // track number of marbles

void sensor_triggered()
{
  last_sensor_state = true;
}

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  strip_0.strip.begin();

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensor_triggered, FALLING);
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();

  
  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE); //for operational purposes

    display.display();
  //delay(2000);
    // Draw scrolling text

}


void loop()
{
  MotorRun();
  if(last_sensor_state) {
    Serial.println("Object detected!");
    marbleCount++;
    last_sensor_state = false;

    delay(800); //chnage for later, tinker, delaying for opening
  // wait for 1 second
     myservo.write(90);
  delay(700); //change for later, tinker, delaying for closing
  
  // Rotate to 90 degrees
  myservo.write(0);
  //delay(700);  // wait for 1
        // Draw scrolling text

    strips_loop();
        // Draw scrolling text
  }
  testscrolltext();
 sensor_triggered;// The CPU is free to do other things in the meantime
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
 // display.println(F("BOX 1 T1_C4"));
  display.println("Marbles: ");
  display.print(marbleCount);
  display.display();      // Show initial text
}

// This function lets you control spinning direction of motors
void MotorRun() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 150);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
}

