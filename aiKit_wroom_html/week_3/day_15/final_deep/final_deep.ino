#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "main.h"
#include "ledControl.h"
#include "displayControl.h"
#include "sensorDisplay.h"
#include "melodyPlay.h"
#include "led.h"
#include "display.h"
#include "sensor.h"
#include "switch.h"
#include "melody.h"

WebServer server(80);
WebSocketsServer webSocket(81);

void handleRoot() {
  String html = main_HTML;
  html.replace("{{SSID}}", WiFi.softAPSSID());
  server.send(200, "text/html", html);
}

void handleLED() {
  server.send(200, "text/html", led_HTML);
}

void handleLEDControl() {
  if (server.hasArg("color") && server.hasArg("action")) {
    String color = server.arg("color");
    String action = server.arg("action");
    
    if (color == "red") {
      setRedLED(action == "on" ? 255 : 0);
    } else if (color == "yellow") {
      setYellowLED(action == "on" ? 255 : 0);
    } else if (color == "blue") {
      setBlueLED(action == "on" ? 255 : 0);
    }
    server.send(200, "text/plain", "OK");
  }
}

void handleDisplay() {
  server.send(200, "text/html", display_HTML);
}

void handleDisplayControl() {
  if (server.method() == HTTP_POST) {
    String body = server.arg("plain");
    // 간단한 JSON 파싱
    String line2 = getJsonValue(body, "line2");
    String line3 = getJsonValue(body, "line3");
    String line4 = getJsonValue(body, "line4");
    
    setDisplayText(line2, line3, line4);
    server.send(200, "text/plain", "OK");
  }
}

String getJsonValue(String json, String key) {
  int keyStart = json.indexOf("\"" + key + "\"") + key.length() + 3;
  int keyEnd = json.indexOf("\"", keyStart);
  return json.substring(keyStart, keyEnd);
}

void handleSensor() {
  server.send(200, "text/html", sensor_HTML);
}

void handleSensorData() {
  float temperature = readTemperature();
  float humidity = readHumidity();
  bool switchState = readSwitch();
  
  String json = "{\"temperature\":" + String(temperature, 1) + 
                ",\"humidity\":" + String(humidity, 1) + 
                ",\"switchState\":" + String(switchState ? "true" : "false") + "}";
  server.send(200, "application/json", json);
}

void handleMelody() {
  server.send(200, "text/html", melody_HTML);
}

void handlePlayMelody() {
  if (server.hasArg("type")) {
    String type = server.arg("type");
    if (type == "alarm") {
      playAlarm();
    } else if (type == "happy") {
      playMelody(1);
    } else if (type == "birthday") {
      playMelody(2);
    } else if (type == "star") {
      playMelody(3);
    } else if (type == "game") {
      playMelody(4);
    }
    server.send(200, "text/plain", "OK");
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // WebSocket 이벤트 처리 (필요시 구현)
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  // WiFi 설정 후에 각 드라이버 설정
  setupLED();
  setupDisplay();
  setupSensor();
  setupSwitch();
  setupMelody();
  
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // 웹 페이지 라우팅
  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.on("/ledControl", handleLEDControl);
  server.on("/display", handleDisplay);
  server.on("/displayControl", handleDisplayControl);
  server.on("/sensor", handleSensor);
  server.on("/sensorData", handleSensorData);
  server.on("/melody", handleMelody);
  server.on("/playMelody", handlePlayMelody);
  
  server.begin();
  
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  // 주기적인 작업이 필요하면 여기에 추가
  // 예: 2초마다 디스플레이 업데이트 등
}