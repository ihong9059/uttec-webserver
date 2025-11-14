#include "switch.h"

// 스위치 초기화
void switch_init() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

// 스위치 상태 읽기
bool get_switch_state() {
  return digitalRead(SWITCH_PIN);
}
