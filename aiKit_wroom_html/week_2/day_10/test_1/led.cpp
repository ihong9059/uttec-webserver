#include "led.h"
#include <Arduino.h>

LED::LED(int red, int yellow, int blue) {
  redPin = red;
  yellowPin = yellow;
  bluePin = blue;
}

void LED::begin() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  digitalWrite(redPin, HIGH);    // LOW에서 ON이므로 초기에는 OFF
  digitalWrite(yellowPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void LED::setRed(bool state) {
  digitalWrite(redPin, state ? LOW : HIGH);
}

void LED::setYellow(bool state) {
  digitalWrite(yellowPin, state ? LOW : HIGH);
}

void LED::setBlue(bool state) {
  digitalWrite(bluePin, state ? LOW : HIGH);
}

void LED::dimRed(int value) {
  analogWrite(redPin, 255 - constrain(value, 0, 255));  // LOW에서 ON이므로 반전
}

void LED::dimYellow(int value) {
  analogWrite(yellowPin, 255 - constrain(value, 0, 255));
}

void LED::dimBlue(int value) {
  analogWrite(bluePin, 255 - constrain(value, 0, 255));
}

