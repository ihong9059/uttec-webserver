// led.h
#pragma once
#include <Arduino.h>

void initLedPins();              // softAP 이후 호출 필수
void setLedValue(const String& color, int value /*0~255 밝기*/);
void allLedOff();
