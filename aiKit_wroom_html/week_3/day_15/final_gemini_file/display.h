#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8g2lib.h>

// I2C 핀 정의
#define SDA_PIN 21
#define SCL_PIN 22

// 외부 변수 선언
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

// 함수 선언
void display_init(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display);
void display_update_text(const char* text1, const char* text2, const char* text3, const char* text4);

#endif