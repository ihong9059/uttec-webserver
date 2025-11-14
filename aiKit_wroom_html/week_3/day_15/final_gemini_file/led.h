#ifndef LED_H
#define LED_H

#include <Arduino.h>

// LED 핀 정의
#define LED_RED_PIN 25
#define LED_YELLOW_PIN 26
#define LED_BLUE_PIN 27

// 함수 선언
void led_init();
void led_control(int pin, bool state);

#endif
