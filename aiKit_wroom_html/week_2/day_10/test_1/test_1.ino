#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

const char* ap_ssid = "HongGilDong";
const char* ap_password = "";

WebServer server(80);
LED led(25, 26, 27);  // Red, Yellow, Blue 핀
const int switchPin = 32;  // 스위치 핀

bool switchState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void handleRoot() {
  String html = all_HTML;
  html.replace("{{AP_SSID}}", WiFi.softAPSSID());
  html.replace("{{SWITCH_STATE}}", switchState ? "ON" : "OFF");
  html.replace("{{SWITCH_CLASS}}", switchState ? "switch-on" : "switch-off");
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
  String state = switchState ? "ON" : "OFF";
  server.send(200, "text/plain", state);
}

void readSwitch() {
  static bool lastButtonState = HIGH;
  bool reading = digitalRead(switchPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != switchState) {
      switchState = reading;
      Serial.print("Switch state changed to: ");
      Serial.println(switchState ? "ON" : "OFF");
    }
  }
  
  lastButtonState = reading;
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
  pinMode(switchPin, INPUT_PULLUP);
  switchState = digitalRead(switchPin);

  // 웹 서버 설정
  server.on("/", handleRoot);
  server.on("/control", handleLED);
  server.on("/switch", handleSwitch);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  readSwitch();
  delay(10);
  // this is error;
}

