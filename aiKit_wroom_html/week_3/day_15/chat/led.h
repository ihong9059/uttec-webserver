#pragma once
#include <Arduino.h>

// 핀 정의 (LOW=ON)
#define PIN_RED     25
#define PIN_YELLOW  26
#define PIN_BLUE    27

// 초기화 & 제어 API
void ledsInit();                      // pinMode, 초기값(모두 OFF), analogWrite 기본화
void ledOn(int pin);                  // LOW=ON
void ledOff(int pin);                 // HIGH=OFF
void ledSetBrightness(int pin, uint8_t value /*0~255*/); // 0=꺼짐, 255=최대밝기 (LOW=ON 보정 내장)

// 이름 -> 핀번호 변환 (RED/YELLOW/BLUE)
int ledPinFromName(const char* name);
