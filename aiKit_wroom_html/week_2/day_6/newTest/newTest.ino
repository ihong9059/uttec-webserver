#include <WiFi.h>
#include <WebServer.h>

// WiFi AP 설정
const char* ssid = "홍광선";   // AP SSID
const char* password = "";    // 비밀번호 없음

// 웹 서버 객체 생성 (포트 80)
WebServer server(80);

// 웹 페이지 HTML
const char* GAME_HTML = R"====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 AP Test</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
    h1 { color: #2c3e50; }
    p  { font-size: 20px; }
  </style>
</head>
<body>
  <h1>ESP32 WiFi AP 모드</h1>
  <p>연결된 SSID: <b>홍광선</b></p>
</body>
</html>
)====";

// 루트 경로 처리
void handleRoot() {
  server.send(200, "text/html", GAME_HTML);
}

void setup() {
  Serial.begin(115200);

  // WiFi AP 모드 시작
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP 모드 시작");
  Serial.print("SSID: ");
  Serial.println(ssid);
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



