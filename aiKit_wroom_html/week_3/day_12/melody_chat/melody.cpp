#include "melody.h"

static uint8_t speakerPin;
static uint8_t redPin, yellowPin, bluePin;

void setupMelody(uint8_t pin, uint8_t r, uint8_t y, uint8_t b) {
  speakerPin = pin;
  redPin = r;
  yellowPin = y;
  bluePin = b;
}

void playMelody(int melody[], int noteDurations[], int length) {
  for (int i = 0; i < length; i++) {
    int noteDuration = 1000 / noteDurations[i];
    if (melody[i] == REST) {
      noTone(speakerPin);
    } else {
      tone(speakerPin, melody[i], noteDuration);
    }

    // LED 순차 점등
    int ledSel = i % 3;
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(bluePin, HIGH);
    if (ledSel == 0) digitalWrite(redPin, LOW);
    if (ledSel == 1) digitalWrite(yellowPin, LOW);
    if (ledSel == 2) digitalWrite(bluePin, LOW);

    delay(noteDuration * 1.3);
  }
  noTone(speakerPin);
  // LED 끄기
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(bluePin, HIGH);
}
