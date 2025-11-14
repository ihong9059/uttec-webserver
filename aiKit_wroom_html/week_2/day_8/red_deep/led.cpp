#include "led.h"
#include <Arduino.h>

const int LED_PIN = 25;

void setupLED() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Low에서 On이므로 초기에는 Off
}

void ledOn() {
  digitalWrite(LED_PIN, LOW);
}

void ledOff() {
  digitalWrite(LED_PIN, HIGH);
}