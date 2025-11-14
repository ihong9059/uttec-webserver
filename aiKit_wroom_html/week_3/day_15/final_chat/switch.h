#pragma once
#include <Arduino.h>
void switchBegin(uint8_t pin, bool pullup);
bool switchPressed(); // Active-Low 기준: 눌림=LOW
