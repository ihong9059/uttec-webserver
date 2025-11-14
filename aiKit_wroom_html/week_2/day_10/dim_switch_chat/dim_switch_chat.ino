// ESP32_AP_LED.ino
#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"
#include "switch.h"

// ===== AP 설정 =====
const char* AP_SSID = "홍길동";   // 비번 없음
const IPAddress local_IP(192,168,4,1);
const IPAddress gateway(192,168,4,1);
const IPAddress subnet(255,255,255,0);

// 핀 매핑
constexpr uint8_t PIN_RED    = 25;
constexpr uint8_t PIN_YELLOW = 26;
constexpr uint8_t PIN_BLUE   = 27;
constexpr uint8_t PIN_SWITCH = 32;

// 객체
Led ledRed(PIN_RED, true);
Led ledYellow(PIN_YELLOW, true);
Led ledBlue(PIN_BLUE, true);
Switch mySwitch(PIN_SWITCH, true);

WebServer server(80);

// LED 선택 함수
Led* getLedByName(const String& name) {
  if (name == "red")    return &ledRed;
  if (name == "yellow") return &ledYellow;
  if (name == "blue")   return &ledBlue;
  return nullptr;
}

// HTML 전송
void sendHtmlWithInfo() {
  String html = all_HTML;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  server.sendHeader("Cache-Control", "no-store");
  server.sendHeader("Content-Type", "text/html; charset=UTF-8");
  server.send(200, "text/html; charset=UTF-8", html);
}

void setup() {
  Serial.begin(115200);
  delay(200);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  bool ok = WiFi.softAP(AP_SSID);
  Serial.println(ok ? "[AP] Started" : "[AP] Failed");
  Serial.print("[AP] SSID: "); Serial.println(AP_SSID);
  Serial.print("[AP] IP  : "); Serial.println(WiFi.softAPIP());

  // softAP 이후 핀 초기화
  ledRed.begin();
  ledYellow.begin();
  ledBlue.begin();
  mySwitch.begin();

  // 라우트
  server.on("/", HTTP_GET, [](){ sendHtmlWithInfo(); });

  server.on("/on", HTTP_GET, [](){
    String name = server.arg("led");
    Led* L = getLedByName(name);
    if (!L) { server.send(400, "text/plain; charset=UTF-8", "잘못된 LED 이름"); return; }
    L->on();
    server.send(200, "text/plain; charset=UTF-8", "OK");
  });

  server.on("/off", HTTP_GET, [](){
    String name = server.arg("led");
    Led* L = getLedByName(name);
    if (!L) { server.send(400, "text/plain; charset=UTF-8", "잘못된 LED 이름"); return; }
    L->off();
    server.send(200, "text/plain; charset=UTF-8", "OK");
  });

  server.on("/dim", HTTP_GET, [](){
    String name = server.arg("led");
    int val = constrain(server.arg("val").toInt(), 0, 255);
    Led* L = getLedByName(name);
    if (!L) { server.send(400, "text/plain; charset=UTF-8", "잘못된 LED 이름"); return; }
    L->dim((uint8_t)val);
    server.send(200, "text/plain; charset=UTF-8", "OK");
  });

  server.on("/switch", HTTP_GET, [](){
    String state = mySwitch.stateText();
    server.send(200, "text/plain; charset=UTF-8", state);
  });

  server.onNotFound([](){
    server.send(404, "text/plain; charset=UTF-8", "404 Not Found");
  });

  server.begin();
  Serial.println("[HTTP] Server started");
}

void loop() {
  server.handleClient();
}
