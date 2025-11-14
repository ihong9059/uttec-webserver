#include "switch.h"

void switchInit() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);  
  // 풀업 입력으로 설정 → 눌림 시 LOW, 놓으면 HIGH
}

bool switchGetState() {
  return digitalRead(SWITCH_PIN) == LOW;  // 눌리면 true
}
