#include "display.h"

// SSD1306 OLED 128x64, I2C 통신, 리셋 핀 없음
// SDA: 21, SCL: 22
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setupDisplay() {
  u8g2.begin();
  u8g2.enableUTF8Print(); // UTF-8 출력 활성화
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("UTTEC Lab Ai");
  u8g2.setCursor(0, 30);
  u8g2.print("2번째 line");
  u8g2.setCursor(0, 45);
  u8g2.print("3번째 line");
  u8g2.setCursor(0, 60);
  u8g2.print("환영 합니다");
  u8g2.sendBuffer();
}

void updateDisplay(const char* line1, const char* line2, const char* line3, const char* line4) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  u8g2.setCursor(0, 15);
  u8g2.print(line1);
  u8g2.setCursor(0, 30);
  u8g2.print(line2);
  u8g2.setCursor(0, 45);
  u8g2.print(line3);
  u8g2.setCursor(0, 60);
  u8g2.print(line4);
  u8g2.sendBuffer();
}


