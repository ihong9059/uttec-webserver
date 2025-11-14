#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_AHTX0.h>

// U8g2 객체 생성 (SSD1306 128x64, I2C, HW 연결)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21
);

// AHT20 센서 객체
Adafruit_AHTX0 aht;

void setup(void) {
  Serial.begin(115200);
  delay(100);

  // I2C 시작
  Wire.begin(21, 22);

  // OLED 초기화
  u8g2.begin();
  u8g2.enableUTF8Print();                       // UTF-8 출력 활성화
  u8g2.setFont(u8g2_font_unifont_t_korean2);    // 한글 폰트 설정

  // AHT20 초기화
  if (!aht.begin()) {
    Serial.println("AHT20 센서를 찾을 수 없습니다!");
    while (1) delay(10);
  }
  Serial.println("AHT20 센서 초기화 성공!");
}

void loop(void) {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // 온도, 습도 읽기

  // OLED 화면에 표시
  u8g2.clearBuffer();

  u8g2.setCursor(0, 14);
  u8g2.print("UTTEC Lab Ai");

  u8g2.setCursor(0, 28);
  u8g2.print("온도: ");
  u8g2.print(temp.temperature);
  u8g2.print(" C");

  u8g2.setCursor(0, 42);
  u8g2.print("습도: ");
  u8g2.print(humidity.relative_humidity);
  u8g2.print(" %");

  u8g2.setCursor(0, 56);
  u8g2.print("welcome UTTEC");

  u8g2.sendBuffer();

  delay(2000); // 2초마다 갱신
}

