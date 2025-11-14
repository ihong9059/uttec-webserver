#include "switch.h"
#include <Arduino.h>

const int SWITCH_PIN = 32;

void setupSwitch() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

bool readSwitch() {
  return digitalRead(SWITCH_PIN) == LOW; // 스위치가 눌리면 LOW
}