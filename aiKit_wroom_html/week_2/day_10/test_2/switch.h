#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class Switch {
  private:
    int pin;
    bool state;
    bool lastButtonState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
    
  public:
    Switch(int switchPin);
    void begin();
    void read();
    bool getState();
    bool isPressed();
    bool isReleased();
};

#endif


