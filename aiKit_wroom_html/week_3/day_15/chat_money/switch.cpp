// switch.cpp
#include "switch.h"

static const int PIN_SW = 32;

void initSwitch(){
  pinMode(PIN_SW, INPUT_PULLUP); // 외부 회로에 맞게 필요시 변경
}

int readSwitch(){
  // 풀업 기준: 눌림=LOW(0), 안눌림=HIGH(1)
  return digitalRead(PIN_SW) == HIGH ? 1 : 0;
}
