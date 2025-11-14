#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"
#include "melody.h"
#include "notes.h"

WebServer server(80);

void handleRoot() {
  String html = all_HTML;
  html.replace("{{SSID}}", WiFi.softAPSSID());
  server.send(200, "text/html", html);
}

void handleMelody() {
  if (server.hasArg("number")) {
    int melodyNumber = server.arg("number").toInt();
    playMelody(melodyNumber);
    server.send(200, "text/plain", "Playing melody " + String(melodyNumber));
  }
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  // WiFi 설정 후에 LED와 스피커 설정
  setupLED();
  setupSpeaker();
  
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/melody", handleMelody);
  server.begin();
}

void loop() {
  server.handleClient();
  updateMelody(); // 멜로디 업데이트 처리
}
