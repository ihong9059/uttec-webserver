#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Adafruit_AHTX0.h>

class Sensor {
private:
    Adafruit_AHTX0 aht;
    sensors_event_t humidity, temp;
    unsigned long lastReadTime = 0;
    const unsigned long readInterval = 1000; // 1초 간격
    bool sensorAvailable = false;

public:
    bool begin() {
        Wire.begin(21, 22); // SDA=21, SCL=22
        if (aht.begin(&Wire)) {
            sensorAvailable = true;
            Serial.println("AHT20 센서 초기화 성공");
            return true;
        } else {
            Serial.println("AHT20 센서를 찾을 수 없습니다!");
            sensorAvailable = false;
            return false;
        }
    }

    void update() {
        if (!sensorAvailable) return;
        
        unsigned long currentTime = millis();
        if (currentTime - lastReadTime >= readInterval) {
            // 센서에서 새로운 데이터 읽기
            if (aht.getEvent(&humidity, &temp)) {
                Serial.printf("센서 읽기 성공: Temp=%.1fC, Humi=%.1f%%\n", 
                             temp.temperature, humidity.relative_humidity);
                lastReadTime = currentTime;
            } else {
                Serial.println("센서 읽기 실패!");
            }
        }
    }

    float getTemperature() {
        return sensorAvailable ? temp.temperature : -999.0;
    }

    float getHumidity() {
        return sensorAvailable ? humidity.relative_humidity : -999.0;
    }

    bool isAvailable() {
        return sensorAvailable;
    }
};

#endif
