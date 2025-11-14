#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"
#include "melody.h"

// WiFi AP 설정
const char* AP_SSID = "홍길동";
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

// 핀
constexpr uint8_t SPEAKER_PIN = 33;
constexpr uint8_t RED_LED_PIN = 25;
constexpr uint8_t YELLOW_LED_PIN = 26;
constexpr uint8_t BLUE_LED_PIN = 27;

// 멜로디 1: C메이저 스케일 오르내리기
int melody1[] = { NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5,
                  NOTE_B4,NOTE_A4,NOTE_G4,NOTE_F4,NOTE_E4,NOTE_D4,NOTE_C4,
                  REST };
int durations1[] = {4,4,4,4,4,4,4,2, 4,4,4,4,4,4,2, 4};
int len1 = sizeof(melody1)/sizeof(melody1[0]);

// 멜로디 2: "작은 별" (Twinkle Twinkle)
int melody2[] = {
  NOTE_C4,NOTE_C4,NOTE_G4,NOTE_G4,NOTE_A4,NOTE_A4,NOTE_G4,
  NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_D4,NOTE_C4,
  REST
};
int durations2[] = {4,4,4,4,4,4,2, 4,4,4,4,4,4,2, 4};
int len2 = sizeof(melody2)/sizeof(melody2[0]);

// 멜로디 3: "학교 종"
int melody3[] = {
  NOTE_G4,NOTE_G4,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_E4,
  NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_D4, REST
};
int durations3[] = {4,4,4,4,4,4,2, 4,4,4,4,2, 4};
int len3 = sizeof(melody3)/sizeof(melody3[0]);

// 멜로디 4: 단순 반복 (C-E-G-C)
int melody4[] = {
  NOTE_C4,NOTE_E4,NOTE_G4,NOTE_C5,
  NOTE_C4,NOTE_E4,NOTE_G4,NOTE_C5,
  NOTE_C4,NOTE_E4,NOTE_G4,NOTE_C5,
  NOTE_C4,NOTE_E4,NOTE_G4,NOTE_C5,
  REST
};
int durations4[] = {4,4,4,2, 4,4,4,2, 4,4,4,2, 4,4,4,2, 4};
int len4 = sizeof(melody4)/sizeof(melody4[0]);

// 멜로디 5: "도레미송" 일부
int melody5[] = {
  NOTE_C4,NOTE_D4,NOTE_E4,NOTE_C4,
  NOTE_E4,NOTE_F4,NOTE_G4,NOTE_E4,
  NOTE_C4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_F4, REST
};
int durations5[] = {4,4,4,4, 4,4,2,4, 4,4,4,4,2,4};
int len5 = sizeof(melody5)/sizeof(melody5[0]);

// 멜로디 6: 단순 코드 순환 (C-F-G-C)
int melody6[] = {
  NOTE_C4,NOTE_F4,NOTE_G4,NOTE_C5,
  NOTE_C4,NOTE_F4,NOTE_G4,NOTE_C5,
  NOTE_C4,NOTE_F4,NOTE_G4,NOTE_C5,
  NOTE_C4,NOTE_F4,NOTE_G4,NOTE_C5,
  REST
};
int durations6[] = {4,4,4,2, 4,4,4,2, 4,4,4,2, 4,4,4,2, 4};
int len6 = sizeof(melody6)/sizeof(melody6[0]);

void sendHtml() {
  String html = all_HTML;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  server.send(200, "text/html; charset=UTF-8", html);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID);

  // softAP 이후 핀 설정
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);

  setupMelody(SPEAKER_PIN, RED_LED_PIN, YELLOW_LED_PIN, BLUE_LED_PIN);

  server.on("/", [](){ sendHtml(); });
  server.on("/melody", [](){
    if (!server.hasArg("id")) { server.send(400, "text/plain", "No ID"); return; }
    int id = server.arg("id").toInt();
    switch(id){
      case 1: playMelody(melody1, durations1, len1); break;
      case 2: playMelody(melody2, durations2, len2); break;
      case 3: playMelody(melody3, durations3, len3); break;
      case 4: playMelody(melody4, durations4, len4); break;
      case 5: playMelody(melody5, durations5, len5); break;
      case 6: playMelody(melody6, durations6, len6); break;
      default: break;
    }
    server.send(200, "text/plain; charset=UTF-8", "멜로디 재생 중");
  });
    server.begin();
  }

void loop() {
  server.handleClient();
}
