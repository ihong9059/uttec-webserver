#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <Wire.h>

class Display {
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    
public:
    Display();
    void begin();
    void clear();
    void printLine(int line, const String& text);
    void show();
};

#endif