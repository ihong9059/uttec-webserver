#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "myHtml.h"
#include "led.h"

WebServer server(80);

// LED 객체 생성
Led redLed(25, "red");     // GPIO 25 - RED
Led yellowLed(26, "yellow"); // GPIO 26 - YELLOW
Led blueLed(27, "blue");   // GPIO 27 - BLUE

// AP 설정
const char* ap_ssid = "홍길동";
const char* ap_password = ""; // 비밀번호 없음

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);
  
  // WiFi 설정 후 LED 핀모드 설정
  redLed.begin();
  yellowLed.begin();
  blueLed.begin();
  
  Serial.println("WiFi AP 시작");
  Serial.print("AP SSID: ");
  Serial.println(ap_ssid);
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());

  // 웹 서버 라우팅 설정
  server.on("/", handleRoot);
  server.on("/getssid", handleGetSSID);
  server.on("/led", handleLedControl);
  server.on("/ledstatus", handleLedStatus);
  
  server.begin();
  Serial.println("HTTP 서버 시작");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", all_HTML);
}

void handleGetSSID() {
  server.send(200, "text/plain", ap_ssid);
}

void handleLedControl() {
  if (server.hasArg("color") && server.hasArg("action")) {
    String color = server.arg("color");
    String action = server.arg("action");
    
    Led* led = getLedByColor(color);
    
    if (led != nullptr) {
      if (action == "on") {
        led->on();
        server.send(200, "text/plain", color + " LED ON");
      } 
      else if (action == "off") {
        led->off();
        server.send(200, "text/plain", color + " LED OFF");
      }
      else if (action == "toggle") {
        led->toggle();
        server.send(200, "text/plain", color + " LED TOGGLE");
      }
      else {
        server.send(400, "text/plain", "Invalid action");
      }
    } else {
      server.send(400, "text/plain", "Invalid LED color");
    }
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void handleLedStatus() {
  StaticJsonDocument<200> doc;
  doc["red"] = redLed.getState() ? "on" : "off";
  doc["yellow"] = yellowLed.getState() ? "on" : "off";
  doc["blue"] = blueLed.getState() ? "on" : "off";
  
  String response;
  serializeJson(doc, response);
  
  server.send(200, "application/json", response);
}

// LED 색상별 객체 반환 함수
Led* getLedByColor(String color) {
  if (color == "red") return &redLed;
  if (color == "yellow") return &yellowLed;
  if (color == "blue") return &blueLed;
  return nullptr;
}