// display.h
#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// SSD1306 128x64, I2C: SDA=21, SCL=22
// 하드웨어 I2C 사용, 리셋 핀 없음
static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);

// 4번째 줄 문구를 저장
static String g_line4 = "";

// 초기화 (softAP 이후 호출)
static inline void displayBegin() {
  // U8g2가 Wire를 내부에서 시작하지만, 확실히 하기 위해 기본 핀으로 시작
  Wire.begin(21, 22);
  u8g2.begin();
  u8g2.enableUTF8Print(); // UTF-8 출력 활성화
}

// 4번째 줄 문구 설정
static inline void displaySetLine4(const String& s) {
  g_line4 = s;
}

// 화면 갱신 (1~3줄은 고정/센서값, 4줄은 입력 문구)
static inline void displayRender(float temp_c, float hum_rh) {
  // 문자열 구성
  char line2[32];  // "온도: 24.3°C"
  char line3[32];  // "습도: 55.0%"
  snprintf(line2, sizeof(line2), "온도: %.1f\xC2\xB0""C", temp_c); // °C
  snprintf(line3, sizeof(line3), "습도: %.1f%%", hum_rh);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_korean2); // 한글 폰트

  // y 좌표는 폰트 높이에 맞춰 베이스라인 기준(대략 16px 간격)
  u8g2.drawUTF8( 2, 14, "UTTEC Lab Ai");     // 1행
  u8g2.drawUTF8( 2, 32, line2);              // 2행
  u8g2.drawUTF8( 2, 50, line3);              // 3행

  // 4행: 웹에서 입력한 문구 (길면 잘릴 수 있음)
  if (g_line4.length() == 0) {
    u8g2.drawUTF8( 2, 64, "메시지를 보내 보세요!");
  } else {
    u8g2.drawUTF8( 2, 64, g_line4.c_str());
  }

  u8g2.sendBuffer();
}
