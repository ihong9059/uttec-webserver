#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_AHTX0.h>

class Sensor {
private:
    Adafruit_AHTX0 aht;
    sensors_event_t humidity, temp;
    
public:
    Sensor();
    bool begin();
    float getTemperature();
    float getHumidity();
    void update();
};

#endif

