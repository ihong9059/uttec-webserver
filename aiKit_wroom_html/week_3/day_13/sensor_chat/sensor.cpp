// sensor.cpp
#include "sensor.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>

static Adafruit_AHTX0 aht;
static bool initialized = false;

void sensorBegin() {
  // AHT20: I2C (SDA=21, SCL=22 는 ESP32 기본 핀)
  Wire.begin(21, 22);
  initialized = aht.begin();
}

Aht20Reading sensorRead() {
  Aht20Reading out{};
  if (!initialized) {
    out.ok = false;
    out.temperature_c = NAN;
    out.humidity_rh   = NAN;
    return out;
  }
  sensors_event_t hum, temp;
  aht.getEvent(&hum, &temp); // 읽기
  out.ok = true;
  out.temperature_c = temp.temperature;
  out.humidity_rh   = hum.relative_humidity;
  return out;
}
