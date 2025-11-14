// ESP32_AP_AHT20_SSD1306_WS.ino
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>  // by Links2004
#include "myHtml.h"
#include "sensor.h"            // 이전에 만든 AHT20 드라이버 재사용 (sensor.h/sensor.cpp)
#include "display.h"           // SSD1306 + U8g2
#include <ArduinoJson.h>

// ===== Wi-Fi AP 설정 =====
const char* AP_SSID = "홍길동";           // 비밀번호 없음(OPEN)
const IPAddress local_IP(192,168,4,1);
const IPAddress gateway (192,168,4,1);
const IPAddress subnet  (255,255,255,0);

// HTTP + WebSocket
WebServer server(80);
WebSocketsServer ws(81);  // ws://<ip>:81

// 방송 타이머
unsigned long lastTick = 0;
const unsigned long INTERVAL_MS = 1000; // 1초

// 마지막 센서값(디스플레이 즉시 갱신용)
static float lastT = NAN, lastH = NAN;

// HTML 전송 (UTF-8 + 플레이스홀더 치환)
void sendHtml() {
  String html = aht20_HTML;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "text/html; charset=UTF-8", html);
}

// 간단한 JSON 파서: {"line4":"..."} 만 처리
void handleIncomingText(uint8_t clientNum, const String& msg) {
  // 매우 단순 파싱: "line4":" ... "
  int k = msg.indexOf("\"line4\"");
  if (k < 0) return;
  int q1 = msg.indexOf('"', k + 7);  // 키 다음의 "
  if (q1 < 0) return;
  int q2 = msg.indexOf('"', q1 + 1); // 값 시작의 "
  if (q2 < 0) return;
  int q3 = msg.indexOf('"', q2 + 1); // 값 끝의 "
  if (q3 < 0) return;

  String val = msg.substring(q2 + 1, q3); // UTF-8 문자열
  displaySetLine4(val);
  // 최신 센서값으로 즉시 화면 갱신
  if (!isnan(lastT) && !isnan(lastH)) {
    displayRender(lastT, lastH);
  }
  ws.sendTXT(clientNum, "OK");
}

void onWsEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED: {
      // 접속 즉시 현재값 보내기
      if (!isnan(lastT) && !isnan(lastH)) {
        String j = String("{\"t\":") + String(lastT,1) + ",\"h\":" + String(lastH,1) + "}";
        ws.sendTXT(num, j);
      } else {
        ws.sendTXT(num, "AHT20 not ready");
      }
    } break;

    case WStype_TEXT: {
      String s((char*)payload, length);
      Serial.print("WS Recv: "); Serial.println(s);

      StaticJsonDocument<256> doc;
      DeserializationError err = deserializeJson(doc, s);
      if (!err && doc.containsKey("line4")) {
        String txt = doc["line4"].as<String>();
        displaySetLine4(txt);
        if (!isnan(lastT) && !isnan(lastH)) {
          displayRender(lastT, lastH);
        }
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
  sensorBegin();   // AHT20 (I2C: SDA=21, SCL=22)
  displayBegin();  // SSD1306 + U8g2

  // 초기화시 첫 화면
  displayRender(NAN, NAN);

  // 3) HTTP
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

  // 1초마다 센서 읽기 & 브로드캐스트 & 디스플레이 갱신
  unsigned long now = millis();
  if (now - lastTick >= INTERVAL_MS) {
    lastTick = now;

    Aht20Reading r = sensorRead();
    if (r.ok) {
      lastT = r.temperature_c;
      lastH = r.humidity_rh;

      // 웹에 전송
      String j = String("{\"t\":") + String(lastT,1) + ",\"h\":" + String(lastH,1) + "}";
      ws.broadcastTXT(j);

      // 화면 업데이트
      displayRender(lastT, lastH);
    } else {
      ws.broadcastTXT("AHT20 not ready");
    }
  }
}
