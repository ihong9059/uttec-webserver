#include "beep.h"
#include "led.h"  // setRedLED 사용

Beeper::Beeper(uint8_t pin, bool activeLow)
: _pin(pin), _activeLow(activeLow), _active(false), _until(0) {}

void Beeper::begin() {
  pinMode(_pin, OUTPUT);
  // Active-Low → HIGH = OFF
  digitalWrite(_pin, _activeLow ? HIGH : LOW);
}

void Beeper::trigger(uint32_t ms) {
  // 비프 On
  digitalWrite(_pin, _activeLow ? LOW : HIGH);
  setRedLED(255); // 빨간 LED On
  _active = true;
  _until = millis() + ms;
}

void Beeper::update() {
  if (_active && (int32_t)(millis() - _until) >= 0) {
    // 비프 Off
    digitalWrite(_pin, _activeLow ? HIGH : LOW);
    setRedLED(0); // 빨간 LED Off
    _active = false;
  }
}

bool Beeper::isActive() const {
  return _active;
}
