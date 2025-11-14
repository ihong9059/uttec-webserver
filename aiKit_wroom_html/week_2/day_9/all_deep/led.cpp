#include "led.h"
#include <Arduino.h>

const int RED_LED_PIN = 25;
const int YELLOW_LED_PIN = 26;
const int BLUE_LED_PIN = 27;

void setupLED() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  // Low에서 On이므로 초기에는 모두 Off
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
}

void redLedOn() {
  digitalWrite(RED_LED_PIN, LOW);
}

void redLedOff() {
  digitalWrite(RED_LED_PIN, HIGH);
}

void yellowLedOn() {
  digitalWrite(YELLOW_LED_PIN, LOW);
}

void yellowLedOff() {
  digitalWrite(YELLOW_LED_PIN, HIGH);
}

void blueLedOn() {
  digitalWrite(BLUE_LED_PIN, LOW);
}

void blueLedOff() {
  digitalWrite(BLUE_LED_PIN, HIGH);
}