// display.cpp
#include "display.h"
#include <U8g2lib.h>
#include <Wire.h>

// HW I2C: SDA=21, SCL=22
// 일부 보드에선 핀 지정 없이도 됨. 여기선 명시:
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21
);

static String line1 = "UTTEC Lab Ai";
static String line2 = "2번째 line";
static String line3 = "3번째 line";
static String line4 = "환영 합니다";

static void redraw(){
  u8g2.clearBuffer();
  u8g2.setCursor(0, 14); u8g2.print(line1);
  u8g2.setCursor(0, 30); u8g2.print(line2);
  u8g2.setCursor(0, 46); u8g2.print(line3);
  u8g2.setCursor(0, 62); u8g2.print(line4);
  u8g2.sendBuffer();
}

void initDisplay(){
  Wire.begin(21,22);
  u8g2.begin();
  u8g2.enableUTF8Print(); // UTF-8 출력 활성
  u8g2.setFont(u8g2_font_unifont_t_korean2); // 한글 포함 폰트
  redraw();
}

void displaySetLines(const String& l1, const String& l2, const String& l3, const String& l4){
  if (l1.length()) line1 = l1;
  if (l2.length()) line2 = l2;
  if (l3.length()) line3 = l3;
  if (l4.length()) line4 = l4;
  redraw();
}
