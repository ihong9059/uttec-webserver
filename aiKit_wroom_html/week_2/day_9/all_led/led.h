// led.h
#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
private:
    int pin;
    bool state;
    String color;
    
public:
    Led(int ledPin, String ledColor);
    void begin();
    void on();
    void off();
    void toggle();
    bool getState();
    String getColor();
};

#endif