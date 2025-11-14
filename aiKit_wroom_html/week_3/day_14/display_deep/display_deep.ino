#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "myHtml.h"
#include "sensor.h"
#include "display.h"

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
String displayText = "안녕하세요!"; // 기본 표시 텍스트

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
    case WStype_TEXT:
      {
        String message = String((char*)payload);
        if (message.startsWith("text:")) {
          displayText = message.substring(5);
          setDisplayData(readTemperature(), readHumidity(), displayText);
          updateDisplay(); // 디스플레이 즉시 업데이트
          webSocket.broadcastTXT("display_updated");
          Serial.println("WebSocket으로 받은 텍스트: " + displayText);
        }
      }
      break;
  }
}

void handleRoot() {
  String html = aht20_HTML;
  html.replace("{{SSID}}", WiFi.softAPSSID());
  html.replace("{{DISPLAY_TEXT}}", displayText);
  server.send(200, "text/html", html);
}

void handleUpdateDisplay() {
  if (server.hasArg("text")) {
    displayText = server.arg("text");
    setDisplayData(readTemperature(), readHumidity(), displayText);
    updateDisplay(); // 디스플레이 업데이트
    server.send(200, "text/plain", "OK");
    Serial.println("HTTP로 받은 텍스트: " + displayText);
  }
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  // WiFi 설정 후에 센서와 디스플레이 설정
  setupSensor();
  setupDisplay();
  
  // 초기 데이터 설정
  setDisplayData(readTemperature(), readHumidity(), displayText);
  
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/update", handleUpdateDisplay);
  server.begin();
  
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  // 초기 디스플레이 업데이트
  updateDisplay();
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 2000) { // 2초마다 업데이트
    lastUpdate = millis();
    
    // 센서 데이터 읽기
    float temperature = readTemperature();
    float humidity = readHumidity();
    
    // 디스플레이 데이터 업데이트 (텍스트는 유지)
    setDisplayData(temperature, humidity, displayText);
    
    // WebSocket으로 데이터 전송
    String data = "temp:" + String(temperature, 1) + ",hum:" + String(humidity, 1);
    webSocket.broadcastTXT(data);
    
    // 디스플레이 업데이트
    updateDisplay();
    
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
}




