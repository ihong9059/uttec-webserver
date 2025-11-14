#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "sensor.h"
#include "myHtml.h"

// WiFi AP 설정
const char* ssid = "홍길동";
const char* password = ""; // 비밀번호 없음

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
Sensor sensor;

// HTML 페이지 제공
void handleRoot() {
  server.send(200, "text/html", aht20_HTML);
}

// WebSocket 이벤트 처리
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
  }
}

// 센서 데이터 JSON 형식으로 변환
String getSensorDataJSON() {
  String json = "{";
  json += "\"temperature\":" + String(sensor.getTemperature(), 1);
  json += ",\"humidity\":" + String(sensor.getHumidity(), 1);
  json += "}";
  return json;
}

void setup() {
  Serial.begin(115200);
  
  // AHT20 센서 초기화
  if (!sensor.begin()) {
    Serial.println("AHT20 센서를 찾을 수 없습니다!");
    while (1);
  }
  
  // WiFi AP 모드 설정
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  
  // 웹 서버 설정
  server.on("/", handleRoot);
  server.begin();
  
  // WebSocket 시작
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  Serial.println("HTTP server started");
  Serial.println("WebSocket server started on port 81");
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  // 센서 데이터 업데이트
  sensor.update();
  
  // 1초마다 모든 클라이언트에 데이터 전송
  static unsigned long lastSendTime = 0;
  if (millis() - lastSendTime > 1000) {
    String data = getSensorDataJSON();
    webSocket.broadcastTXT(data);
    lastSendTime = millis();
    
    // 시리얼 모니터 출력
    Serial.printf("Temperature: %.1f°C, Humidity: %.1f%%\n", 
                 sensor.getTemperature(), sensor.getHumidity());
  }
  
  delay(10);
}

