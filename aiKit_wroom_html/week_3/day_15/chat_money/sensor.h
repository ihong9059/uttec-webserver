// sensor.h
#pragma once
#include <Arduino.h>

void initSensor();
bool readAHT20(float& t, float& h); // 섭씨/습도
