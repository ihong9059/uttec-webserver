#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"
#include "switch.h"

WebServer server(80);

void handleRoot() {
  String html = all_HTML;
  html.replace("{{SSID}}", WiFi.softAPSSID());
  html.replace("{{SWITCH_STATE}}", getSwitchState() ? "켜짐" : "꺼짐");
  html.replace("{{SWITCH_ICON}}", getSwitchState() ? "🔴" : "⚪");
  server.send(200, "text/html", html);
}

void handleLED() {
  if (server.hasArg("color") && server.hasArg("action")) {
    String color = server.arg("color");
    String action = server.arg("action");
    
    if (action == "on") {
      if (color == "red") setRedLED(255);
      else if (color == "yellow") setYellowLED(255);
      else if (color == "blue") setBlueLED(255);
    }
    else if (action == "off") {
      if (color == "red") setRedLED(0);
      else if (color == "yellow") setYellowLED(0);
      else if (color == "blue") setBlueLED(0);
    }
    else if (action == "dim" && server.hasArg("value")) {
      int value = server.arg("value").toInt();
      if (color == "red") setRedLED(value);
      else if (color == "yellow") setYellowLED(value);
      else if (color == "blue") setBlueLED(value);
    }
    
    server.send(200, "text/plain", "OK");
  }
}

void handleSwitch() {
  String state = getSwitchState() ? "on" : "off";
  server.send(200, "text/plain", state);
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  // WiFi 설정 후에 LED와 스위치 설정
  setupLED();
  setupSwitch();
  
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.on("/switch", handleSwitch);
  server.begin();
}

void loop() {
  server.handleClient();
  updateSwitchState(); // 스위치 상태 주기적으로 확인
}