#ifndef MAIN_H
#define MAIN_H

const char* main_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 AP 정보</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f0f0f0; }
        .container { background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); display: inline-block; }
        h1 { color: #333; }
        p { font-size: 1.2em; color: #666; }
        #ssid-display { font-weight: bold; color: #007bff; }
        button { padding: 10px 20px; font-size: 1em; margin-top: 20px; cursor: pointer; border: none; border-radius: 5px; color: white; margin: 5px; }
        .led-btn { background-color: #28a745; }
        .led-btn:hover { background-color: #218838; }
        .display-btn { background-color: #17a2b8; }
        .display-btn:hover { background-color: #138496; }
        .sensor-btn { background-color: #ffc107; }
        .sensor-btn:hover { background-color: #e0a800; }
        .melody-btn { background-color: #6f42c1; }
        .melody-btn:hover { background-color: #563d7c; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 AP 정보</h1>
        <p>현재 AP의 SSID: <span id="ssid-display">연결 대기 중...</span></p>
        <button class="led-btn" onclick="window.location.href='/led'">LED 제어 페이지로 이동</button>
        <button class="display-btn" onclick="window.location.href='/display'">OLED 제어 페이지로 이동</button>
        <button class="sensor-btn" onclick="window.location.href='/sensor'">센서 값 페이지로 이동</button>
        <button class="melody-btn" onclick="window.location.href='/melody'">멜로디 연주 페이지로 이동</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.host + '/ws');
        ws.onmessage = function(event) {
            document.getElementById('ssid-display').innerText = event.data;
        };
    </script>
</body>
</html>
)**";

#endif




