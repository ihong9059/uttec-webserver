#include "led.h"

const int RED_LED_PIN = 25;
const int YELLOW_LED_PIN = 26;
const int BLUE_LED_PIN = 27;

void setupLED() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  // 시작시 모두 OFF (Active-Low → HIGH가 꺼짐)
  analogWrite(RED_LED_PIN,   255); // 0밝기
  analogWrite(YELLOW_LED_PIN,255);
  analogWrite(BLUE_LED_PIN,  255);
}

static inline void writeActiveLowPWM(int pin, int val){
  val = constrain(val, 0, 255);
  analogWrite(pin, 255 - val); // Active-Low 반전
}

void setRedLED(int brightness){    writeActiveLowPWM(RED_LED_PIN, brightness); }
void setYellowLED(int brightness){ writeActiveLowPWM(YELLOW_LED_PIN, brightness); }
void setBlueLED(int brightness){   writeActiveLowPWM(BLUE_LED_PIN, brightness); }
