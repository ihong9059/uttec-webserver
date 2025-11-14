// --- 라이브러리 및 헤더 파일 포함 ---
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <U8g2lib.h>

#include "main.h"
#include "led.h"
#include "display.h"
#include "sensor.h"
#include "switch.h"
#include "melody.h"
#include "notes.h"
#include "ledControl.h"
#include "displayControl.h"
#include "sensorDisplay.h"
#include "melodyPlay.h"

// --- 전역 변수 및 객체 ---
const char* ssid = "홍길동";
const char* password = ""; // 비밀번호 없음

AsyncWebServer server(80);
WebSocketsServer ws(81);
Adafruit_AHTX0 aht;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// --- WebSocket 이벤트 핸들러 ---
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_CONNECTED) {
    ws.sendTXT(num, ssid);
  } else if (type == WStype_TEXT) {
    String message = (char*)payload;

    if (message.startsWith("toggle_led:")) {
      String color = message.substring(11);
      int pin = 0;
      if (color == "red") pin = LED_RED_PIN;
      else if (color == "yellow") pin = LED_YELLOW_PIN;
      else if (color == "blue") pin = LED_BLUE_PIN;
      
      if (pin != 0) {
        static bool led_states[3] = {false, false, false};
        int index = (pin == LED_RED_PIN) ? 0 : (pin == LED_YELLOW_PIN) ? 1 : 2;
        led_states[index] = !led_states[index];
        led_control(pin, led_states[index]);
      }
    } else if (message.startsWith("oled_update:")) {
      String text_data = message.substring(12);
      String lines[4];
      int last_idx = 0;
      for (int i = 0; i < 3; ++i) {
        int next_idx = text_data.indexOf('|', last_idx);
        if (next_idx != -1) {
          lines[i] = text_data.substring(last_idx, next_idx);
          last_idx = next_idx + 1;
        } else {
          lines[i] = text_data.substring(last_idx);
          last_idx = text_data.length();
          break;
        }
      }
      lines[3] = text_data.substring(last_idx);
      display_update_text(lines[0].c_str(), lines[1].c_str(), lines[2].c_str(), lines[3].c_str());
    } else if (message == "request_sensor_data") {
      float temp = get_temperature(aht);
      float humi = get_humidity(aht);
      bool switch_state = get_switch_state();
      
      String json = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(humi) + ", \"switch_state\": \"" + (switch_state ? "ON" : "OFF") + "\"}";
      ws.sendTXT(num, json);
    } else if (message.startsWith("play_melody:")) {
      String melody_name = message.substring(12);
      if (melody_name == "alarm") {
        play_tone(BEEPER_PIN, 1000, 500);
      } else if (melody_name == "melody1") {
        play_melody_1(SPEAKER_PIN);
      } else if (melody_name == "melody2") {
        play_melody_2(SPEAKER_PIN);
      } else if (melody_name == "melody3") {
        play_melody_3(SPEAKER_PIN);
      } else if (melody_name == "melody4") {
        play_melody_4(SPEAKER_PIN);
      }
    }
  }
}

// --- setup() 함수 ---
void setup() {
  Serial.begin(115200);

  // WiFi AP 설정
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP 주소: ");
  Serial.println(IP);

  // 드라이버 초기화
  led_init();
  switch_init();
  display_init(u8g2);
  sensor_init(aht);
  melody_init();
  
  // 웹 서버 핸들러 설정
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", main_HTML);
  });
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", led_HTML);
  });
  server.on("/display", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", display_HTML);
  });
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", sensor_HTML);
  });
  server.on("/melody", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", melody_HTML);
  });

  // 웹소켓 이벤트 핸들러 등록
  ws.onEvent(onWebSocketEvent);

  // 서버 시작
  server.begin();
  ws.begin();
}

// --- loop() 함수 ---
void loop() {
  ws.loop();
}