#include "melody.h"
#include "notes.h"

// 멜로디 관련 초기화
void melody_init() {
  pinMode(BEEPER_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(BEEPER_PIN, HIGH); // Low에서 Beep이므로 초기 Off
}

// 톤 재생 함수
void play_tone(int pin, int freq, int duration) {
  tone(pin, freq, duration);
  delay(duration);
  noTone(pin);
}

// 생일 축하 멜로디
void play_melody_1(int pin) {
  int melody[] = { NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, REST, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, REST };
  int noteDurations[] = { 400, 400, 400, 400, 400, 400, 200, 400, 400, 400, 400, 400, 400, 200 };
  for (int i = 0; i < 14; i++) {
    play_tone(pin, melody[i], noteDurations[i]);
  }
}

// 작은 별 멜로디
void play_melody_2(int pin) {
  int melody[] = { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, REST, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, REST };
  int noteDurations[] = { 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400 };
  for (int i = 0; i < 16; i++) {
    play_tone(pin, melody[i], noteDurations[i]);
  }
}

// 엘리제를 위하여 멜로디
void play_melody_3(int pin) {
  int melody[] = { NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4, REST, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4 };
  int noteDurations[] = { 200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 400, 400, 400, 400 };
  for (int i = 0; i < 14; i++) {
    play_tone(pin, melody[i], noteDurations[i]);
  }
}

// 떴다 떴다 비행기 멜로디
void play_melody_4(int pin) {
  int melody[] = { NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4, REST, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4, REST };
  int noteDurations[] = { 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250 };
  for (int i = 0; i < 10; i++) {
    play_tone(pin, melody[i], noteDurations[i]);
  }
}
