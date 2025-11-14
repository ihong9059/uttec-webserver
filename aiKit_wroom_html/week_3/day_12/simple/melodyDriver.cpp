#include "melodyDriver.h"

MelodyDriver::MelodyDriver(int spkPin, int redPin, int yellowPin, int bluePin) {
  speakerPin = spkPin;
  redLedPin = redPin;
  yellowLedPin = yellowPin;
  blueLedPin = bluePin;
}

void MelodyDriver::playNote(int note, int duration) {
  if (note == REST) {
    noTone(speakerPin);
  } else {
    tone(speakerPin, note);
  }
  delay(duration);
  noTone(speakerPin);
}

void MelodyDriver::setLed(int ledNumber, bool state) {
  switch(ledNumber) {
    case 1: digitalWrite(redLedPin, state ? HIGH : LOW); break;
    case 2: digitalWrite(yellowLedPin, state ? HIGH : LOW); break;
    case 3: digitalWrite(blueLedPin, state ? HIGH : LOW); break;
  }
}

void MelodyDriver::allLedsOff() {
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
}

void MelodyDriver::playMelody1() {
  // 도레미파솔라시도
  int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
  int noteDurations[] = {500, 500, 500, 500, 500, 500, 500, 500};
  
  for (int i = 0; i < 8; i++) {
    setLed((i % 3) + 1, true);
    playNote(melody[i], noteDurations[i]);
    setLed((i % 3) + 1, false);
    delay(50);
  }
  allLedsOff();
}

void MelodyDriver::playMelody2() {
  // 생일축하곡
  int melody[] = {NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
                  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4};
  int noteDurations[] = {400, 400, 800, 800, 800, 1600,
                        400, 400, 800, 800, 800, 1600};
  
  for (int i = 0; i < 12; i++) {
    setLed((i % 3) + 1, true);
    playNote(melody[i], noteDurations[i]);
    setLed((i % 3) + 1, false);
    delay(50);
  }
  allLedsOff();
}

void MelodyDriver::playMelody3() {
  // 징글벨
  int melody[] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
                  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4};
  int noteDurations[] = {500, 500, 1000, 500, 500, 1000,
                        500, 500, 500, 500, 2000};
  
  for (int i = 0; i < 11; i++) {
    setLed((i % 3) + 1, true);
    playNote(melody[i], noteDurations[i]);
    setLed((i % 3) + 1, false);
    delay(50);
  }
  allLedsOff();
}

void MelodyDriver::playMelody4() {
  // 오델로
  int melody[] = {NOTE_E5, NOTE_FS5, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_D5,
                  NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_B4};
  int noteDurations[] = {400, 400, 400, 400, 400, 400, 400, 400,
                        400, 400, 400, 400, 400, 400, 400, 800};
  
  for (int i = 0; i < 16; i++) {
    setLed((i % 3) + 1, true);
    playNote(melody[i], noteDurations[i]);
    setLed((i % 3) + 1, false);
    delay(50);
  }
  allLedsOff();
}

void MelodyDriver::playMelody5() {
  // 반짝반짝 작은별
  int melody[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
                  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};
  int noteDurations[] = {500, 500, 500, 500, 500, 500, 1000,
                        500, 500, 500, 500, 500, 500, 1000};
  
  for (int i = 0; i < 14; i++) {
    setLed((i % 3) + 1, true);
    playNote(melody[i], noteDurations[i]);
    setLed((i % 3) + 1, false);
    delay(50);
  }
  allLedsOff();
}

void MelodyDriver::playMelody6() {
  // 아리랑
  int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
                  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4};
  int noteDurations[] = {500, 500, 500, 500, 500, 500, 500, 500,
                        500, 500, 1000, 500, 500, 1000};
  
  for (int i = 0; i < 14; i++) {
    setLed((i % 3) + 1, true);
    playNote(melody[i], noteDurations[i]);
    setLed((i % 3) + 1, false);
    delay(50);
  }
  allLedsOff();
}

