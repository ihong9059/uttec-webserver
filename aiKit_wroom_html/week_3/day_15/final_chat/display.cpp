#include "display.h"
#include <Wire.h>
#include <U8g2lib.h>

// I2C: SDA=21, SCL=22
static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);

static String L1="UTTEC Lab Ai", L2="2번째 line", L3="3번째 line", L4="환영 합니다";

void displayBegin(){
  Wire.begin(21,22);
  u8g2.begin();
  u8g2.enableUTF8Print();                 // UTF-8 활성화
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  displayRender();
}
void displaySetLine(uint8_t idx, const String& s){
  if(idx==1) L1=s; else if(idx==2) L2=s; else if(idx==3) L3=s; else if(idx==4) L4=s;
}
void displayRender(){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  u8g2.drawUTF8(2,14, L1.c_str());
  u8g2.drawUTF8(2,32, L2.c_str());
  u8g2.drawUTF8(2,50, L3.c_str());
  u8g2.drawUTF8(2,64, L4.c_str());
  u8g2.sendBuffer();
}
