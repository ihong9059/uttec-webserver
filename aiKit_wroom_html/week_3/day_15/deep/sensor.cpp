#include "sensor.h"

Sensor::Sensor() {}

bool Sensor::begin() {
    Wire.begin(21, 22); // SDA=21, SCL=22
    if (!aht.begin(&Wire, 0, 0x38)) {
        return false;
    }
    return true;
}

float Sensor::getTemperature() {
    return temp.temperature;
}

float Sensor::getHumidity() {
    return humidity.relative_humidity;
}

void Sensor::update() {
    aht.getEvent(&humidity, &temp);
}