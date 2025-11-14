#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "main.h"           // main_HTML
#include "led.h"
#include "ledControl.h"     // led_HTML
#include "display.h"
#include "displayControl.h" // display_HTML
#include "sensor.h"
#include "sensorDisplay.h"  // sensor_HTML
#include "switch.h"
#include "melody.h"
#include "melodyPlay.h"     // melody_HTML

// ====== 전역 ======
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// 주기적 브로드캐스트용
unsigned long lastBroadcast = 0;
const unsigned long BROADCAST_MS = 1000;

// 클라이언트로 SSID 알려주기
String getApSsid() { return String("홍길동"); }

// 웹소켓 송신 헬퍼(JSON)
void wsSendJson(uint32_t clientId, const JsonDocument& doc) {
  String out;
  serializeJson(doc, out);
  if (clientId == 0) {
    ws.textAll(out);
  } else {
    ws.text(clientId, out);
  }
}

// 수신 처리
void handleWsMessage(AsyncWebSocketClient *client, const String& msg) {
  // 간단한 프로토콜(JSON 권장)
  StaticJsonDocument<512> doc;
  DeserializationError err = deserializeJson(doc, msg);
  if (err) {
    // 텍스트 명령도 허용 (호환)
    if (msg == "GET_SSID") {
      StaticJsonDocument<128> res;
      res["type"] = "SSID";
      res["ssid"] = getApSsid();
      wsSendJson(client->id(), res);
    }
    return;
  }

  const char* type = doc["type"] | "";

  // === LED 제어 ===
  if (strcmp(type, "LED_SET") == 0) {
    String color = doc["color"] | "";
    int value = doc["value"] | 0;         // 0~255 (밝기)
    setLedValue(color, value);            // Low-Active 대응 내부 처리
    StaticJsonDocument<128> res;
    res["type"] = "LED_ACK";
    res["ok"] = true;
    wsSendJson(client->id(), res);
    return;
  }
  if (strcmp(type, "LED_OFFALL") == 0) {
    allLedOff();
    StaticJsonDocument<128> res;
    res["type"] = "LED_ACK";
    res["ok"] = true;
    wsSendJson(client->id(), res);
    return;
  }

  // === 디스플레이 제어 ===
  if (strcmp(type, "DISP_SET_LINES") == 0) {
    String l1 = doc["l1"] | "";
    String l2 = doc["l2"] | "";
    String l3 = doc["l3"] | "";
    String l4 = doc["l4"] | "";
    displaySetLines(l1, l2, l3, l4);
    StaticJsonDocument<128> res;
    res["type"] = "DISP_ACK";
    res["ok"] = true;
    wsSendJson(client->id(), res);
    return;
  }

  // === 센서 즉시읽기 ===
  if (strcmp(type, "SENSOR_NOW") == 0) {
    float t, h;
    readAHT20(t, h);
    StaticJsonDocument<128> res;
    res["type"] = "SENSOR_DATA";
    res["t"] = t;
    res["h"] = h;
    res["sw"] = readSwitch(); // 0/1
    wsSendJson(client->id(), res);
    return;
  }

  // === 알람/멜로디 ===
  if (strcmp(type, "ALARM_BEEP") == 0) {
    alarmBeep(); // beeper LOW 0.5s
    StaticJsonDocument<96> res;
    res["type"] = "ALARM_ACK";
    wsSendJson(client->id(), res);
    return;
  }
  if (strcmp(type, "MELODY_PLAY") == 0) {
    int no = doc["no"] | 1;
    playMelody(no); // 1~4
    StaticJsonDocument<96> res;
    res["type"] = "MELODY_ACK";
    wsSendJson(client->id(), res);
    return;
  }
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    // 접속 시 SSID 안내
    StaticJsonDocument<128> res;
    res["type"] = "SSID";
    res["ssid"] = getApSsid();
    wsSendJson(client->id(), res);
  } else if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
      String msg = String((char*)data, len);
      handleWsMessage(client, msg);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // I2C 및 주변 준비(라이브러리 내에서 Wire.begin(21,22) 수행)
  initDisplay();    // U8g2 + 초기 문구 세팅
  initSensor();     // AHT20
  initSwitch();     // GPIO32 입력풀업
  initMelody();     // tone 핀 준비(33), beeper(14) OFF

  // ===== Wi-Fi AP 시작 =====
  WiFi.mode(WIFI_AP);
  bool ok = WiFi.softAP("홍길동"); // open AP (no password)
  Serial.printf("AP start: %s, IP=%s\n", ok ? "OK" : "FAIL",
                WiFi.softAPIP().toString().c_str());

  // *** 요구사항: pinMode는 softAP 이후에 수행 ***
  initLedPins();    // LED 핀모드/초기상태 설정(모두 OFF=HIGH)

  // ===== Web Server & Routes =====
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // 페이지 라우팅(UTF-8 명시)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html; charset=utf-8", main_HTML);
  });
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html; charset=utf-8", led_HTML);
  });
  server.on("/display", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html; charset=utf-8", display_HTML);
  });
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html; charset=utf-8", sensor_HTML);
  });
  server.on("/melody", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html; charset=utf-8", melody_HTML);
  });

  server.begin();
}

void loop() {
  // 주기적으로 센서/스위치 브로드캐스트
  unsigned long now = millis();
  if (now - lastBroadcast >= BROADCAST_MS) {
    lastBroadcast = now;
    float t, h;
    readAHT20(t, h);
    StaticJsonDocument<128> res;
    res["type"] = "SENSOR_DATA";
    res["t"] = t;
    res["h"] = h;
    res["sw"] = readSwitch(); // 0/1
    wsSendJson(0, res);       // 모든 클라이언트
  }
}
