#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

void setupDisplay();
void updateDisplay();
void setDisplayData(float temp, float humi, const String& text);

// 외부에서 사용할 display 객체 선언
extern U8G2 display;

#endif