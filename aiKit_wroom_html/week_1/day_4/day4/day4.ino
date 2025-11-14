#include <Wire.h>
#include <U8g2lib.h>

// ESP32-WROOM I2C: SDA=21, SCL=22
// SSD1306 128x64, I2C, U8G2 라이브러리 객체 생성
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);

void setup(void) {
  u8g2.begin();                          // U8g2 초기화
  u8g2.enableUTF8Print();                // UTF-8 출력 활성화
  u8g2.setFont(u8g2_font_unifont_t_korean2); // 한글 지원 폰트 설정
}

void loop(void) {
  u8g2.clearBuffer();  // 버퍼 초기화

  u8g2.setCursor(0, 14);  
  u8g2.print("UTTEC Lab Ai");

  u8g2.setCursor(0, 28);
  u8g2.print("환영합니다");

  u8g2.setCursor(0, 42);
  u8g2.print("AI 프로그램");

  u8g2.setCursor(0, 56);
  u8g2.print("welcome UTTEC");

  u8g2.sendBuffer();   // OLED에 출력 적용

  delay(1000);
}

