#include <Adafruit_NeoPixel.h>

class Observer
{
  protected:
    int pinsetLength;
    int *pinsetLed;
    int active;
    int pinSensor;
    int const TIME_ACTIVE = 1000;
    int const LIGHT_SENSOR_SENSITIVITY = 400;
    unsigned long timeStarted;

    void toggleActive()
    {
        if(analogRead(pinSensor) > LIGHT_SENSOR_SENSITIVITY && active == 0)
        {
            active = 1;
            timeStarted = millis();
        }
        else
        {
            unsigned long elapsed = millis() - timeStarted;
            if(elapsed > TIME_ACTIVE)
            {
                active = 0;
            }
        }
    };

  public:
    Observer(int pinSensor, int *pinsetLed, int pinsetLength)
    {
        this->pinSensor = pinSensor;
        this->pinsetLed = pinsetLed;
        this->pinsetLength = pinsetLength;
        active = 0;
        for(int i = 0; i < pinsetLength; i++)
        {
            pinMode(pinsetLed[i], OUTPUT);
        }
    };
    virtual void observe() = 0;
};

class ObserverDefault: public Observer
{
  public:
     ObserverDefault(int pinSensor, int *pinsetLed, int pinsetLength): Observer(pinSensor, pinsetLed, pinsetLength){};
     void observe()
     {
        toggleActive();

        for(int i = 0; i < pinsetLength; i++)
        {
            if(pinsetLed[i] != -1)
            {
                if (active)
                {
                    digitalWrite(pinsetLed[i], HIGH);
                }
                else
                {
                    digitalWrite(pinsetLed[i], LOW);
                }
            }
        }
     }
};

class ObserverRandom: public Observer
{
  public:
     ObserverRandom(int pinSensor, int *pinsetLed, int pinsetLength): Observer(pinSensor, pinsetLed, pinsetLength){};
     void observe()
     {
        toggleActive();
        if (active)
        {
            Serial.println(random(0, 15));
            int pow = generate_random_number();
            _set_leds(pow);
        }
        else
        {
            _set_leds(0);
        }
     };
  private:
    int _set_leds(int onOff)
    {
        int copyOnOff = onOff;
        for(int i = pinsetLength - 1; i > 0; i--)
        {
            if(pinsetLed[i] != -1)
            {
                int power = pow(2, i);
                if (onOff != 0 && (copyOnOff - pow(2, i)) > 0)
                {
                    copyOnOff = copyOnOff - pow(2, i);
                    digitalWrite(pinsetLed[i], HIGH);
                }
                else
                {
                    digitalWrite(pinsetLed[i], LOW);
                }
            }
        }
    };
    //Generates a random number between 1 and 2^pinsetLength
    int generate_random_number()
    {
        return random(0, pow(2, pinsetLength)) + 1;
    };

    int pow(int base, int pow){
        int result = 1;
        for(int i = 0; i < pow; i++){
            result = result * base;
        }
        return result;
    };
 };

class ObserverLed: public Observer
{
  public:
    int numPixels;

    ObserverLed(int pinSensor, unsigned int pinLed, unsigned int numPixels): Observer(pinSensor, pinsetLed, pinsetLength)
    {
        this->pinSensor = pinSensor;
        this->pinLed = pinLed;
        this->numPixels = numPixels;
        pixels = new Adafruit_NeoPixel(numPixels, pinLed, NEO_GRB + NEO_KHZ800);
        //Initialize the library
        pixels->begin();
    };

    void observe()
    {
        toggleActive();
        //Random colour each iteration
        int redColor = random(0, 255);
        int greenColor = random(0, 255);
        int blueColor = random(0, 255);

        if(active)
        {
            for (int i = 0; i < numPixels; i++)
            {
                pixels->setPixelColor(i, pixels->Color(redColor, greenColor, blueColor));
                pixels->show();
                delay(LED_DELAY);
            }
        }
    };

  private:
    Adafruit_NeoPixel *pixels;
    int const LED_DELAY = 100;
    unsigned int pinLed;
};


void setup()
{
  Serial.begin(9600);
}

int pinsetObserver[4] = {2, 3, 4, 5};
//Observer *observerDefault = new ObserverDefault(0, pinsetObserver, 4);
Observer *observerRandom = new ObserverRandom(0, pinsetObserver, 4);
ObserverLed *observerLed = new ObserverLed(1, 11, 10);
Observer *observers[1] = {observerRandom};

void loop()
{
  	observerLed->observe();
    analogWrite(6, 300);
    for (int i = 0; i < (sizeof(observers) / sizeof(observers[0])); i++)
    {
        observers[i]->observe();
    }
}

