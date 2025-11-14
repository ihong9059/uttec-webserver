#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"

WebServer server(80);

// AP 설정
const char* ap_ssid = "홍광선";
const char* ap_password = ""; // 비밀번호 없음

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);
  
  Serial.println("WiFi AP 시작");
  Serial.print("AP SSID: ");
  Serial.println(ap_ssid);
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());

  // 웹 서버 라우팅 설정
  server.on("/", handleRoot);
  server.on("/getssid", handleGetSSID);
  
  server.begin();
  Serial.println("HTTP 서버 시작");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", my_HTML);
}

void handleGetSSID() {
  // 현재 AP의 SSID를 반환
  server.send(200, "text/plain", ap_ssid);
}
