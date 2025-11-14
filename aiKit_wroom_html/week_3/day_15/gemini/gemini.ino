#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "main.h"
#include "ledControl.h"
#include "led.h"
#include "display.h"
#include "displayControl.h"
#include "sensor.h"
#include "sensorDisplay.h"
#include "switch.h"
#include "melody.h"
#include "melodyPlay.h"

// AP 설정
const char* ssid = "홍길동";
const char* password = "";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncWebSocket wsLed("/ws_led");
AsyncWebSocket wsDisplay("/ws_display");
AsyncWebSocket wsSensor("/ws_sensor");
AsyncWebSocket wsMelody("/ws_melody");

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_CONNECT){
        Serial.printf("클라이언트 접속 #%u\n", client->id());
        client->text(ssid);
    } else if (type == WS_EVT_DISCONNECT){
        Serial.printf("클라이언트 접속 해제 #%u\n", client->id());
    }
}

void onWsLedEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_DATA){
        if(len > 1){
            char color = (char)data[0];
            char *valueStr = (char*)malloc(len);
            memcpy(valueStr, data + 1, len - 1);
            valueStr[len-1] = '\0';
            int value = atoi(valueStr);
            free(valueStr);
            
            controlLed(color, value);
            Serial.printf("LED 제어: %c, 밝기: %d\n", color, value);
        }
    }
}

void onWsDisplayEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_DATA){
        char* payload = (char*)data;
        payload[len] = '\0';
        
        char* lines[4];
        int line_count = 0;
        char* token = strtok(payload, "||");
        while(token != NULL && line_count < 4){
            lines[line_count++] = token;
            token = strtok(NULL, "||");
        }

        while(line_count < 4){
            lines[line_count++] = "";
        }
        
        updateDisplay(lines[0], lines[1], lines[2], lines[3]);
        Serial.println("OLED 내용 업데이트");
    }
}

void onWsSensorEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_CONNECT){
        Serial.printf("센서 클라이언트 접속 #%u\n", client->id());
        float temp, hum;
        getSensorData(&temp, &hum);
        int switchState = getSwitchState();
        
        char sensorData[50];
        snprintf(sensorData, sizeof(sensorData), "%.1f,%.1f,%d", temp, hum, switchState);
        
        client->text(sensorData);
    }
}

void onWsMelodyEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_DATA){
        char* cmd = (char*)data;
        if(strncmp(cmd, "alarm", len) == 0){
            playAlarm();
            Serial.println("알람 연주");
        } else if (strncmp(cmd, "melody1", len) == 0){
            playMelody(1);
            Serial.println("멜로디 1 연주");
        } else if (strncmp(cmd, "melody2", len) == 0){
            playMelody(2);
            Serial.println("멜로디 2 연주");
        } else if (strncmp(cmd, "melody3", len) == 0){
            playMelody(3);
            Serial.println("멜로디 3 연주");
        } else if (strncmp(cmd, "melody4", len) == 0){
            playMelody(4);
            Serial.println("멜로디 4 연주");
        }
    }
}

void setup() {
    Serial.begin(115200);

    // AP 모드 설정
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP Address: ");
    Serial.println(IP);

    // 하드웨어 초기화 (AP 설정 이후)
    setupLeds();
    setupDisplay();
    setupSensor();
    setupSwitch();
    setupMelody();

    // 웹소켓 이벤트 핸들러 등록
    ws.onEvent(onWsEvent);
    wsLed.onEvent(onWsLedEvent);
    wsDisplay.onEvent(onWsDisplayEvent);
    wsSensor.onEvent(onWsSensorEvent);
    wsMelody.onEvent(onWsMelodyEvent);

    // 웹 서버 핸들러
    server.addHandler(&ws);
    server.addHandler(&wsLed);
    server.addHandler(&wsDisplay);
    server.addHandler(&wsSensor);
    server.addHandler(&wsMelody);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", main_HTML);
    });

    server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", led_HTML);
    });
    
    server.on("/display", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", display_HTML);
    });
    
    server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", sensor_HTML);
    });

    server.on("/melody", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", melody_HTML);
    });
    
    server.begin();
}

void loop() {
    static unsigned long lastSensorReadTime = 0;
    const unsigned long readInterval = 2000; // 2초마다 센서 값 전송

    if (millis() - lastSensorReadTime > readInterval) {
        float temp, hum;
        getSensorData(&temp, &hum);
        int switchState = getSwitchState();
        
        char sensorData[50];
        snprintf(sensorData, sizeof(sensorData), "%.1f,%.1f,%d", temp, hum, switchState);
        
        wsSensor.textAll(sensorData);

        lastSensorReadTime = millis();
    }
}










