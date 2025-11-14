#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "main.h"         // const char* main_HTML
#include "led.h"          // LED driver API
#include "ledControl.h"   // const char* led_HTML
#include "display.h"
#include "displayControl.h"

#include "switch.h"

#include "sensor.h"
#include "sensorDisplay.h"

#include "melody.h"
#include "melodyPlay.h"

// ====== Wi-Fi AP 설정 ======
static const char* AP_SSID = "홍길동";   // 비밀번호 없음(오픈 AP)

// ====== 서버 & 웹소켓 ======
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// 클라이언트에게 SSID 전송 헬퍼
static void sendSsidTo(uint32_t clientId) {
  ws.text(clientId, String("SSID:") + AP_SSID);
}

// 문자열 유틸
static bool startsWith(const String& s, const char* prefix) {
  return s.startsWith(prefix);
}

// WebSocket 이벤트 핸들러
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    // 접속 즉시 AP SSID를 보내 화면에 표시
    sendSsidTo(client->id());
  } else if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
      String msg;
      msg.reserve(len + 1);
      for (size_t i = 0; i < len; i++) msg += (char)data[i];

      // 프로토콜:
      // "PING"                      -> "PONG"
      // "GET_SSID"                  -> "SSID:<name>"
      // "LED:<RED|YELLOW|BLUE>:ON"  -> LED 켜기(LOW)
      // "LED:<...>:OFF"             -> LED 끄기(HIGH)
      // "PWM:<RED|YELLOW|BLUE>:<0~255>" -> 밝기(0=꺼짐,255=최대밝기)  ※ 내부에서 LOW=ON 보정

      if (msg == "PING") {
        client->text("PONG");
        return;
      }
      if (msg == "GET_SSID") {
        sendSsidTo(client->id());
        return;
      }

      if (msg == "SENSOR?") {
        float t = sensorGetTemperature();
        float h = sensorGetHumidity();
        String reply = "SENSOR:TEMP:" + String(t,1) + ":HUM:" + String(h,1);
        client->text(reply);
        return;
      }
      
      if (msg == "SWITCH?") {
        bool state = switchGetState();
        client->text(String("SWITCH:") + (state ? "ON" : "OFF"));
        return;
      }

      if (msg == "ALARM") {
        playAlarm();
        client->text("OK");
        return;
      }
      if (msg.startsWith("MELODY:")) {
        int id = msg.substring(7).toInt();
        playMelody(id);
        client->text("OK");
        return;
      }

      if (startsWith(msg, "LED:")) {
        // LED 제어
        // 예: LED:RED:ON
        int p1 = msg.indexOf(':', 4);
        if (p1 > 0) {
          String which = msg.substring(4, p1);
          String act   = msg.substring(p1 + 1);
          int pin = ledPinFromName(which.c_str()); // RED/YELLOW/BLUE -> 핀번호
          if (pin > 0) {
            if (act == "ON") {
              ledOn(pin);     // LOW=ON
              client->text("OK");
            } else if (act == "OFF") {
              ledOff(pin);    // HIGH=OFF
              client->text("OK");
            } else {
              client->text("ERR:UNKNOWN_LED_ACTION");
            }
          } else {
            client->text("ERR:UNKNOWN_LED_NAME");
          }
        } else {
          client->text("ERR:BAD_LED_CMD");
        }
        return;
      }

      if (startsWith(msg, "DISP:")) {
        // 예: DISP:1:문자열
        int p1 = msg.indexOf(':', 5);
        if (p1 > 0) {
          int line = msg.substring(5, p1).toInt();
          String txt = msg.substring(p1 + 1);
          displaySetLine(line, txt.c_str());
          client->text("OK");
        }
        return;
      }

      if (startsWith(msg, "PWM:")) {
        // 예: PWM:RED:128
        int p1 = msg.indexOf(':', 4);
        if (p1 > 0) {
          String which = msg.substring(4, p1);
          String valStr = msg.substring(p1 + 1);
          int value = constrain(valStr.toInt(), 0, 255);
          int pin = ledPinFromName(which.c_str());
          if (pin > 0) {
            ledSetBrightness(pin, value); // 내부에서 LOW=ON 보정함
            client->text("OK");
          } else {
            client->text("ERR:UNKNOWN_LED_NAME");
          }
        } else {
          client->text("ERR:BAD_PWM_CMD");
        }
        return;
      }

      client->text("ERR:UNKNOWN_CMD");
    }
  } else if (type == WS_EVT_DISCONNECT) {
    // noop
  } else if (type == WS_EVT_PONG) {
    // noop
  } else if (type == WS_EVT_ERROR) {
    // noop
  }
}


void setup() {
  Serial.begin(115200);
  delay(200);

  // 1) AP 모드 시작 (비밀번호 없음)
  WiFi.mode(WIFI_AP);
  // 비밀번호 길이가 8 미만이면 오픈 네트워크가 됩니다.
  bool ok = WiFi.softAP(AP_SSID);
  if (!ok) {
    Serial.println("[WiFi] softAP start failed!");
  } else {
    Serial.print("[WiFi] AP started. SSID: ");
    Serial.println(AP_SSID);
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.softAPIP());
  }

  // 2) (요청 조건) WiFi.softAP 이후에 LED 핀 초기화
  ledsInit();      // 내부에서 pinMode/초기 HIGH(=꺼짐), analogWrite 기본화
  displayInit();
  sensorInit();
  switchInit();
  melodyInit();

  // 3) WebSocket 준비
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // 4) 라우팅 (UTF-8 헤더)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html; charset=utf-8", main_HTML);
  });
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html; charset=utf-8", led_HTML);
  });

  server.on("/display", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html; charset=utf-8", display_HTML);
  });

  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html; charset=utf-8", sensor_HTML);
  });

  server.on("/melody", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html; charset=utf-8", melody_HTML);
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain; charset=utf-8", "페이지를 찾을 수 없습니다.");
  });

  server.begin();
}

bool lastSwitchState = false;

void loop() {
  // Async 서버 사용: loop에서 할 일 없음
  bool curState = switchGetState();   // true=눌림, false=해제
  if (curState != lastSwitchState) {
    lastSwitchState = curState;
    String msg = String("SWITCH:") + (curState ? "ON" : "OFF");
    ws.textAll(msg);   // 모든 연결된 클라이언트에 전송
  }  
}

