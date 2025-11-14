// sensor.h
#pragma once
#include <Arduino.h>

struct Aht20Reading {
  bool   ok;
  float  temperature_c;
  float  humidity_rh;
};

void  sensorBegin();                 // AHT20 초기화 (softAP 후 호출)
Aht20Reading sensorRead();           // 현재값 읽기 (성공/실패 포함)
