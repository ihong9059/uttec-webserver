// ESP32_AP_BEEP_LED.ino
#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h"

// 기존 LED 드라이버 (이전 대화에서 제공된 led.h/led.cpp 사용)
#include "led.h"

// 비프 드라이버
#include "beep.h"

// ===== AP 설정 =====
const char* AP_SSID = "홍길동";   // 비번 없음(OPEN)
const IPAddress local_IP(192,168,4,1);
const IPAddress gateway(192,168,4,1);
const IPAddress subnet(255,255,255,0);

// 핀 매핑
constexpr uint8_t PIN_RED   = 25; // Active-Low LED
constexpr uint8_t PIN_BEEP  = 14; // Active-Low Beeper

// 객체
Led    ledRed(PIN_RED, true);     // true = Active-Low
Beeper beeper(PIN_BEEP, true);    // true = Active-Low

WebServer server(80);

// HTML 전송 (UTF-8 + 플레이스홀더 치환)
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
  delay(150);

  // AP 시작 (비밀번호 없음)
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  bool ok = WiFi.softAP(AP_SSID);
  Serial.println(ok ? "[AP] Started" : "[AP] Failed");
  Serial.print("[AP] SSID: "); Serial.println(AP_SSID);
  Serial.print("[AP] IP  : "); Serial.println(WiFi.softAPIP());

  // !!! 요청사항: softAP 이후에 핀 초기화 !!!
  ledRed.begin();
  beeper.begin();
  beeper.attachBuddy(&ledRed); // 비프와 빨간 LED 동기화

  // 라우트
  server.on("/", HTTP_GET, [](){ sendHtmlWithInfo(); });

  // 0.5초 비프 (동시에 빨간 LED on/off)
  server.on("/beep", HTTP_GET, [](){
    beeper.trigger(500); // 500ms
    server.send(200, "text/plain; charset=UTF-8", "삐—! (0.5초 동작)");
  });

  server.onNotFound([](){
    server.send(404, "text/plain; charset=UTF-8", "404 Not Found");
  });

  server.begin();
  Serial.println("[HTTP] Server started");
}

void loop() {
  server.handleClient();
  beeper.update(); // 논블로킹 타이머 업데이트
}
