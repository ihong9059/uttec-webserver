#include "switch.h"

// 생성자
SwitchControl::SwitchControl(int pin) {
    switchPin = pin;
}

// 핀 모드 설정 (풀업 저항 사용)
void SwitchControl::setupPin() {
    pinMode(switchPin, INPUT_PULLUP);
}

// 스위치 상태 확인 (눌리면 LOW, 아니면 HIGH)
bool SwitchControl::getState() {
    // 스위치가 눌렸을 때 true 반환
    return digitalRead(switchPin) == LOW;
}

