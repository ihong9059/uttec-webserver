#include "display.h"

// U8G2 객체 생성 (HW I2C, SDA=21, SCL=22)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// 4줄 텍스트 버퍼
static String lines[4] = {
  "UTTEC Lab Ai",
  "2번째 line",
  "3번째 line",
  "환영 합니다"
};

void displayInit() {
  u8g2.begin();
  u8g2.enableUTF8Print();                 // UTF-8 출력 활성화
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  // 초기 텍스트 표시
  for (int i=0;i<4;i++) {
    displaySetLine(i+1, lines[i].c_str());
  }
}

void displaySetLine(uint8_t line, const char* text) {
  if (line < 1 || line > 4) return;
  lines[line-1] = String(text);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  for (int i=0;i<4;i++) {
    u8g2.setCursor(0, (i+1)*16);   // 16픽셀 단위 줄 간격
    u8g2.print(lines[i]);
  }
  u8g2.sendBuffer();
}
