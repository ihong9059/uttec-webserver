#ifndef MELODYDRIVER_H
#define MELODYDRIVER_H

#include <Arduino.h>
#include "notes.h"

class MelodyDriver {
private:
  int speakerPin;
  int redLedPin;
  int yellowLedPin;
  int blueLedPin;
  
public:
  MelodyDriver(int spkPin, int redPin, int yellowPin, int bluePin);
  
  void playNote(int note, int duration);
  void playMelody1(); // 도레미파솔라시도
  void playMelody2(); // 생일축하곡
  void playMelody3(); // 징글벨
  void playMelody4(); // 오델로
  void playMelody5(); // 반짝반짝 작은별
  void playMelody6(); // 아리랑
  
  void setLed(int ledNumber, bool state);
  void allLedsOff();
};

#endif