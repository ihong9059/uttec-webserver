#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"

// AP 설정
const char* ap_ssid = "홍길동";
const char* ap_password = "";  // 비밀번호 없음

// 웹 서버 설정
WebServer server(80);
IPAddress local_IP(192, 168, 7, 1);
IPAddress gateway(192, 168, 7, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nESP32 AP 모드 설정 중...");

  // AP 모드 설정
  WiFi.mode(WIFI_AP);
  
  // 고정 IP 설정
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("AP IP 설정 실패!");
    return;
  }

  // AP 시작 (비밀번호 없음)
  if (WiFi.softAP(ap_ssid, ap_password)) {
    Serial.println("AP 모드 시작 완료");
    Serial.print("AP SSID: ");
    Serial.println(ap_ssid);
    Serial.print("AP IP 주소: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("AP 모드 시작 실패!");
    return;
  }

  // 웹 서버 라우팅 설정
  server.on("/", handleRoot);
  server.on("/getSSID", handleGetSSID);

  // 404 에러 핸들러
  server.onNotFound(handleNotFound);

  // 웹 서버 시작
  server.begin();
  Serial.println("HTTP 서버 시작됨");
  Serial.println("핸드폰에서 WiFi 네트워크 '홍길동'에 연결 후");
  Serial.println("브라우저에서 http://192.168.7.1 접속");
}

void loop() {
  server.handleClient();
}

// 루트 페이지 핸들러
void handleRoot() {
  server.send(200, "text/html", my_HTML);
}

// SSID 정보 요청 핸들러
void handleGetSSID() {
  server.send(200, "text/plain", ap_ssid);
}

// 404 에러 핸들러
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  
  server.send(404, "text/plain", message);
}