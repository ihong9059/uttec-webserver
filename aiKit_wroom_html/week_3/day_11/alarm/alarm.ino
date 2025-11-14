#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "beeper.h"
#include "led.h"  // LED 헤더 추가

const char* ap_ssid = "HongGilDong";
const char* ap_password = "";

WebServer server(80);
Beeper beeper(14);  // Beeper 핀 14
LED led(25, 26, 27);  // Red, Yellow, Blue 핀 추가

void handleRoot() {
  String html = all_HTML;
  html.replace("{{AP_SSID}}", WiFi.softAPSSID());
  server.send(200, "text/html", html);
}

void handleBeep() {
  beeper.beep(500);  // 0.5초 동안 beep
  led.setRed(true);   // Red LED도 함께 ON
  server.send(200, "text/plain", "Beep sound played");
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 설정
  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Beeper 설정
  beeper.begin();

  // LED 설정 (WiFi.softAP 이후에 수행)
  led.begin();

  // 웹 서버 설정
  server.on("/", handleRoot);
  server.on("/beep", handleBeep);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  beeper.update();  // Beeper 상태 업데이트
  
  // Beeper가 멈추면 Red LED도 함께 멈춤
  if (!beeper.isActive()) {
    led.setRed(false);
  }
  
  delay(10);
}