#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class Switch {
private:
    int pin;
    bool lastState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
    
public:
    Switch(int pin);
    void begin();
    bool read();
    bool isPressed();
    bool stateChanged();
};

#endif

