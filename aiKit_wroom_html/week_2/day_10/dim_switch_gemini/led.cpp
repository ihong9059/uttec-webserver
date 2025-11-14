#include "Arduino.h"
#include "led.h"

// 생성자
LedControl::LedControl(int pin) {
    ledPin = pin;
}

// 핀 모드 설정 (WiFi 설정 이후에 호출)
void LedControl::setupPin() {
    pinMode(ledPin, OUTPUT);
    // 초기 상태: LED 끄기
    digitalWrite(ledPin, HIGH);
}

// LED 켜기 (Active Low: LOW)
void LedControl::turnOn() {
    // 0 = 최대 밝기
    analogWrite(ledPin, 0); 
}

// LED 끄기 (Active Low: HIGH)
void LedControl::turnOff() {
    // 255 = 최소 밝기 (꺼짐)
    analogWrite(ledPin, 255);
}

// 밝기 조절 (0:어두움 ~ 255:밝음)
void LedControl::setBrightness(int brightness) {
    // Active Low를 위해 밝기 값을 반전
    int analogValue = 255 - brightness;
    analogWrite(ledPin, analogValue);
}

