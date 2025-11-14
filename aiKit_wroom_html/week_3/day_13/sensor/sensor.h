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

public:
    bool begin() {
        Wire.begin(21, 22); // SDA=21, SCL=22
        return aht.begin(&Wire);
    }

    void update() {
        unsigned long currentTime = millis();
        if (currentTime - lastReadTime >= readInterval) {
            aht.getEvent(&humidity, &temp);
            lastReadTime = currentTime;
        }
    }

    float getTemperature() {
        return temp.temperature;
    }

    float getHumidity() {
        return humidity.relative_humidity;
    }
};

#endif