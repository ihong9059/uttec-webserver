#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

void displayBegin();                    // softAP 이후
void displaySetLine(uint8_t lineIdx, const String& s); // 1~4
void displayRender();                   // 현재 저장된 라인으로 갱신

#endif
