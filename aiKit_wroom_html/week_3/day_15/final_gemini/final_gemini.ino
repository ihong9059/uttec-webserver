// --- 라이브러리 포함 ---
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <U8g2lib.h>

// --- 전역 변수 및 상수 ---
const char* ssid = "홍길동";

// LED 핀 정의
#define LED_RED_PIN 25
#define LED_YELLOW_PIN 26
#define LED_BLUE_PIN 27

// Beeper 및 Speaker 핀 정의
#define BEEPER_PIN 14
#define SPEAKER_PIN 33

// 스위치 핀 정의
#define SWITCH_PIN 32

// I2C 핀 정의
#define SDA_PIN 21
#define SCL_PIN 22

// 웹 서버 및 웹소켓 객체
AsyncWebServer server(80);
WebSocketsServer ws(81);

// AHT20 센서 객체
Adafruit_AHTX0 aht;

// OLED 디스플레이 객체 (I2C)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// --- notes.h (멜로디 음계 정의) ---
// 아두이노의 tone() 함수를 위한 주파수 값 정의
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define REST      0

// --- main.h (메인 웹 페이지) ---
const char* main_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>UTTEC Lab Ai</title>
    <style>
        body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
        .container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
        h1 { color: #007bff; margin-bottom: 20px; }
        .ssid-box { background-color: #e2f0ff; padding: 15px; border-radius: 10px; margin-bottom: 20px; font-size: 1.2em; font-weight: bold; }
        .button-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
        .button-grid button { padding: 20px; font-size: 1em; font-weight: bold; border: none; border-radius: 10px; color: white; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }
        .button-grid button:hover { transform: translateY(-3px); box-shadow: 0 6px 10px rgba(0,0,0,0.15); }
        .led-btn { background-color: #ff6347; }
        .oled-btn { background-color: #4CAF50; }
        .sensor-btn { background-color: #2196F3; }
        .melody-btn { background-color: #9c27b0; }
        .footer { margin-top: 20px; font-size: 0.9em; color: #777; }
    </style>
</head>
<body>
    <div class="container">
        <h1>UTTEC Lab Ai</h1>
        <div class="ssid-box">
            <span>AP SSID:</span> <span id="ssid-name">...</span>
        </div>
        <div class="button-grid">
            <button class="led-btn" onclick="window.location.href='/led'">LED 제어</button>
            <button class="oled-btn" onclick="window.location.href='/display'">OLED 제어</button>
            <button class="sensor-btn" onclick="window.location.href='/sensor'">센서/스위치</button>
            <button class="melody-btn" onclick="window.location.href='/melody'">멜로디 연주</button>
        </div>
        <div class="footer">
            <p>직관적으로 쉽게 사용해보세요!</p>
        </div>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
        ws.onmessage = function(event) {
            document.getElementById('ssid-name').innerText = event.data;
        };
    </script>
</body>
</html>
)**";

// --- ledControl.h (LED 제어 웹 페이지) ---
const char* led_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED 제어</title>
    <style>
        body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
        .container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
        h1 { color: #ff6347; margin-bottom: 20px; }
        .led-buttons { display: flex; justify-content: space-around; flex-wrap: wrap; margin-bottom: 20px; }
        .led-buttons button { padding: 15px 30px; font-size: 1.2em; font-weight: bold; border: none; border-radius: 10px; color: white; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 4px 6px rgba(0,0,0,0.1); margin: 10px; }
        .led-buttons button:hover { transform: translateY(-3px); box-shadow: 0 6px 10px rgba(0,0,0,0.15); }
        .led-red { background-color: #ff4136; }
        .led-yellow { background-color: #ffc400; }
        .led-blue { background-color: #0074d9; }
        .status-box { background-color: #e8f5e9; padding: 15px; border-radius: 10px; }
        .status-box p { margin: 0; font-weight: bold; }
        .back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>LED 제어</h1>
        <div class="led-buttons">
            <button class="led-red" onclick="toggleLED('red')">빨강 LED</button>
            <button class="led-yellow" onclick="toggleLED('yellow')">노랑 LED</button>
            <button class="led-blue" onclick="toggleLED('blue')">파랑 LED</button>
        </div>
        <div class="status-box">
            <p>LED 상태를 변경하려면 버튼을 누르세요.</p>
        </div>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
        function toggleLED(color) {
            ws.send("toggle_led:" + color);
        }
    </script>
</body>
</html>
)**";

// --- displayControl.h (OLED 제어 웹 페이지) ---
const char* display_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OLED 제어</title>
    <style>
        body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
        .container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
        h1 { color: #4CAF50; margin-bottom: 20px; }
        .input-group { margin-bottom: 15px; }
        .input-group label { display: block; margin-bottom: 5px; font-weight: bold; }
        .input-group input { width: 80%; padding: 8px; border: 1px solid #ccc; border-radius: 5px; }
        #send-btn { padding: 10px 20px; background-color: #4CAF50; color: white; border: none; border-radius: 10px; cursor: pointer; transition: background-color 0.2s; margin-top: 10px; }
        #send-btn:hover { background-color: #45a049; }
        .back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>OLED 제어</h1>
        <p>OLED에 출력할 내용을 입력하고 버튼을 누르세요.</p>
        <div class="input-group">
            <label for="line1">1번째 줄:</label>
            <input type="text" id="line1" value="UTTEC Lab Ai">
        </div>
        <div class="input-group">
            <label for="line2">2번째 줄:</label>
            <input type="text" id="line2" value="2번째 line">
        </div>
        <div class="input-group">
            <label for="line3">3번째 줄:</label>
            <input type="text" id="line3" value="3번째 line">
        </div>
        <div class="input-group">
            <label for="line4">4번째 줄:</label>
            <input type="text" id="line4" value="환영 합니다">
        </div>
        <button id="send-btn" onclick="sendText()">내용 보내기</button>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
        function sendText() {
            var text1 = document.getElementById('line1').value;
            var text2 = document.getElementById('line2').value;
            var text3 = document.getElementById('line3').value;
            var text4 = document.getElementById('line4').value;
            var message = `oled_update:${text1}|${text2}|${text3}|${text4}`;
            ws.send(message);
        }
    </script>
</body>
</html>
)**";

// --- sensorDisplay.h (센서 및 스위치 웹 페이지) ---
const char* sensor_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>센서/스위치 상태</title>
    <style>
        body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
        .container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
        h1 { color: #2196F3; margin-bottom: 20px; }
        .data-box { background-color: #e3f2fd; padding: 15px; border-radius: 10px; margin-bottom: 20px; }
        .data-box p { margin: 10px 0; font-size: 1.2em; }
        .data-box .label { font-weight: bold; color: #004d99; }
        .back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>센서/스위치 상태</h1>
        <div class="data-box">
            <p><span class="label">온도:</span> <span id="temperature">...</span> °C</p>
            <p><span class="label">습도:</span> <span id="humidity">...</span> %</p>
            <p><span class="label">스위치:</span> <span id="switch-state">...</span></p>
        </div>
        <p>상태가 5초마다 자동으로 갱신됩니다.</p>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
        ws.onmessage = function(event) {
            var data = JSON.parse(event.data);
            document.getElementById('temperature').innerText = data.temperature.toFixed(1);
            document.getElementById('humidity').innerText = data.humidity.toFixed(1);
            document.getElementById('switch-state').innerText = data.switch_state;
        };
        setInterval(function() {
            ws.send("request_sensor_data");
        }, 5000); // 5초마다 데이터 요청
    </script>
</body>
</html>
)**";

// --- melodyPlay.h (멜로디 연주 웹 페이지) ---
const char* melody_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>멜로디 연주</title>
    <style>
        body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
        .container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
        h1 { color: #9c27b0; margin-bottom: 20px; }
        .melody-buttons { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; margin-bottom: 20px; }
        .melody-buttons button { padding: 15px; font-size: 1.1em; font-weight: bold; border: none; border-radius: 10px; color: white; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }
        .melody-buttons button:hover { transform: translateY(-3px); box-shadow: 0 6px 10px rgba(0,0,0,0.15); }
        .alarm-btn { background-color: #f44336; }
        .melody-btn-1 { background-color: #28a745; }
        .melody-btn-2 { background-color: #ffc107; }
        .melody-btn-3 { background-color: #17a2b8; }
        .melody-btn-4 { background-color: #6f42c1; }
        .back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>멜로디 연주</h1>
        <p>원하는 멜로디 버튼을 눌러보세요.</p>
        <div class="melody-buttons">
            <button class="alarm-btn" onclick="playMelody('alarm')">삐 소리</button>
            <button class="melody-btn-1" onclick="playMelody('melody1')">생일 축하</button>
            <button class="melody-btn-2" onclick="playMelody('melody2')">작은 별</button>
            <button class="melody-btn-3" onclick="playMelody('melody3')">엘리제를 위하여</button>
            <button class="melody-btn-4" onclick="playMelody('melody4')">떴다 떴다 비행기</button>
        </div>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
        function playMelody(melody) {
            ws.send("play_melody:" + melody);
        }
    </script>
</body>
</html>
)**";

// --- led.h/led.cpp (LED 드라이버) ---
void led_init() {
  // pinMode는 WiFi.softAP 후에 설정됩니다.
  // 초기 상태는 모두 꺼짐 (Low ON이므로 255)
  analogWrite(LED_RED_PIN, 255);
  analogWrite(LED_YELLOW_PIN, 255);
  analogWrite(LED_BLUE_PIN, 255);
}

void led_control(int pin, bool state) {
  // state가 true(켜짐)이면 0, false(꺼짐)이면 255를 보냄
  analogWrite(pin, state ? 0 : 255);
}

// --- display.h/display.cpp (OLED 드라이버) ---
void display_init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!u8g2.begin()) {
    Serial.println("OLED 시작 실패!");
  } else {
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_unifont_t_korean2);
    u8g2.setFontMode(1);
    u8g2.setFontDirection(0);
    u8g2.setCursor(0, 15);
    u8g2.print("UTTEC Lab Ai");
    u8g2.setCursor(0, 30);
    u8g2.print("2번째 line");
    u8g2.setCursor(0, 45);
    u8g2.print("3번째 line");
    u8g2.setCursor(0, 60);
    u8g2.print("환영 합니다");
    u8g2.sendBuffer();
  }
}

void display_update_text(const char* text1, const char* text2, const char* text3, const char* text4) {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print(text1);
  u8g2.setCursor(0, 30);
  u8g2.print(text2);
  u8g2.setCursor(0, 45);
  u8g2.print(text3);
  u8g2.setCursor(0, 60);
  u8g2.print(text4);
  u8g2.sendBuffer();
}

// --- sensor.h/sensor.cpp (AHT20 센서 드라이버) ---
void sensor_init() {
  if (!aht.begin()) {
    Serial.println("AHT20 센서 찾기 실패!");
  }
}

float get_temperature() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  return temp.temperature;
}

float get_humidity() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  return humidity.relative_humidity;
}

// --- switch.h/switch.cpp (스위치 드라이버) ---
void switch_init() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

bool get_switch_state() {
  return digitalRead(SWITCH_PIN);
}

// --- melody.h/melody.cpp (멜로디 드라이버) ---
void play_tone(int pin, int freq, int duration) {
  tone(pin, freq, duration);
}

void play_melody(int melody_index) {
  int melody1[] = { NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, REST, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, REST };
  int melody2[] = { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, REST, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, REST };
  int melody3[] = { NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4, REST, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4 };
  int melody4[] = { NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4, REST, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4, REST };
  int noteDurations[] = { 400, 400, 400, 400, 400, 400, 200, 400, 400, 400, 400, 400, 400, 200 };
  int noteDurations2[] = { 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400 };
  int noteDurations3[] = { 200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 400, 400, 400, 400 };
  int noteDurations4[] = { 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250 };
  
  int noteCount = 0;
  int* currentMelody;
  int* currentDurations;
  
  if (melody_index == 1) { // 생일 축하
    currentMelody = melody1;
    currentDurations = noteDurations;
    noteCount = sizeof(melody1) / sizeof(melody1[0]);
  } else if (melody_index == 2) { // 작은 별
    currentMelody = melody2;
    currentDurations = noteDurations2;
    noteCount = sizeof(melody2) / sizeof(melody2[0]);
  } else if (melody_index == 3) { // 엘리제를 위하여
    currentMelody = melody3;
    currentDurations = noteDurations3;
    noteCount = sizeof(melody3) / sizeof(melody3[0]);
  } else if (melody_index == 4) { // 떴다 떴다 비행기
    currentMelody = melody4;
    currentDurations = noteDurations4;
    noteCount = sizeof(melody4) / sizeof(melody4[0]);
  }

  if (noteCount > 0) {
    for (int i = 0; i < noteCount; i++) {
      if (currentMelody[i] == REST) {
        noTone(SPEAKER_PIN);
        delay(currentDurations[i]);
      } else {
        tone(SPEAKER_PIN, currentMelody[i], currentDurations[i]);
        delay(currentDurations[i] * 1.3);
      }
    }
  }
}

// --- WebSocket 이벤트 핸들러 ---
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_CONNECTED) {
    ws.sendTXT(num, ssid);
  } else if (type == WStype_DISCONNECTED) {
    // 연결 해제 처리
  } else if (type == WStype_TEXT) {
    String message = (char*)payload;

    if (message.startsWith("toggle_led:")) {
      String color = message.substring(11);
      int pin = 0;
      if (color == "red") pin = LED_RED_PIN;
      else if (color == "yellow") pin = LED_YELLOW_PIN;
      else if (color == "blue") pin = LED_BLUE_PIN;
      
      if (pin != 0) {
        static bool led_states[3] = {false, false, false}; // Red, Yellow, Blue
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
      float temp = get_temperature();
      float humi = get_humidity();
      bool switch_state = get_switch_state();
      
      String json = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(humi) + ", \"switch_state\": \"" + (switch_state ? "OFF" : "ON") + "\"}";
      ws.sendTXT(num, json);
    } else if (message.startsWith("play_melody:")) {
      String melody_name = message.substring(12);
      if (melody_name == "alarm") {
        play_tone(BEEPER_PIN, 1000, 500);
      } else if (melody_name == "melody1") {
        play_melody(1);
      } else if (melody_name == "melody2") {
        play_melody(2);
      } else if (melody_name == "melody3") {
        play_melody(3);
      } else if (melody_name == "melody4") {
        play_melody(4);
      }
    }
  }
}

// --- setup() 함수 ---
void setup() {
  Serial.begin(115200);

  // WiFi AP 설정
  Serial.println("AP 모드 시작 중...");
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP 주소: ");
  Serial.println(IP);

  // LED 핀모드 설정 (WiFi.softAP 후)
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  led_init();

  // Beeper 및 Speaker 핀모드 설정
  pinMode(BEEPER_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(BEEPER_PIN, HIGH);

  // 스위치 핀모드 설정
  switch_init();

  // OLED 및 AHT20 센서 초기화
  display_init();
  sensor_init();
  
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
  // loop()에서는 웹소켓 클라이언트 관리를 위해 ws.loop()만 호출
  // 모든 제어는 웹소켓 이벤트를 통해 비동기적으로 처리됩니다.
}

