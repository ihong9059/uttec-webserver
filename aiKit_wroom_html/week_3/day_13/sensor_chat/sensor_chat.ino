// ESP32_AP_AHT20_WS.ino
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>  // by Links2004
#include "myHtml.h"
#include "sensor.h"

// ===== Wi-Fi AP 설정 =====
const char* AP_SSID = "홍길동";       // 비밀번호 없음(OPEN)
const IPAddress local_IP(192,168,4,1);
const IPAddress gateway (192,168,4,1);
const IPAddress subnet  (255,255,255,0);

// HTTP + WebSocket
WebServer server(80);
WebSocketsServer ws(81);  // ws://<ip>:81

// 방송 타이머
unsigned long lastTick = 0;
const unsigned long INTERVAL_MS = 1000; // 1초

// HTML 전송 (UTF-8 + 플레이스홀더 치환)
void sendHtml() {
  String html = aht20_HTML;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "text/html; charset=UTF-8", html);
}

// WebSocket 이벤트 (여기서는 단순 브로드캐스트만 사용)
void onWsEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED: {
      // 접속 즉시 한 번 현재값 전송
      Aht20Reading r = sensorRead();
      if (r.ok) {
        String j = String("{\"t\":") + String(r.temperature_c,1) + ",\"h\":" + String(r.humidity_rh,1) + "}";
        ws.sendTXT(num, j);
      } else {
        ws.sendTXT(num, "AHT20 not ready");
      }
    } break;
    default: break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(150);

  // 1) AP 시작
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  bool ok = WiFi.softAP(AP_SSID);   // 비번 미지정 → Open AP
  Serial.println(ok ? "[AP] Started" : "[AP] Failed");
  Serial.print("[AP] SSID: "); Serial.println(AP_SSID);
  Serial.print("[AP] IP  : "); Serial.println(WiFi.softAPIP());

  // 2) !!! 요청사항: softAP 이후에 초기화 !!!
  sensorBegin(); // AHT20 초기화 (I2C: SDA=21, SCL=22)

  // 3) HTTP 라우트
  server.on("/", HTTP_GET, [](){ sendHtml(); });
  server.onNotFound([](){
    server.send(404, "text/plain; charset=UTF-8", "404 Not Found");
  });
  server.begin();
  Serial.println("[HTTP] Server started");

  // 4) WebSocket
  ws.begin();
  ws.onEvent(onWsEvent);
  Serial.println("[WS] WebSocket started on :81");
}

void loop() {
  server.handleClient();
  ws.loop();

  // 1초마다 센서 읽고 전체 클라이언트에 전송
  unsigned long now = millis();
  if (now - lastTick >= INTERVAL_MS) {
    lastTick = now;
    Aht20Reading r = sensorRead();
    if (r.ok) {
      String j = String("{\"t\":") + String(r.temperature_c,1) + ",\"h\":" + String(r.humidity_rh,1) + "}";
      ws.broadcastTXT(j);
    } else {
      ws.broadcastTXT("AHT20 not ready");
    }
  }
}
