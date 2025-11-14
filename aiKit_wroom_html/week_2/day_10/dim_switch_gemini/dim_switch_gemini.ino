// Esp32wroom, 아두이노에서, wifi ap mode로 설정하고, ssid는 홍길동, password는 없는것으로 하여, 핸드폰이 접속하면, ap의 ssid를 보내서 화면에 나타나도록 하는 프로그램을 만들어 주세요. Web page부분은 const char* all_HTML = R”**( )**”; 의 형태로 만들어 주세요.page에서 한글이 깨지지 않게해주세요.
// Web page부분은 myHtml.h로 분리하여 만들어 주세요. 
// Red led는 25에, Yellow 26, Blue 27에 연결되어있고, low에서 Led가 On됩니다. Led를 구동하는 부분을 led.cpp와 led.h로 분리하여 만들어 주시고,
// Web page에는 red, yellow, blue led를 on/off하는 button을 만들어, red, yellow, blue led를 컨트롤 할수있도록 해주세요.
// Led port를 설정하는 pinMode는 WiFi.softAP함수 다음에 수행될수있도록 해주세요
// 각 led를 dimming하는 기능을 추가해 주세요. 특히 led 객체부분을 수정해서 진행해 주세요. Dimming시 analogWrite를 사용해 주세요. 현재 esp32 version에서는, ledcSetup등의 함수가 적용되지 않읍니다. 
// 초등학생들 대상으로 교육을 하고있으니, page를 직관적이고 알기쉽게 만들어 주세요.

// switch: 32를 연결하고, 상태를 나타내는, page를 만들어 주세요.
// 역시,switch에 관해서 driver file를 별도로 만들어 주세요. Switch.cpp와 switch.h로 분리해서 만들어 주세요

#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>
#include "myHtml.h"
#include "led.h"
#include "switch.h"

// 웹 서버 객체 생성 (포트 80)
WebServer server(80);

// AP 이름 설정
const char* ssid = "홍길동";

// LED 제어 객체 생성
LedControl redLed(25);
LedControl yellowLed(26);
LedControl blueLed(27);

// 스위치 제어 객체 생성
SwitchControl mySwitch(32);

// 웹 페이지를 전송하는 함수
void handleRoot() {
  server.send(200, "text/html", all_HTML);
}

// LED 제어를 처리하는 함수
void handleLed() {
  String ledColor = server.arg("color");
  String action = server.arg("action");
  
  if (ledColor == "red") {
    if (action == "on") redLed.turnOn();
    else if (action == "off") redLed.turnOff();
    else if (action == "dim") {
      int value = server.arg("value").toInt();
      redLed.setBrightness(value);
    }
  } else if (ledColor == "yellow") {
    if (action == "on") yellowLed.turnOn();
    else if (action == "off") yellowLed.turnOff();
    else if (action == "dim") {
      int value = server.arg("value").toInt();
      yellowLed.setBrightness(value);
    }
  } else if (ledColor == "blue") {
    if (action == "on") blueLed.turnOn();
    else if (action == "off") blueLed.turnOff();
    else if (action == "dim") {
      int value = server.arg("value").toInt();
      blueLed.setBrightness(value);
    }
  }
  
  // 페이지 새로고침
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

// 스위치 상태를 JSON으로 보내는 함수
void handleSwitchStatus() {
  String status = mySwitch.getState() ? "눌림" : "안 눌림";
  server.send(200, "application/json", "{\"status\": \"" + status + "\"}");
}

void setup() {
  Serial.begin(115200);

  // WiFi AP 모드 설정
  WiFi.softAP(ssid);
  Serial.print("AP 이름: ");
  Serial.println(ssid);

  // LED와 스위치 핀 설정 (WiFi 설정 이후에 실행)
  redLed.setupPin();
  yellowLed.setupPin();
  blueLed.setupPin();
  mySwitch.setupPin();

  // 웹 서버 경로 설정
  server.on("/", handleRoot);
  server.on("/control_led", HTTP_GET, handleLed);
  server.on("/switch_status", HTTP_GET, handleSwitchStatus);

  // 서버 시작
  server.begin();
  Serial.println("웹 서버 시작");
  Serial.print("접속 IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // 클라이언트 요청 처리
  server.handleClient();
}



