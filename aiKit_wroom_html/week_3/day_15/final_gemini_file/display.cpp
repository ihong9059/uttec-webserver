#include "display.h"
#include <Wire.h>

// OLED 디스플레이 초기화
void display_init(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display) {
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin()) {
    Serial.println("OLED 시작 실패!");
  } else {
    display.enableUTF8Print(); // 한글 출력을 위한 UTF-8 활성화
    display.setFont(u8g2_font_unifont_t_korean2); // 한글 폰트 설정
    display.setFontMode(1);
    display.setFontDirection(0);
    display.setCursor(0, 15);
    display.print("UTTEC Lab Ai");
    display.setCursor(0, 30);
    display.print("2번째 line");
    display.setCursor(0, 45);
    display.print("3번째 line");
    display.setCursor(0, 60);
    display.print("환영 합니다");
    display.sendBuffer();
  }
}

// OLED에 텍스트 업데이트
void display_update_text(const char* text1, const char* text2, const char* text3, const char* text4) {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print(text1);
  u8g2.setCursor(0, 30);
  u8g2.print(text2);
  u8g2.setCursor(0, 45);
  u8g2.print(text3);
  u8g2.setCursor(0, 60);
  u8g2.print(text4);
  u8g2.sendBuffer();
}
