#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"   // HTML 헤더 파일 포함

// WiFi AP 설정
const char* ap_ssid = "홍광선";   // AP SSID
const char* ap_password = "";    // 비밀번호 없음

// 웹 서버 객체 생성 (포트 80)
WebServer server(80);

// 루트 경로 처리
void handleRoot() {
  // AP SSID를 HTML에 삽입해서 보냄
  String page = String(my_HTML);
  page.replace("{{SSID}}", ap_ssid);   // placeholder {{SSID}} 치환
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  // WiFi AP 모드 시작
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("WiFi AP 모드 시작됨");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());

  // 웹 서버 라우트 설정
  server.on("/", handleRoot);

  // 서버 시작
  server.begin();
  Serial.println("HTTP 서버 시작됨");
}

void loop() {
  server.handleClient();
}

