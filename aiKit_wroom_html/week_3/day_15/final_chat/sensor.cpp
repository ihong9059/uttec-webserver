#include "sensor.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>

static Adafruit_AHTX0 aht;
static bool inited=false;

void sensorBegin(){
  Wire.begin(21,22);
  inited = aht.begin();
}
Aht20Reading sensorRead(){
  Aht20Reading out{};
  if(!inited){ out.ok=false; out.temperature_c=NAN; out.humidity_rh=NAN; return out; }
  sensors_event_t hum, temp;
  aht.getEvent(&hum, &temp);
  out.ok=true; out.temperature_c=temp.temperature; out.humidity_rh=hum.relative_humidity;
  return out;
}
