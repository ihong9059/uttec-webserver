#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

WebServer server(80);

// AP 정보
const char* ssid = "홍길도";   // AP SSID
const char* password = "";     // 비밀번호 없음

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", red_HTML);
}

void handleLedOn() {
  ledOn();
  server.send(200, "text/html; charset=UTF-8", red_HTML);
}

void handleLedOff() {
  ledOff();
  server.send(200, "text/html; charset=UTF-8", red_HTML);
}

void setup() {
  Serial.begin(115200);

  // WiFi AP 시작
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP 시작됨");
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());

  // WiFi.softAP() 이후 pinMode 설정
  initLed();

  // 서버 라우트 등록
  server.on("/", handleRoot);
  server.on("/ledon", handleLedOn);
  server.on("/ledoff", handleLedOff);

  server.begin();
  Serial.println("웹 서버 시작됨");
}

void loop() {
  server.handleClient();
}
