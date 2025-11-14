// led.cpp
#include "led.h"

// Low-Active LED: LOW=ON, HIGH=OFF
static const int PIN_RED = 25;
static const int PIN_YEL = 26;
static const int PIN_BLU = 27;

static int toLowActivePwm(int bright255){ // 0(꺼짐)~255(최대밝기)를 Low-Active로 변환
  // analogWrite: 0=LOW(ON최대), 255=HIGH(OFF)
  // 우리가 받은 bright는 사람기준 밝기이므로, 반전 필요:
  // 밝기 0 -> OFF(HIGH=255), 밝기 255 -> ON최대(LOW=0)
  return 255 - constrain(bright255, 0, 255);
}

void initLedPins(){
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YEL, OUTPUT);
  pinMode(PIN_BLU, OUTPUT);
  // 시작은 모두 OFF(=HIGH)
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_YEL, HIGH);
  digitalWrite(PIN_BLU, HIGH);
}

static int pinFromColor(const String& c){
  if (c == "red") return PIN_RED;
  if (c == "yellow") return PIN_YEL;
  if (c == "blue") return PIN_BLU;
  return -1;
}

void setLedValue(const String& color, int value){
  int pin = pinFromColor(color);
  if (pin < 0) return;
  int duty = toLowActivePwm(value);
  analogWrite(pin, duty); // 요구사항: ledcSetup/AttachPin 사용하지 말고 analogWrite 사용
}

void allLedOff(){
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_YEL, HIGH);
  digitalWrite(PIN_BLU, HIGH);
}
