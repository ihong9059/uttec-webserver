#include "display.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

String line2Text = "2번째 line";
String line3Text = "3번째 line";
String line4Text = "환영 합니다";

void setupDisplay() {
  display.begin();
  display.setFont(u8g2_font_unifont_t_korean2);
  display.enableUTF8Print();
  updateDisplay();
}

void setDisplayText(const String& line2, const String& line3, const String& line4) {
  line2Text = line2;
  line3Text = line3;
  line4Text = line4;
  updateDisplay();
}

void updateDisplay() {
  display.clearBuffer();
  
  // 1라인: UTTEC Lab Ai
  display.setCursor(0, 15);
  display.print("UTTEC Lab Ai");
  
  // 2라인: 사용자 입력
  display.setCursor(0, 35);
  display.print(line2Text);
  
  // 3라인: 사용자 입력
  display.setCursor(0, 55);
  display.print(line3Text);
  
  // 4라인: 사용자 입력
  display.setCursor(0, 75);
  display.print(line4Text);
  
  display.sendBuffer();
}