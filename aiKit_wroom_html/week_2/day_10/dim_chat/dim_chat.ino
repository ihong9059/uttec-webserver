// ESP32_AP_LED.ino
#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"
#include "led.h"

// ===== 설정 =====
const char* AP_SSID = "홍길동";   // 비번 없음 (open)
const IPAddress local_IP(192,168,4,1);   // 기본 AP IP (ESP32 기본: 192.168.4.1)
const IPAddress gateway(192,168,4,1);
const IPAddress subnet(255,255,255,0);

// 핀 매핑 (Active-Low)
constexpr uint8_t PIN_RED    = 25;
constexpr uint8_t PIN_YELLOW = 26;
constexpr uint8_t PIN_BLUE   = 27;

// LED 객체
Led ledRed(PIN_RED, true);
Led ledYellow(PIN_YELLOW, true);
Led ledBlue(PIN_BLUE, true);

WebServer server(80);

// 유틸: led 이름으로 참조 얻기
Led* getLedByName(const String& name) {
  if (name == "red")    return &ledRed;
  if (name == "yellow") return &ledYellow;
  if (name == "blue")   return &ledBlue;
  return nullptr;
}

// 유틸: UTF-8로 HTML 전송 + 플레이스홀더 치환
void sendHtmlWithInfo() {
  String html = all_HTML;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  server.sendHeader("Cache-Control", "no-store");
  server.sendHeader("Content-Type", "text/html; charset=UTF-8");
  server.send(200, "text/html; charset=UTF-8", html);
}

void setup() {
  // 시리얼(디버그)
  Serial.begin(115200);
  delay(200);

  // AP 시작 (OPEN)
  WiFi.mode(WIFI_AP);
  // 고정 IP를 쓰고 싶으면 아래 두 줄 유지(ESP32 기본도 192.168.4.1)
  WiFi.softAPConfig(local_IP, gateway, subnet);
  bool ok = WiFi.softAP(AP_SSID); // 비밀번호 미설정 = 개방형
  Serial.println(ok ? "[AP] Started" : "[AP] Failed");
  Serial.print("[AP] SSID: "); Serial.println(AP_SSID);
  Serial.print("[AP] IP  : "); Serial.println(WiFi.softAPIP());

  // !!! 요청사항: softAP 이후에 핀 설정 !!!
  ledRed.begin();
  ledYellow.begin();
  ledBlue.begin();

  // 라우트
  server.on("/", HTTP_GET, []() {
    sendHtmlWithInfo();
  });

  // 켜기
  server.on("/on", HTTP_GET, []() {
    String name = server.hasArg("led") ? server.arg("led") : "";
    Led* L = getLedByName(name);
    if (!L) { server.send(400, "text/plain; charset=UTF-8", "잘못된 LED 이름"); return; }
    L->on();
    server.send(200, "text/plain; charset=UTF-8", "OK");
  });

  // 끄기
  server.on("/off", HTTP_GET, []() {
    String name = server.hasArg("led") ? server.arg("led") : "";
    Led* L = getLedByName(name);
    if (!L) { server.send(400, "text/plain; charset=UTF-8", "잘못된 LED 이름"); return; }
    L->off();
    server.send(200, "text/plain; charset=UTF-8", "OK");
  });

  // 디밍 (0~255)
  server.on("/dim", HTTP_GET, []() {
    String name = server.hasArg("led") ? server.arg("led") : "";
    String v    = server.hasArg("val") ? server.arg("val") : "0";
    Led* L = getLedByName(name);
    if (!L) { server.send(400, "text/plain; charset=UTF-8", "잘못된 LED 이름"); return; }
    int val = constrain(v.toInt(), 0, 255);
    L->dim((uint8_t)val);
    server.send(200, "text/plain; charset=UTF-8", "OK");
  });

  // 기본 핸들러
  server.onNotFound([]() {
    server.send(404, "text/plain; charset=UTF-8", "404 Not Found");
  });

  server.begin();
  Serial.println("[HTTP] Server started");
}

void loop() {
  server.handleClient();
}
