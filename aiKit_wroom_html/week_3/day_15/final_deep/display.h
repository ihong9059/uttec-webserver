#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

void setupDisplay();
void updateDisplay();
void setDisplayText(const String& line2, const String& line3, const String& line4);

#endif