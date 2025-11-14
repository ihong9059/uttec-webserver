#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

// Set LED pins
#define RED_LED_PIN 25
#define YELLOW_LED_PIN 26
#define BLUE_LED_PIN 27

// Set WiFi AP credentials
const char* ssid = "홍길동";
const char* password = "";

WebServer server(80);
Led leds(RED_LED_PIN, YELLOW_LED_PIN, BLUE_LED_PIN);

void handleRoot() {
  server.send(200, "text/html", all_HTML);
}

void handleLedControl() {
  if (server.hasArg("red")) {
    int value = server.arg("red").toInt();
    leds.setRed(value);
  }
  if (server.hasArg("yellow")) {
    int value = server.arg("yellow").toInt();
    leds.setYellow(value);
  }
  if (server.hasArg("blue")) {
    int value = server.arg("blue").toInt();
    leds.setBlue(value);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting AP mode...");

  WiFi.softAP(ssid, password);
  
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  leds.setup(); // LED 초기화 함수는 WiFi.softAP() 이후에 호출

  server.on("/", handleRoot);
  server.on("/led", handleLedControl);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
  // Dimming logic can be handled within the Led class or here
  leds.update();
}