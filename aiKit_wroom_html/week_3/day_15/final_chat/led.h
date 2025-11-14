#ifndef LED_H
#define LED_H
#include <Arduino.h>

void setupLED();                 // 소프트AP 이후 호출
void setRedLED(int brightness);  // 0~255 (Active-Low이므로 내부 반전)
void setYellowLED(int brightness);
void setBlueLED(int brightness);

#endif
