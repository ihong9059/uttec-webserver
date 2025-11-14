#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
private:
    int _redPin;
    int _yellowPin;
    int _bluePin;
    int _redValue;
    int _yellowValue;
    int _blueValue;

public:
    Led(int redPin, int yellowPin, int bluePin);
    void setup();
    void setRed(int value);
    void setYellow(int value);
    void setBlue(int value);
    void update();
};

#endif