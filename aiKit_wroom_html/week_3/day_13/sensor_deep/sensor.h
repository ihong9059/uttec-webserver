#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Adafruit_AHTX0.h>

void setupSensor();
float readTemperature();
float readHumidity();

#endif