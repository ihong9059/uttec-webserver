#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "main.h"
#include "ledControl.h"
#include "led.h"
#include "displayControl.h"
#include "display.h"
#include "sensorDisplay.h"
#include "sensor.h"
#include "switch.h"
#include "melodyPlay.h"
#include "melody.h"
#include "notes.h"

// LED 객체 생성
LED redLED(25);
LED yellowLED(26);
LED blueLED(27);

// Display 객체 생성
Display oledDisplay;

// Sensor 객체 생성
Sensor aht20Sensor;

// Switch 객체 생성 (GPIO 32)
Switch mySwitch(32);

// Melody 객체 생성 (Beeper: 14, Speaker: 33)
Melody melodyPlayer(14, 33);

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// 멜로디 정의
const int happy_birthday[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

const int happy_birthday_durations[] = {
  4, 4, 2, 2, 2, 1,
  4, 4, 2, 2, 2, 1,
  4, 4, 2, 2, 2, 2, 2,
  4, 4, 2, 2, 2, 1
};

const int jingle_bells[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4
};

const int jingle_bells_durations[] = {
  2, 2, 4, 2, 2, 4,
  2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 1
};

const int twinkle[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

const int twinkle_durations[] = {
  2, 2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 1
};

const int ode_to_joy[] = {
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4
};

const int ode_to_joy_durations[] = {
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 1
};

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      {
        Serial.printf("[%u] Received: %s\n", num, payload);
        String message = String((char*)payload);
        
        // LED 제어 메시지 처리
        if(message.startsWith("red:")) {
          int value = message.substring(4).toInt();
          redLED.setBrightness(value);
          webSocket.sendTXT(num, "RED LED: " + String(value));
        }
        else if(message.startsWith("yellow:")) {
          int value = message.substring(7).toInt();
          yellowLED.setBrightness(value);
          webSocket.sendTXT(num, "YELLOW LED: " + String(value));
        }
        else if(message.startsWith("blue:")) {
          int value = message.substring(5).toInt();
          blueLED.setBrightness(value);
          webSocket.sendTXT(num, "BLUE LED: " + String(value));
        }
        // 디스플레이 제어 메시지 처리
        else if(message.startsWith("display:")) {
          String displayText = message.substring(8);
          int separator1 = displayText.indexOf('|');
          int separator2 = displayText.indexOf('|', separator1 + 1);
          int separator3 = displayText.indexOf('|', separator2 + 1);
          
          if(separator1 != -1 && separator2 != -1 && separator3 != -1) {
            String line1 = displayText.substring(0, separator1);
            String line2 = displayText.substring(separator1 + 1, separator2);
            String line3 = displayText.substring(separator2 + 1, separator3);
            String line4 = displayText.substring(separator3 + 1);
            
            oledDisplay.clear();
            oledDisplay.printLine(1, line1);
            oledDisplay.printLine(2, line2);
            oledDisplay.printLine(3, line3);
            oledDisplay.printLine(4, line4);
            oledDisplay.show();
            
            webSocket.sendTXT(num, "디스플레이 업데이트 완료");
          }
        }
        // 센서 데이터 요청 처리
        else if(message == "get_sensor") {
          aht20Sensor.update();
          float temp = aht20Sensor.getTemperature();
          float humidity = aht20Sensor.getHumidity();
          bool switchState = mySwitch.isPressed();
          
          String sensorData = "sensor:" + String(temp, 1) + "," + String(humidity, 1) + "," + (switchState ? "ON" : "OFF");
          webSocket.sendTXT(num, sensorData);
        }
        // 멜로디 제어 메시지 처리
        else if(message.startsWith("play:")) {
          String melodyName = message.substring(5);
          webSocket.sendTXT(num, "playing:" + melodyName);
          
          if(melodyName == "alarm") {
            melodyPlayer.beep(500);
            webSocket.sendTXT(num, "finished:alarm");
          }
          else if(melodyName == "happy_birthday") {
            melodyPlayer.playMelody(happy_birthday, happy_birthday_durations, 24);
            webSocket.sendTXT(num, "finished:happy_birthday");
          }
          else if(melodyName == "jingle_bells") {
            melodyPlayer.playMelody(jingle_bells, jingle_bells_durations, 25);
            webSocket.sendTXT(num, "finished:jingle_bells");
          }
          else if(melodyName == "twinkle") {
            melodyPlayer.playMelody(twinkle, twinkle_durations, 42);
            webSocket.sendTXT(num, "finished:twinkle");
          }
          else if(melodyName == "ode_to_joy") {
            melodyPlayer.playMelody(ode_to_joy, ode_to_joy_durations, 29);
            webSocket.sendTXT(num, "finished:ode_to_joy");
          }
        }
        // 멜로디 중지 메시지 처리
        else if(message == "stop:melody") {
          melodyPlayer.stop();
          webSocket.sendTXT(num, "stopped:melody");
        }
      }
      break;
  }
}

void handleRoot() {
  server.send(200, "text/html", main_HTML);
}

void handleLED() {
  server.send(200, "text/html", led_HTML);
}

void handleDisplay() {
  server.send(200, "text/html", display_HTML);
}

void handleSensor() {
  server.send(200, "text/html", sensor_HTML);
}

void handleMelody() {
  server.send(200, "text/html", melody_HTML);
}

void setup() {
  Serial.begin(115200);
  
  // WiFi AP 모드 설정
  WiFi.softAP("홍길동", NULL);
  
  Serial.println("AP 모드 시작");
  Serial.print("AP SSID: ");
  Serial.println("홍길동");
  Serial.print("AP IP 주소: ");
  Serial.println(WiFi.softAPIP());
  
  // LED 핀 모드 설정
  redLED.begin();
  yellowLED.begin();
  blueLED.begin();
  
  // 모든 LED 끄기
  redLED.off();
  yellowLED.off();
  blueLED.off();
  
  // OLED 디스플레이 초기화
  oledDisplay.begin();
  
  // AHT20 센서 초기화
  if (!aht20Sensor.begin()) {
    Serial.println("AHT20 센서를 찾을 수 없습니다!");
  } else {
    Serial.println("AHT20 센서 초기화 완료");
  }
  
  // 스위치 초기화
  mySwitch.begin();
  Serial.println("스위치 초기화 완료 (GPIO 32)");
  
  // 멜로디 플레이어 초기화
  melodyPlayer.begin();
  Serial.println("멜로디 플레이어 초기화 완료");
  
  // 웹 서버 라우팅 설정
  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.on("/display", handleDisplay);
  server.on("/sensor", handleSensor);
  server.on("/melody", handleMelody);
  
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  webSocket.loop();
  
  // 주기적으로 센서 데이터 업데이트
  static unsigned long lastSensorUpdate = 0;
  if (millis() - lastSensorUpdate > 1000) { // 1초마다
    aht20Sensor.update();
    
    // 스위치 상태가 변경되었는지 확인
    if (mySwitch.stateChanged()) {
      // 상태 변경 시 모든 클라이언트에 알림
      float temp = aht20Sensor.getTemperature();
      float humidity = aht20Sensor.getHumidity();
      bool switchState = mySwitch.isPressed();
      
      String sensorData = "sensor:" + String(temp, 1) + "," + String(humidity, 1) + "," + (switchState ? "ON" : "OFF");
      webSocket.broadcastTXT(sensorData);
    }
    
    lastSensorUpdate = millis();
  }
}



