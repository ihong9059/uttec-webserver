#include "switch.h"
#include <Arduino.h>

const int SWITCH_PIN = 32;
bool switchState = false;
bool lastSwitchState = false;

void setupSwitch() {
  pinMode(SWITCH_PIN, INPUT_PULLUP); // 내부 풀업 저항 사용
  switchState = digitalRead(SWITCH_PIN) == LOW; // 스위치가 눌리면 LOW
  lastSwitchState = switchState;
}

void updateSwitchState() {
  bool currentState = digitalRead(SWITCH_PIN) == LOW;
  
  // 상태가 변경되었을 때만 업데이트
  if (currentState != lastSwitchState) {
    // 디바운싱을 위한 약간의 지연
    delay(50);
    bool confirmedState = digitalRead(SWITCH_PIN) == LOW;
    
    if (confirmedState == currentState) {
      switchState = confirmedState;
      lastSwitchState = switchState;
      
      Serial.print("스위치 상태: ");
      Serial.println(switchState ? "켜짐" : "꺼짐");
    }
  }
}

bool getSwitchState() {
  return switchState;
}