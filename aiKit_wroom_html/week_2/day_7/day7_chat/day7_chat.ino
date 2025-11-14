#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"

// AP 설정
const char* ssid = "홍길동";
const char* password = "";

WebServer server(80);

// 루트 페이지 핸들러
void handleRoot() {
  String page = my_HTML;
  page.replace("__SSID__", ssid);                 // SSID 삽입
  page.replace("__IP__", WiFi.softAPIP().toString()); // IP 삽입
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  // 원하는 IP 세팅
  IPAddress local_ip(192,168,7,1);
  IPAddress gateway(192,168,7,1);
  IPAddress subnet(255,255,255,0);

  // AP 모드 시작
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("ESP32 AP 모드 시작됨");
  Serial.print("AP SSID: "); Serial.println(ssid);
  Serial.print("AP IP 주소: "); Serial.println(WiFi.softAPIP());

  // 웹 서버 라우트 등록
  server.on("/", handleRoot);
  server.begin();
  Serial.println("웹 서버 시작됨");
}

void loop() {
  server.handleClient();
}


