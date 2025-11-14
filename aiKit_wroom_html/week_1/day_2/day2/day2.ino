// ESP32-WROOM : Red LED Fade In/Out (1초 주기)
// GPIO 25번 핀에 Red LED 연결
// analogWrite 사용

#define RED_LED 25

void setup() {
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  // LED 밝아짐 (0 → 255, 약 1초)
  for (int i = 0; i <= 255; i++) {
    analogWrite(RED_LED, i);   // 0~255 : PWM 듀티비
    delay(1000 / 256);         // 1초를 256단계로 나눔 ≈ 4ms
    hks
  }

  // LED 어두워짐 (255 → 0, 약 1초)
  for (int i = 255; i >= 0; i--) {
    analogWrite(RED_LED, i);
    delay(1000 / 256);
  }
}
