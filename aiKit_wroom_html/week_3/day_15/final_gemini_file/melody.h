#ifndef MELODY_H
#define MELODY_H

#include <Arduino.h>

// Beeper 및 Speaker 핀 정의
#define BEEPER_PIN 14
#define SPEAKER_PIN 33

// 함수 선언
void melody_init();
void play_tone(int pin, int freq, int duration);
void play_melody_1(int pin);
void play_melody_2(int pin);
void play_melody_3(int pin);
void play_melody_4(int pin);

#endif
