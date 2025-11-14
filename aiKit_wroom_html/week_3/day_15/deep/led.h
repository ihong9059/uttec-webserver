#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
private:
    int pin;
    bool isOn;
    
public:
    LED(int pin);
    void begin();
    void on();
    void off();
    void setBrightness(int brightness);
    bool getState();
};

#endif