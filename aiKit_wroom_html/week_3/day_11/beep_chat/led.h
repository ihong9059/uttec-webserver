// led.h
#pragma once
#include <Arduino.h>

class Led {
public:
  Led(uint8_t pin, bool activeLow = true)
  : _pin(pin), _activeLow(activeLow), _level(0), _isOn(false) {}

  void begin() {
    pinMode(_pin, OUTPUT);
    off(); // 시작 시 소등
  }

  void on() {
    _isOn = true;
    // Active-Low이면 LOW가 켜짐
    digitalWrite(_pin, _activeLow ? LOW : HIGH);
    _level = 255;
  }

  void off() {
    _isOn = false;
    digitalWrite(_pin, _activeLow ? HIGH : LOW);
    _level = 0;
  }

  // 0~255 (0=꺼짐, 255=최대밝기)
  void dim(uint8_t brightness) {
    _level = brightness;
    // ESP32 Arduino의 analogWrite 사용(사용자 요청: ledc* 직접 사용 금지)
    // Active-Low이므로 듀티 반전
    uint8_t duty = _activeLow ? (uint8_t)(255 - brightness) : brightness;
    analogWrite(_pin, duty);
    _isOn = (brightness > 0);
  }

  uint8_t level() const { return _level; }
  bool isOn() const { return _isOn; }
  uint8_t pin() const { return _pin; }

private:
  uint8_t _pin;
  bool    _activeLow;
  uint8_t _level;
  bool    _isOn;
};
