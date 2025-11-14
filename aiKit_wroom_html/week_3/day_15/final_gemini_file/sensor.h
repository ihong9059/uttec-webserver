#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <Adafruit_AHTX0.h>

// 함수 선언
void sensor_init(Adafruit_AHTX0 &aht);
float get_temperature(Adafruit_AHTX0 &aht);
float get_humidity(Adafruit_AHTX0 &aht);

#endif