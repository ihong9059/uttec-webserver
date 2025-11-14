#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_AHTX0.h>

void setupSensor();
void getSensorData(float* temperature, float* humidity);

#endif

