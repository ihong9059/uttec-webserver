#pragma once
#include <Arduino.h>

// 핀 정의
#define BEEPER_PIN 14   // LOW=ON
#define SPEAKER_PIN 33  // tone() 출력

void melodyInit();
void playAlarm();           // 0.5초 beep
void playMelody(uint8_t id); // 1~4번 멜로디
