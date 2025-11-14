#include "beeper.h"

Beeper::Beeper(int pin) {
  beepPin = pin;
  isBeeping = false;
  beepStartTime = 0;
  beepDuration = 0;
}

void Beeper::begin() {
  pinMode(beepPin, OUTPUT);
  digitalWrite(beepPin, HIGH);  // LOW에서 beep이므로 초기에는 OFF
  Serial.println("Beeper initialized");
}

void Beeper::beep(unsigned long duration) {
  if (isBeeping) {
    // 이미 beeping 중이면 먼저 멈춤
    digitalWrite(beepPin, HIGH);
  }
  
  digitalWrite(beepPin, LOW);  // beep ON
  isBeeping = true;
  beepStartTime = millis();
  beepDuration = duration;
  Serial.print("Beep started for ");
  Serial.print(duration);
  Serial.println(" ms");
}

void Beeper::update() {
  if (isBeeping && (millis() - beepStartTime >= beepDuration)) {
    digitalWrite(beepPin, HIGH);  // beep OFF
    isBeeping = false;
    Serial.println("Beep stopped");
  }
}

bool Beeper::isActive() {
  return isBeeping;
}


