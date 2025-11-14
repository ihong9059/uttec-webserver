// beep.h
#pragma once
#include <Arduino.h>
class Led;

class Beeper {
public:
  Beeper(uint8_t pin, bool activeLow = true);
  void attachBuddy(Led* buddy);
  void begin();
  void trigger(uint32_t ms);
  void update();
  bool isActive() const;

private:
  uint8_t  _pin;
  bool     _activeLow;
  bool     _active;
  uint32_t _until;
  Led*     _buddyLed;
};
