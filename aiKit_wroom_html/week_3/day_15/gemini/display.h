#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

void setupDisplay();
void updateDisplay(const char* line1, const char* line2, const char* line3, const char* line4);

#endif

