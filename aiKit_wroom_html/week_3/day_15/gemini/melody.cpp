#include "melody.h"
#include "notes.h"
#include <Arduino.h>

#define BEEPER_PIN 14
#define SPEAKER_PIN 33

void setupMelody() {
  // tone() 함수는 pinMode를 내부적으로 처리하므로 별도의 설정이 필요 없습니다.
  // 부저는 LOW에서 켜지므로 HIGH로 초기화
  pinMode(BEEPER_PIN, OUTPUT);
  digitalWrite(BEEPER_PIN, HIGH);
}

void playTone(int frequency, int duration, int pin) {
  if (frequency == REST) {
    noTone(pin);
  } else {
    tone(pin, frequency, duration);
  }
  delay(duration);
  noTone(pin);
}

void playAlarm() {
  digitalWrite(BEEPER_PIN, LOW); // 부저 ON
  delay(500);
  digitalWrite(BEEPER_PIN, HIGH); // 부저 OFF
}

// 멜로디 데이터 (기존과 동일)
int melody1[] = { NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4 };
int duration1[] = { 250, 250, 500, 500, 500, 1000 };
int melody2[] = { NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4 };
int duration2[] = { 500, 500, 500, 500, 500, 500, 1000 };
int melody3[] = { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4 };
int duration3[] = { 500, 500, 500, 500, 500, 500, 1000 };
int melody4[] = { NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5 };
int duration4[] = { 500, 500, 500, 1000 };

void playMelody(int melodyIndex) {
  int* currentMelody;
  int* currentDuration;
  int length;

  switch (melodyIndex) {
    case 1:
      currentMelody = melody1;
      currentDuration = duration1;
      length = sizeof(melody1) / sizeof(melody1[0]);
      break;
    case 2:
      currentMelody = melody2;
      currentDuration = duration2;
      length = sizeof(melody2) / sizeof(melody2[0]);
      break;
    case 3:
      currentMelody = melody3;
      currentDuration = duration3;
      length = sizeof(melody3) / sizeof(melody3[0]);
      break;
    case 4:
      currentMelody = melody4;
      currentDuration = duration4;
      length = sizeof(melody4) / sizeof(melody4[0]);
      break;
    default:
      return;
  }

  for (int i = 0; i < length; i++) {
    playTone(currentMelody[i], currentDuration[i], SPEAKER_PIN);
    delay(50); // 음표 사이의 간격
  }
}

