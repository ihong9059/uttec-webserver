#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include "myHtml.h"

// WiFi 설정
const char* ssid = "홍길동";
const char* password = "";

// WebServer 및 WebSocket 설정
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// OLED 설정 (SDA: 21, SCL: 22)
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/U8X8_PIN_NONE);

// AHT20 센서 설정
Adafruit_AHTX0 aht;
sensors_event_t humidity_event, temp_event;

// 온도/습도 변수
float temperature = 0.0;
float humidity = 0.0;
String displayText = "웹에서 입력하세요";

void setup() {
  Serial.begin(115200);
  
  // UTF-8 출력 활성화
  setUTF8Locale();
  
  // I2C 시작
  Wire.begin(21, 22); // SDA, SCL
  
  // OLED 초기화
  u8g2.begin();
  u8g2.setFont(u8g2_font_unifont_t_korean2);
  u8g2.clearBuffer();
  u8g2.sendBuffer();
  
  // AHT20 센서 초기화
  if (!aht.begin(&Wire, 0, 0x38)) { // 기본 I2C 주소 0x38
    Serial.println("AHT20 센서를 찾을 수 없습니다. 연결을 확인하세요!");
    while (1) delay(10);
  }
  Serial.println("AHT20 센서 초기화 완료");
  
  // WiFi AP 모드 설정
  WiFi.softAP(ssid, password);
  Serial.println("AP 모드 시작");
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());
  
  // 웹 서버 설정
  server.on("/", []() {
    server.send(200, "text/html", aht20_HTML);
  });
  
  server.begin();
  
  // WebSocket 설정
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  // 초기 OLED 표시
  updateDisplay();
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  // 주기적으로 온도/습도 업데이트 (AHT20에서 읽기)
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) { // 2초마다 업데이트
    lastUpdate = millis();
    readAHT20();
    updateDisplay();
  }
}

void readAHT20() {
  // AHT20에서 온도와 습도 읽기
  aht.getEvent(&humidity_event, &temp_event);
  
  temperature = temp_event.temperature;
  humidity = humidity_event.relative_humidity;
  
  Serial.printf("온도: %.1f°C, 습도: %.1f%%\n", temperature, humidity);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] 연결 종료\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] 연결됨 from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        // 연결 시 현재 AP SSID 전송
        webSocket.sendTXT(num, "AP SSID: " + String(ssid));
        // 현재 온도/습도도 함께 전송
        String sensorData = "온도: " + String(temperature, 1) + "°C, 습도: " + String(humidity, 1) + "%";
        webSocket.sendTXT(num, sensorData);
      }
      break;
    case WStype_TEXT:
      {
        // 텍스트 메시지 수신
        String receivedText = "";
        for(int i = 0; i < length; i++) {
          receivedText += (char)payload[i];
        }
        Serial.printf("수신된 텍스트: %s\n", receivedText.c_str());
        
        // OLED 표시 텍스트 업데이트
        displayText = receivedText;
        updateDisplay();
        
        // 확인 응답 전송 (현재 온도/습도 포함)
        String response = "텍스트 수신됨: " + receivedText;
        response += "\n현재 온도: " + String(temperature, 1) + "°C";
        response += "\n현재 습도: " + String(humidity, 1) + "%";
        webSocket.sendTXT(num, response);
      }
      break;
  }
}

void updateDisplay() {
  u8g2.clearBuffer();
  
  // 1라인: "UTTEC Lab Ai"
  u8g2.setCursor(0, 15);
  u8g2.print("UTTEC Lab Ai");
  
  // 2라인: 온도
  u8g2.setCursor(0, 30);
  u8g2.print("온도: ");
  u8g2.print(temperature, 1);
  u8g2.print("°C");
  
  // 3라인: 습도
  u8g2.setCursor(0, 45);
  u8g2.print("습도: ");
  u8g2.print(humidity, 1);
  u8g2.print("%");
  
  // 4라인: 웹에서 입력한 내용
  u8g2.setCursor(0, 60);
  
  // OLED에 표시할 텍스트 길이 제한 (한글 8자 정도)
  String displayLine = displayText;
  if (displayLine.length() > 16) { // 한글은 2바이트 문자이므로
    displayLine = displayLine.substring(0, 16);
  }
  u8g2.print(displayLine);
  
  u8g2.sendBuffer();
}

void setUTF8Locale() {
  // UTF-8 로케일 설정 (한글 출력을 위해)
  setlocale(LC_ALL, "en_US.UTF-8");
}