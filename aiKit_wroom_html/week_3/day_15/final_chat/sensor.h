#pragma once
#include <Arduino.h>
struct Aht20Reading { bool ok; float temperature_c; float humidity_rh; };
void  sensorBegin();     // softAP 이후
Aht20Reading sensorRead();
