

#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

WebServer server(80);

void handleRoot() {
  String html = red_HTML;
  html.replace("{{SSID}}", WiFi.softAPSSID());
  server.send(200, "text/html", html);
}

void handleLED() {
  if (server.hasArg("state")) {
    String state = server.arg("state");
    if (state == "on") {
      ledOn();
    } else if (state == "off") {
      ledOff();
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