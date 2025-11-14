#include "display.h"
#include "sensor.h"

// display 객체 정의
U8G2 display = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 전역 변수
float currentTemp = 0;
float currentHumi = 0;
String currentText = "안녕하세요!";

void setupDisplay() {
  // SSD1306 I2C 디스플레이 초기화
  display.begin();
  
  // 한국어 폰트 설정 및 UTF-8 활성화
  display.setFont(u8g2_font_unifont_t_korean2);
  display.enableUTF8Print();
  
  Serial.println("SSD1306 디스플레이 초기화 완료!");
}

void setDisplayData(float temp, float humi, const String& text) {
  currentTemp = temp;
  currentHumi = humi;
  currentText = text;
  Serial.println("디스플레이 데이터 설정: " + text);
}

void updateDisplay() {
  display.clearBuffer();
  
  // 1라인: UTTEC Lab Ai
  display.setCursor(0, 15);
  display.print("UTTEC Lab Ai");
  
  // 2라인: 온도
  display.setCursor(0, 30);
  display.print("온도: ");
  display.print(currentTemp, 1);
  display.print("°C");
  
  // 3라인: 습도
  display.setCursor(0, 45);
  display.print("습도: ");
  display.print(currentHumi, 1);
  display.print("%");
  
  // 4라인: 사용자 입력 텍스트 (최대 16자 정도)
  display.setCursor(0, 60);
  String displayText = currentText;
  if (displayText.length() > 16) {
    displayText = displayText.substring(0, 16) + "...";
  }
  display.print(displayText);
  
  display.sendBuffer();
  Serial.println("디스플레이 업데이트 완료: " + currentText);
}

