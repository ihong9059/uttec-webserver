#include "sensor.h"

// AHT20 센서 초기화
void sensor_init(Adafruit_AHTX0 &aht) {
  if (!aht.begin()) {
    Serial.println("AHT20 센서 찾기 실패!");
  }
}

// 온도 측정
float get_temperature(Adafruit_AHTX0 &aht) {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  return temp.temperature;
}

// 습도 측정
float get_humidity(Adafruit_AHTX0 &aht) {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  return humidity.relative_humidity;
}
