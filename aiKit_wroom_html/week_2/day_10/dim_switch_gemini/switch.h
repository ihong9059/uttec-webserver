#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class SwitchControl {
public:
    // 생성자 (핀 번호 설정)
    SwitchControl(int pin);

    // 핀 모드 설정
    void setupPin();

    // 스위치 상태 확인
    bool getState();

private:
    int switchPin;
};

#endif