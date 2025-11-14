#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h> // Links2004
#include "main.h"             // main_HTML
#include "ledControl.h"       // led_HTML
#include "displayControl.h"   // display_HTML
#include "sensorDisplay.h"    // sensor_HTML
#include "melodyPlay.h"       // melody_HTML

// Drivers
#include "led.h"
#include "display.h"
#include "sensor.h"
#include "switch.h"
#include "melody.h"
#include "notes.h"

// ===== Wi-Fi AP =====
const char* AP_SSID = "홍길동";          // OPEN AP
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet (255,255,255,0);

// HTTP + WebSocket
WebServer server(80);
WebSocketsServer ws(81);  // ws://<ip>:81

// Sensor tick
unsigned long lastTick = 0;
const unsigned long INTERVAL_MS = 1000;

// Last sensor values
static float lastT = NAN, lastH = NAN;
static bool  lastSw = false;

// ---------- HTML helpers ----------
String fillCommon(const char* htmlRaw) {
  String html = htmlRaw;
  html.replace("%SSID%", AP_SSID);
  html.replace("%APIP%", WiFi.softAPIP().toString());
  return html;
}

void sendHtml(const char* htmlRaw) {
  String html = fillCommon(htmlRaw);
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "text/html; charset=UTF-8", html);
}

// ---------- HTTP routes ----------
void setupHttp() {
  server.on("/",           HTTP_GET, [](){ sendHtml(main_HTML);    });
  server.on("/led",        HTTP_GET, [](){ sendHtml(led_HTML);     });
  server.on("/display",    HTTP_GET, [](){ sendHtml(display_HTML); });
  server.on("/sensor",     HTTP_GET, [](){ sendHtml(sensor_HTML);  });
  server.on("/melody",     HTTP_GET, [](){ sendHtml(melody_HTML);  });

  server.onNotFound([](){
    server.send(404, "text/plain; charset=UTF-8", "404 Not Found");
  });

  server.begin();
  Serial.println("[HTTP] Server started");
}

// ---------- WS protocol ----------
// 수신 JSON 예:
// { "cmd":"led", "target":"red|yellow|blue", "val":0..255 }
// { "cmd":"display", "l1":"...", "l2":"...", "l3":"...", "l4":"..." }  // 일부만 보내도 됨
// { "cmd":"alarm" }  // 핀14 beep 0.5s
// { "cmd":"melody", "id":1..4 } // 스피커 33번 멜로디
#include <ArduinoJson.h>

void wsHandleText(uint8_t num, const String& s) {
  StaticJsonDocument<384> doc;
  DeserializationError err = deserializeJson(doc, s);
  if (err) return;

  const char* cmd = doc["cmd"] | "";
  if (!strcmp(cmd, "led")) {
    const char* tgt = doc["target"] | "";
    int val = doc["val"] | 0;
    val = constrain(val, 0, 255);
    if (!strcmp(tgt, "red"))    setRedLED(val);
    else if (!strcmp(tgt, "yellow")) setYellowLED(val);
    else if (!strcmp(tgt, "blue"))   setBlueLED(val);
    ws.sendTXT(num, "OK");
  }
  else if (!strcmp(cmd, "display")) {
    if (doc.containsKey("l1")) displaySetLine(1, doc["l1"].as<String>());
    if (doc.containsKey("l2")) displaySetLine(2, doc["l2"].as<String>());
    if (doc.containsKey("l3")) displaySetLine(3, doc["l3"].as<String>());
    if (doc.containsKey("l4")) displaySetLine(4, doc["l4"].as<String>());
    displayRender(); // 현재 저장된 라인들 바로 갱신
    ws.sendTXT(num, "OK");
  }
  else if (!strcmp(cmd, "alarm")) {
    beepOnce(500); // 0.5s beep on pin 14 (Active-Low)
    ws.sendTXT(num, "OK");
  }
  else if (!strcmp(cmd, "melody")) {
    int id = doc["id"] | 1;
    playMelodyId(id); // blocking 재생 (테스트용)
    ws.sendTXT(num, "OK");
  }
}

void onWsEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t len) {
  switch(type) {
    case WStype_CONNECTED: {
      // 접속 시 현재 상태 1회 전송
      String j = String("{\"t\":") + (isnan(lastT)?String("null"):String(lastT,1)) +
                 ",\"h\":" + (isnan(lastH)?String("null"):String(lastH,1)) +
                 ",\"sw\":" + (lastSw? "true":"false") + "}";
      ws.sendTXT(num, j);
    } break;
    case WStype_TEXT: {
      String s((char*)payload, len);
      wsHandleText(num, s);
    } break;
    default: break;
  }
}

// ---------- setup/loop ----------
void setup() {
  Serial.begin(115200);
  delay(150);

  // 1) AP 시작
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID);
  Serial.println("[AP] Started");
  Serial.print("[AP] SSID: "); Serial.println(AP_SSID);
  Serial.print("[AP] IP  : "); Serial.println(WiFi.softAPIP());

  // 2) softAP 이후 하드웨어 초기화!!!
  setupLED();                       // 3채널 LED (25/26/27, Active-Low, analogWrite)
  displayBegin();                   // U8g2 SSD1306 + 초기 4줄
  sensorBegin();                    // AHT20 (SDA=21, SCL=22)
  switchBegin(32, true);            // 스위치(핀32, 내부풀업)
  melodyBegin(14, 33, true);        // beeper=14(Active-Low), speaker=33(tone)

  // 3) HTTP
  setupHttp();

  // 4) WebSocket
  ws.begin();
  ws.onEvent(onWsEvent);
  Serial.println("[WS] WebSocket :81");
}

void loop() {
  server.handleClient();
  ws.loop();

  // 1초마다 센서+스위치 읽어 브로드캐스트
  unsigned long now = millis();
  if (now - lastTick >= INTERVAL_MS) {
    lastTick = now;

    // AHT20
    auto r = sensorRead();
    if (r.ok) { lastT = r.temperature_c; lastH = r.humidity_rh; }

    // 스위치
    lastSw = switchPressed();

    // JSON 생성 브로드캐스트
    String j = String("{\"t\":") + (isnan(lastT)?String("null"):String(lastT,1)) +
               ",\"h\":" + (isnan(lastH)?String("null"):String(lastH,1)) +
               ",\"sw\":" + (lastSw? "true":"false") + "}";
    ws.broadcastTXT(j);

    // 디스플레이는 여기서는 자동갱신하지 않음(사용자가 display 페이지에서 수동 전송)
  }
}
