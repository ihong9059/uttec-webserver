#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "sensor.h"
#include "display.h"
#include "myHtml.h"

// WiFi AP 설정
const char* ssid = "홍길동";
const char* password = ""; // 비밀번호 없음

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
Sensor sensor;
Display display;

String userInput = "";

// HTML 페이지 제공
void handleRoot() {
  server.send(200, "text/html", aht20_HTML);
}

// WebSocket 이벤트 처리
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] 연결 해제!\n", num);
      break;
      
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] 연결됨 from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        // 연결 즉시 데이터 전송
        sendSensorData(num);
      }
      break;
      
    case WStype_TEXT:
      {
        String text = String((char*)payload);
        Serial.printf("[%u] 수신: %s\n", num, text);
        
        if (text == "getData") {
          // 센서 데이터 전송
          sendSensorData(num);
        } 
        else if (text.startsWith("{")) {
          // JSON 메시지 처리
          DynamicJsonDocument doc(256);
          DeserializationError error = deserializeJson(doc, payload);
          
          if (!error) {
            String messageType = doc["type"];
            
            if (messageType == "display") {
              userInput = doc["text"].as<String>();
              Serial.println("사용자 입력: " + userInput);
              
              // 디스플레이 업데이트
              display.displayMessage(sensor.getTemperature(), sensor.getHumidity(), userInput);
              
              // 응답 전송
              String response = "{\"type\":\"message\",\"text\":\"텍스트가 표시됩니다: " + userInput + "\"}";
              webSocket.sendTXT(num, response);
            }
          }
        }
      }
      break;
  }
}

// 센서 데이터 전송
void sendSensorData(uint8_t num) {
  float temperature = sensor.getTemperature();
  float humidity = sensor.getHumidity();
  
  String json = "{";
  json += "\"type\":\"sensor\",";
  json += "\"temperature\":" + String(temperature, 1);
  json += ",\"humidity\":" + String(humidity, 1);
  json += "}";
  webSocket.sendTXT(num, json);
}

// 모든 클라이언트에 센서 데이터 브로드캐스트
void broadcastSensorData() {
  float temperature = sensor.getTemperature();
  float humidity = sensor.getHumidity();
  
  String json = "{";
  json += "\"type\":\"sensor\",";
  json += "\"temperature\":" + String(temperature, 1);
  json += ",\"humidity\":" + String(humidity, 1);
  json += "}";
  webSocket.broadcastTXT(json);
}

void setup() {
  Serial.begin(115200);
  Serial.println("시스템 시작...");
  
  // 디스플레이 초기화
  display.begin();
  display.setLine1("UTTEC Lab Ai");
  display.setLine2("Temp: --.-C");
  display.setLine3("Humi: --.-%");
  display.setLine4("시작중...");
  
  // AHT20 센서 초기화
  Serial.println("AHT20 센서 초기화 중...");
  if (sensor.begin()) {
    Serial.println("AHT20 센서 초기화 성공!");
    display.setLine4("센서 준비됨");
  } else {
    Serial.println("AHT20 센서 없음, 더미 데이터 사용");
    display.setLine4("센서 없음");
  }
  
  // WiFi AP 모드 설정
  Serial.println("WiFi AP 설정 중...");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  
  display.setLine4("IP: " + IP.toString());
  delay(2000);
  
  // 웹 서버 설정
  server.on("/", handleRoot);
  server.begin();
  
  // WebSocket 시작
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  Serial.println("HTTP server started");
  Serial.println("WebSocket server started on port 81");
  display.setLine4("웹서버 대기중");
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  // 센서 데이터 업데이트
  sensor.update();
  
  // 2초마다 모든 클라이언트에 데이터 전송 및 디스플레이 업데이트
  static unsigned long lastUpdateTime = 0;
  if (millis