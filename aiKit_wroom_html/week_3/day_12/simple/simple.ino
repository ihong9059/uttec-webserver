#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "melodyDriver.h"

// WiFi 설정
const char* ssid = "홍길동";
const char* password = NULL;

// LED 핀 설정
const int RED_LED_PIN = 25;
const int YELLOW_LED_PIN = 26;
const int BLUE_LED_PIN = 27;
const int SPEAKER_PIN = 33;

WebServer server(80);
MelodyDriver* melodyPlayer;

void handleRoot() {
  server.send(200, "text/html", all_HTML);
}

void handlePlay() {
  if (server.hasArg("melody")) {
    int melodyNumber = server.arg("melody").toInt();
    
    String melodyNames[] = {
      "도레미파솔라시도", 
      "생일축하곡", 
      "징글벨", 
      "오델로", 
      "반짝반짝 작은별", 
      "아리랑"
    };
    
    if (melodyNumber >= 1 && melodyNumber <= 6) {
      Serial.println("Playing melody: " + melodyNames[melodyNumber - 1]);
      
      switch(melodyNumber) {
        case 1:
          melodyPlayer->playMelody1();
          break;
        case 2:
          melodyPlayer->playMelody2();
          break;
        case 3:
          melodyPlayer->playMelody3();
          break;
        case 4:
          melodyPlayer->playMelody4();
          break;
        case 5:
          melodyPlayer->playMelody5();
          break;
        case 6:
          melodyPlayer->playMelody6();
          break;
      }
      
      server.send(200, "text/plain", "Melody " + String(melodyNumber) + " played");
    } else {
      server.send(400, "text/plain", "Invalid melody number");
    }
  } else {
    server.send(400, "text/plain", "Missing melody parameter");
  }
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정 (먼저 설정)
  WiFi.softAP(ssid, password);
  
  Serial.println("AP 모드 시작");
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());

  // 핀모드 설정 (softAP 이후에 설정)
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  // 모든 LED 끄기
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  
  // 멜로디 드라이버 초기화
  melodyPlayer = new MelodyDriver(SPEAKER_PIN, RED_LED_PIN, YELLOW_LED_PIN, BLUE_LED_PIN);

  // 웹 서버 라우팅 설정
  server.on("/", handleRoot);
  server.on("/play", handlePlay);
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Connect to WiFi '홍길동' and visit http://" + WiFi.softAPIP().toString());
}

void loop() {
  server.handleClient();
  delay(2); // 작은 딜레이로 안정성 향상
}