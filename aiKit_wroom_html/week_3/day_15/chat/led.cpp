#include "led.h"

// ESP32(Arduino-ESP32 보드 패키지 3.x)에서 analogWrite는 기본 8비트(0~255).
// LOW=ON 이므로, pwmValue를 (255 - value)로 보정해서 씁니다.
// value 0   -> 255(=HIGH=OFF)  ≈ 꺼짐
// value 255 -> 0  (=LOW =ON)   ≈ 최대밝기

static void configPin(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // 시작 시 모두 OFF(=HIGH)
  // 필요시 해상도 지정 가능: analogWriteResolution(8);
}

void ledsInit() {
  configPin(PIN_RED);
  configPin(PIN_YELLOW);
  configPin(PIN_BLUE);
}

void ledOn(int pin) {
  digitalWrite(pin, LOW); // LOW=ON
}

void ledOff(int pin) {
  digitalWrite(pin, HIGH); // HIGH=OFF
}

void ledSetBrightness(int pin, uint8_t value) {
  // value: 0~255 (0=OFF, 255=최대밝기)
  // LOW=ON 보정
  uint8_t pwm = 255 - value;
  analogWrite(pin, pwm);
  // 주의: analogWrite 사용 시 핀은 PWM 출력이므로 단순 digitalWrite와 섞을 때는
  // 원하는 동작으로 고정하고 싶으면 value=0(OFF) 또는 255(최대)로 명시 사용 권장.
}

int ledPinFromName(const char* name) {
  if (!name) return -1;
  String s(name);
  s.toUpperCase();
  if (s == "RED")    return PIN_RED;
  if (s == "YELLOW") return PIN_YELLOW;
  if (s == "BLUE")   return PIN_BLUE;
  return -1;
}
