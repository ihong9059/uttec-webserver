#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <Wire.h>

class Display {
private:
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C display;
    String line1 = "UTTEC Lab Ai";
    String line2 = "Temp: --.-C";
    String line3 = "Humi: --.-%";
    String line4 = "";

public:
    Display() : display(U8G2_SSD1306_128X64_NONAME_F_SW_I2C(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/U8X8_PIN_NONE)) {}
    
    void begin() {
        Wire.begin(21, 22); // SDA=21, SCL=22
        display.begin();
        display.enableUTF8Print(); // UTF-8 출력 활성화
        display.setFont(u8g2_font_unifont_t_korean2); // 한국어 폰트 설정
        display.setFontDirection(0);
        clear();
    }

    void clear() {
        display.clearBuffer();
    }

    void show() {
        display.sendBuffer();
    }

    void setLine1(const String& text) {
        line1 = text;
        updateDisplay();
    }

    void setLine2(const String& text) {
        line2 = text;
        updateDisplay();
    }

    void setLine3(const String& text) {
        line3 = text;
        updateDisplay();
    }

    void setLine4(const String& text) {
        line4 = text;
        updateDisplay();
    }

    void updateDisplay() {
        clear();
        
        // 1라인: UTTEC Lab Ai
        display.setCursor(0, 12);
        display.print(line1);
        
        // 2라인: 온도
        display.setCursor(0, 28);
        display.print(line2);
        
        // 3라인: 습도
        display.setCursor(0, 44);
        display.print(line3);
        
        // 4라인: 사용자 입력
        display.setCursor(0, 60);
        display.print(line4.length() > 20 ? line4.substring(0, 20) : line4);
        
        show();
    }

    void displayMessage(float temperature, float humidity, const String& userInput = "") {
        line2 = "Temp: " + String(temperature, 1) + "C";
        line3 = "Humi: " + String(humidity, 1) + "%";
        if (!userInput.isEmpty()) {
            line4 = userInput;
        }
        updateDisplay();
    }
};

#endif