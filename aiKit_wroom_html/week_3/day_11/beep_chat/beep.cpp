// beep.cpp
#include "beep.h"
#include "led.h"

Beeper::Beeper(uint8_t pin, bool activeLow)
: _pin(pin), _activeLow(activeLow), _active(false), _until(0), _buddyLed(nullptr) {}

void Beeper::attachBuddy(Led* buddy) { _buddyLed = buddy; }

void Beeper::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _activeLow ? HIGH : LOW);
}

void Beeper::trigger(uint32_t ms) {
  digitalWrite(_pin, _activeLow ? LOW : HIGH);
  if (_buddyLed) _buddyLed->on();
  _active = true;
  _until = millis() + ms;
}

void Beeper::update() {
  if (_active && (int32_t)(millis() - _until) >= 0) {
    digitalWrite(_pin, _activeLow ? HIGH : LOW);
    if (_buddyLed) _buddyLed->off();
    _active = false;
  }
}

bool Beeper::isActive() const { return _active; }

