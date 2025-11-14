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
  setRedLED(0);
  setYellowLED(0);
  setBlueLED(0);
}

void setRedLED(int brightness) {
  analogWrite(RED_LED_PIN, 255 - brightness); // Low에서 On이므로 반전
}

void setYellowLED(int brightness) {
  analogWrite(YELLOW_LED_PIN, 255 - brightness); // Low에서 On이므로 반전
}

void setBlueLED(int brightness) {
  analogWrite(BLUE_LED_PIN, 255 - brightness); // Low에서 On이므로 반전
}