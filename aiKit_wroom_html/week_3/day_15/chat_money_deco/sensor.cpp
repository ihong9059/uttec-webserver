// sensor.cpp
#include "sensor.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>

static Adafruit_AHTX0 aht;

void initSensor(){
  Wire.begin(21,22);
  aht.begin(); // 기본주소
}

bool readAHT20(float& t, float& h){
  sensors_event_t hum, temp;
  if (!aht.getEvent(&hum, &temp)) return false;
  t = temp.temperature;
  h = hum.relative_humidity;
  return true;
}
