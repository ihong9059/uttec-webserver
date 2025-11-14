#pragma once
#include <Arduino.h>
void melodyBegin(uint8_t beeperPin, uint8_t speakerPin, bool beeperActiveLow);
void beepOnce(uint16_t ms);
void playMelodyId(int id); // 1~4 (blocking 재생, 교육용 단순 구현)
