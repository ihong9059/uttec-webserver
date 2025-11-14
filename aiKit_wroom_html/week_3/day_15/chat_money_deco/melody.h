// melody.h
#pragma once
#include <Arduino.h>
void initMelody();
void alarmBeep();       // beeper(14) LOW로 0.5초
void playMelody(int no); // 1~4
