#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

WebServer server(80);

void handleRoot() {
  String html = all_HTML;
  html.replace("{{SSID}}", WiFi.softAPSSID());
  server.send(200, "text/html", html);
}

void handleLED() {
  if (server.hasArg("color") && server.hasArg("state")) {
    String color = server.arg("color");
    String state = server.arg("state");
    
    if (color == "red") {
      if (state == "on") redLedOn();
      else if (state == "off") redLedOff();
    }
    else if (color == "yellow") {
      if (state == "on") yellowLedOn();
      else if (state == "off") yellowLedOff();
    }
    else if (color == "blue") {
      if (state == "on") blueLedOn();
      else if (state == "off") blueLedOff();
    }
    
    server.send(200, "text/plain", "OK");
  }
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  // WiFi 설정 후에 pinMode 설정
  setupLED();
  
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.begin();
}

void loop() {
  server.handleClient();
}
