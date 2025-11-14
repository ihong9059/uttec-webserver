#include <Arduino.h>
#include "led.h"

void initLed() {
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH); // 초기 상태: 꺼짐 (LOW에서 ON)
}

void ledOn() {
  digitalWrite(RED_LED, LOW);  // LOW → LED ON
}

void ledOff() {
  digitalWrite(RED_LED, HIGH); // HIGH → LED OFF
}
