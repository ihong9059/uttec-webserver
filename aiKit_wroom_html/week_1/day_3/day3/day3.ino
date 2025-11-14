// ESP32-WROOM : Traffic Light + Melody
// LED는 LOW에서 ON
// Red=25, Yellow=26, Blue=27
// Speaker=33

#define RED_LED     25
#define YELLOW_LED  26
#define BLUE_LED    27
#define SPEAKER_PIN 33

// "건너가세요" 멜로디 (예: 짧은 반복음)
int melody[] = { 784, 988, 784, 988 }; // 솔-시-솔-시 (Hz)
int noteDurations[] = { 4, 4, 4, 4 };  // 각각 1/4박자

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(RED_LED, HIGH);    // 초기 OFF
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void playMelody(int durationMs) {
  unsigned long startTime = millis();
  while (millis() - startTime < durationMs) {
    for (int i = 0; i < 4; i++) {
      int noteDuration = 1000 / noteDurations[i];
      tone(SPEAKER_PIN, melody[i], noteDuration);
      delay(noteDuration * 1.3);
      if (millis() - startTime >= durationMs) {
        break; // Blue 시간(10초)이 끝나면 빠져나감
      }
    }
  }
  noTone(SPEAKER_PIN);
}

void loop() {
  // Red ON (10초)
  digitalWrite(RED_LED, LOW); // ON
  delay(10000);
  digitalWrite(RED_LED, HIGH); // OFF

  // Yellow ON (2초)
  digitalWrite(YELLOW_LED, LOW);
  delay(2000);
  digitalWrite(YELLOW_LED, HIGH);

  // Blue ON (10초) + Melody 반복
  digitalWrite(BLUE_LED, LOW);
  playMelody(10000); // 10초 동안 건너가라는 멜로디 반복
  digitalWrite(BLUE_LED, HIGH);

  // Yellow ON (2초)
  digitalWrite(YELLOW_LED, LOW);
  delay(2000);
  digitalWrite(YELLOW_LED, HIGH);
}









