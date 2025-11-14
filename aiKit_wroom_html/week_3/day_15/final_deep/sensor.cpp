#include "sensor.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
sensors_event_t humidity, temp;

void setupSensor() {
  Wire.begin(21, 22);
  if (!aht.begin(&Wire)) {
    Serial.println("AHT20 센서를 찾을 수 없습니다!");
    while (1) delay(10);
  }
}

float readTemperature() {
  aht.getEvent(&humidity, &temp);
  return temp.temperature;
}

float readHumidity() {
  aht.getEvent(&humidity, &temp);
  return humidity.relative_humidity;
}