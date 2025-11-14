#pragma once
#include <Arduino.h>
#include <U8g2lib.h>

// I2C 핀 정의
#define DISP_SDA 21
#define DISP_SCL 22

// 외부에서 접근할 U8G2 객체 선언
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

// 초기화 함수
void displayInit();

// 문자열 설정 및 화면 업데이트
void displaySetLine(uint8_t line, const char* text);
