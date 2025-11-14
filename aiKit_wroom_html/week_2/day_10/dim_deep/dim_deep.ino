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

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  // WiFi 설정 후에 LED 설정
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