// Esp32wroom, 아두이노에서, wifi ap mode로 설정하고, ssid는 홍길동, password는 없는것으로 하여, 핸드폰이 접속하면, ap의 ssid를 보내서 화면에 나타나도록 하는 프로그램을 만들어 주세요. Web page부분은 const char* red_HTML = R”**( )**”; 의 형태로 만들어 주세요.한글이 깨지지 않게하세요.
// Web page부분은 myHtml.h로 분리하여 만들어 주세요. 
// Red led는 25에 연결되어있고, low에서 Led가 On됩니다. Led를 구동하는 부분을 led.cpp와 led.h로 분리하여 만들어 주시고,
// Web page에는 red led를 on/off하는 button을 만들어, red led를 컨트롤 할수있도록 해주세요.
// Led port를 설정하는 pinMode는 WiFi.softAP함수 다음에 수행될수있도록 해주세요
#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

// Set up web server on port 80
WebServer server(80);

// Set up the AP SSID
const char* ssid = "홍길동";

// LedControl object to manage the LED on GPIO 25.
// The constructor handles the pinMode setting.
LedControl led(25);

// Function to handle the root URL "/"
void handleRoot() {
  server.send(200, "text/html", myHtml);
}

// Function to handle the LED ON button
void handleLedOn() {
  led.turnOn();
  server.send(200, "text/plain", "LED ON");
  // Redirect back to the root page after the action is done.
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

// Function to handle the LED OFF button
void handleLedOff() {
  led.turnOff();
  server.send(200, "text/plain", "LED OFF");
  // Redirect back to the root page after the action is done.
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);

  // Set the ESP32 to AP mode with the specified SSID.
  WiFi.softAP(ssid);
  Serial.print("Access Point created with SSID: ");
  Serial.println(ssid);

  led.initRed();
  
  // Set up the LED pin *after* setting up the WiFi.
  // The LED is active low, so we initialize it to HIGH (off).
  digitalWrite(led.getPin(), HIGH);

  // Define web server routes
  server.on("/", handleRoot);
  server.on("/led_on", handleLedOn);
  server.on("/led_off", handleLedOff);

  // Start the server
  server.begin();
  Serial.println("Web server started.");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Handle client requests
  server.handleClient();
}


