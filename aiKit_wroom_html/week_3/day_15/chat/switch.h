#pragma once
#include <Arduino.h>

#define SWITCH_PIN 32

void switchInit();
bool switchGetState();   // true=눌림(LOW), false=안눌림(HIGH)
