#include "sensor.h"
#include <Wire.h>

Adafruit_AHTX0 aht;

void setupSensor() {
  if (! aht.begin()) {
    Serial.println("AHT20 센서를 찾을 수 없습니다. 연결을 확인하세요.");
  } else {
    Serial.println("AHT20 센서가 정상적으로 연결되었습니다.");
  }
}

void getSensorData(float* temperature, float* humidity) {
  sensors_event_t humidity_event, temp_event;
  aht.getEvent(&humidity_event, &temp_event);

  if (isnan(temp_event.temperature) || isnan(humidity_event.relative_humidity)) {
    Serial.println("센서 데이터를 읽는 데 실패했습니다.");
    *temperature = -999.0;
    *humidity = -999.0;
    return;
  }

  *temperature = temp_event.temperature;
  *humidity = humidity_event.relative_humidity;
}