#include "led.h"

// 초기화 함수
void led_init() {
  // pinMode는 main.ino의 WiFi.softAP() 함수 호출 다음에 실행됩니다.
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  
  // 시작 시 모든 LED는 꺼진 상태 (Low-ON 이므로 255)
  analogWrite(LED_RED_PIN, 255);
  analogWrite(LED_YELLOW_PIN, 255);
  analogWrite(LED_BLUE_PIN, 255);
}

// LED 제어 함수 (true = On, false = Off)
void led_control(int pin, bool state) {
  analogWrite(pin, state ? 0 : 255);
}
