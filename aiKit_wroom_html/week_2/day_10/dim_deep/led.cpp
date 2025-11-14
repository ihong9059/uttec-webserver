#include "led.h"
#include <Arduino.h>

const int RED_LED_PIN = 25;
const int YELLOW_LED_PIN = 26;
const int BLUE_LED_PIN = 27;

void setupLED() {
  // LED 핀을 출력으로 설정
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  // 초기에는 모든 LED 끄기
  setRedLED(0);
  setYellowLED(0);
  setBlueLED(0);
}

void setRedLED(int brightness) {
  // Low에서 On이므로 반전 (255 - brightness)
  analogWrite(RED_LED_PIN, 255 - brightness);
}

void setYellowLED(int brightness) {
  // Low에서 On이므로 반전 (255 - brightness)
  analogWrite(YELLOW_LED_PIN, 255 - brightness);
}

void setBlueLED(int brightness) {
  // Low에서 On이므로 반전 (255 - brightness)
  analogWrite(BLUE_LED_PIN, 255 - brightness);
}
