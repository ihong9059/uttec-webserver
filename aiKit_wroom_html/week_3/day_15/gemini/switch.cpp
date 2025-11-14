#include "switch.h"
#include <Arduino.h>

#define SWITCH_PIN 32

void setupSwitch() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

bool getSwitchState() {
  // 스위치가 눌리면 LOW 신호를 반환
  return digitalRead(SWITCH_PIN);
}

