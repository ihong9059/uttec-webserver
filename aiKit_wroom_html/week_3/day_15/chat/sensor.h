#pragma once
#include <Arduino.h>
#include <Adafruit_AHTX0.h>

void sensorInit();
float sensorGetTemperature();   // °C
float sensorGetHumidity();      // %
