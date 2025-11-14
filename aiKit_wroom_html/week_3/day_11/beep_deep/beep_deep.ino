#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"
#include "beep.h"

// WiFi AP 설정
const char* AP_SSID = "홍길동";
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

constexpr uint8_t PIN_BEEP = 14;
Beeper beeper(PIN_BEEP, true);

WebServer server(80);

void sendHtml() {
  String html = all_HTML;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  server.send(200, "text/html; charset=UTF-8", html);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID);

  setupLED();       // LED 초기화
  beeper.begin();   // Beeper 초기화

  server.on("/", [](){ sendHtml(); });
  server.on("/beep", [](){
    beeper.trigger(500); // 0.5초 동작
    server.send(200, "text/plain; charset=UTF-8", "삐—! 0.5초 동작");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  beeper.update();
}
