#include "sensor.h"

static Adafruit_AHTX0 aht;

void sensorInit() {
  if (!aht.begin()) {
    Serial.println("[AHT20] 초기화 실패!");
  } else {
    Serial.println("[AHT20] 초기화 성공");
  }
}

float sensorGetTemperature() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // temp.temperature, humidity.relative_humidity
  return temp.temperature;
}

float sensorGetHumidity() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  return humidity.relative_humidity;
}
