#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

// 스위치 핀 정의
#define SWITCH_PIN 32

// 함수 선언
void switch_init();
bool get_switch_state();

#endif