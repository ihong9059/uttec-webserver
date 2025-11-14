// switch.h
#pragma once
#include <Arduino.h>

class Switch {
public:
  Switch(uint8_t pin, bool pullup = true)
  : _pin(pin), _pullup(pullup) {}

  void begin() {
    if (_pullup) pinMode(_pin, INPUT_PULLUP);
    else pinMode(_pin, INPUT);
  }

  // 스위치가 눌렸는지 (Active-Low 기준: 눌리면 LOW)
  bool isPressed() {
    return digitalRead(_pin) == (_pullup ? LOW : HIGH);
  }

  // 상태를 텍스트로 반환
  String stateText() {
    return isPressed() ? "눌림" : "떼짐";
  }

private:
  uint8_t _pin;
  bool _pullup;
};
