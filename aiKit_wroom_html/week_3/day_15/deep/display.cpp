#include "display.h"

Display::Display() : u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE) {}

void Display::begin() {
    Wire.begin(21, 22); // SDA=21, SCL=22
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_unifont_t_korean2);
    u8g2.setFontDirection(0);
    
    // 초기 화면 표시
    clear();
    printLine(1, "UTTEC Lab Ai");
    printLine(2, "2번째 line");
    printLine(3, "3번째 line");
    printLine(4, "환영 합니다");
    show();
}

void Display::clear() {
    u8g2.clearBuffer();
}

void Display::printLine(int line, const String& text) {
    int y_pos = 0;
    switch(line) {
        case 1: y_pos = 15; break;
        case 2: y_pos = 30; break;
        case 3: y_pos = 45; break;
        case 4: y_pos = 60; break;
        default: y_pos = 15; break;
    }
    u8g2.setCursor(0, y_pos);
    u8g2.print(text);
}

void Display::show() {
    u8g2.sendBuffer();
}