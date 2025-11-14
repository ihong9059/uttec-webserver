#include "led.h"

Led::Led(int redPin, int yellowPin, int bluePin) {
    _redPin = redPin;
    _yellowPin = yellowPin;
    _bluePin = bluePin;
    _redValue = 0;
    _yellowValue = 0;
    _blueValue = 0;
}

void Led::setup() {
    pinMode(_redPin, OUTPUT);
    pinMode(_yellowPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
    // Low에서 LED가 On되므로, 초기 상태를 OFF (PWM 0)로 설정합니다.
    analogWrite(_redPin, 0);
    analogWrite(_yellowPin, 0);
    analogWrite(_bluePin, 0);
}

void Led::setRed(int value) {
    _redValue = value;
}

void Led::setYellow(int value) {
    _yellowValue = value;
}

void Led::setBlue(int value) {
    _blueValue = value;
}

void Led::update() {
    // Low에서 LED가 On되므로, 값을 반전시켜서 analogWrite 합니다.
    analogWrite(_redPin, 255 - _redValue);
    analogWrite(_yellowPin, 255 - _yellowValue);
    analogWrite(_bluePin, 255 - _blueValue);
}
