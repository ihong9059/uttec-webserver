#include "led.h"

LED::LED(int pin) {
    this->pin = pin;
    this->isOn = false;
}

void LED::begin() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // LOW에서 ON이 되므로 시작시 HIGH로 꺼짐
}

void LED::on() {
    digitalWrite(pin, LOW);
    isOn = true;
}

void LED::off() {
    digitalWrite(pin, HIGH);
    isOn = false;
}

void LED::setBrightness(int brightness) {
    brightness = constrain(brightness, 0, 255);
    analogWrite(pin, 255 - brightness); // LOW에서 ON이므로 반전
}

bool LED::getState() {
    return isOn;
}