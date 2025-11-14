#include "melody.h"
#include "notes.h"
#include <Arduino.h>

const int BEEPER_PIN = 14;
const int SPEAKER_PIN = 33;

void setupMelody() {
  pinMode(BEEPER_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(BEEPER_PIN, HIGH); // Low에서 Beep이므로 초기 Off
}

void playAlarm() {
  digitalWrite(BEEPER_PIN, LOW);
  delay(500);
  digitalWrite(BEEPER_PIN, HIGH);
}

void playMelody(int melodyNumber) {
  // 간단한 멜로디 구현 (tone 함수 사용)
  switch(melodyNumber) {
    case 1: // 즐거운 날
      tone(SPEAKER_PIN, NOTE_C4, 300); delay(350);
      tone(SPEAKER_PIN, NOTE_E4, 300); delay(350);
      tone(SPEAKER_PIN, NOTE_G4, 300); delay(350);
      break;
    case 2: // 생일 축하곡
      tone(SPEAKER_PIN, NOTE_C4, 200); delay(250);
      tone(SPEAKER_PIN, NOTE_C4, 200); delay(250);
      tone(SPEAKER_PIN, NOTE_D4, 400); delay(450);
      tone(SPEAKER_PIN, NOTE_C4, 400); delay(450);
      break;
    case 3: // 작은 별
      tone(SPEAKER_PIN, NOTE_C4, 300); delay(350);
      tone(SPEAKER_PIN, NOTE_C4, 300); delay(350);
      tone(SPEAKER_PIN, NOTE_G4, 300); delay(350);
      tone(SPEAKER_PIN, NOTE_G4, 300); delay(350);
      break;
    case 4: // 게임 BGM
      tone(SPEAKER_PIN, NOTE_E4, 150); delay(200);
      tone(SPEAKER_PIN, NOTE_G4, 150); delay(200);
      tone(SPEAKER_PIN, NOTE_C5, 300); delay(350);
      break;
  }
  noTone(SPEAKER_PIN);
}