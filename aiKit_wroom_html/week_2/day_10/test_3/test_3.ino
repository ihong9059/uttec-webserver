#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"
#include "switch.h"

const char* ap_ssid = "HongGilDong";
const char* ap_password = "";

WebServer server(80);
LED led(25, 26, 27);        // Red, Yellow, Blue 핀
Switch mySwitch(32);        // 스위치 객체

void handleRoot() {
  String html = all_HTML;
  html.replace("{{AP_SSID}}", WiFi.softAPSSID());
  html.replace("{{SWITCH_STATE}}", mySwitch.isPressed() ? "PRESSED" : "RELEASED");
  html.replace("{{SWITCH_CLASS}}", mySwitch.isPressed() ? "switch-on" : "switch-off");
  
  // 템플릿 조건문 제거
  html.replace("{{#if SWITCH_STATE}}fa-check{{else}}fa-times{{/if}}", 
               mySwitch.isPressed() ? "fa-check" : "fa-times");
  
  server.send(200, "text/html", html);
}

void handleLED() {
  String color = server.arg("color");
  String action = server.arg("action");
  int value = server.arg("value").toInt();

  if (color == "red") {
    if (action == "on") led.setRed(true);
    else if (action == "off") led.setRed(false);
    else if (action == "dim") led.dimRed(value);
  }
  else if (color == "yellow") {
    if (action == "on") led.setYellow(true);
    else if (action == "off") led.setYellow(false);
    else if (action == "dim") led.dimYellow(value);
  }
  else if (color == "blue") {
    if (action == "on") led.setBlue(true);
    else if (action == "off") led.setBlue(false);
    else if (action == "dim") led.dimBlue(value);
  }

  server.send(200, "text/plain", "OK");
}

void handleSwitch() {
  String state = mySwitch.isPressed() ? "PRESSED" : "RELEASED";
  server.send(200, "text/plain", state);
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 설정
  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // LED 설정 (WiFi.softAP 이후에 수행)
  led.begin();

  // 스위치 설정
  mySwitch.begin();

  // 웹 서버 설정
  server.on("/", handleRoot);
  server.on("/control", handleLED);
  server.on("/switch", handleSwitch);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  mySwitch.read();
  delay(10);
}



