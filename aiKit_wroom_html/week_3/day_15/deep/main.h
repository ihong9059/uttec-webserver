#ifndef MAIN_H
#define MAIN_H

const char* main_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 제어 시스템</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f0f0f0;
        }
        .container {
            max-width: 600px;
            margin: 0 auto;
            background-color: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        h1 {
            color: #333;
            text-align: center;
        }
        .status {
            background-color: #e8f5e8;
            padding: 15px;
            border-radius: 5px;
            margin-bottom: 20px;
            border-left: 4px solid #4CAF50;
        }
        .button {
            display: block;
            width: 100%;
            padding: 15px;
            margin: 10px 0;
            color: white;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
        }
        .button:hover {
            opacity: 0.9;
        }
        .button-led {
            background-color: #4CAF50;
        }
        .button-display {
            background-color: #FF9800;
        }
        .button-sensor {
            background-color: #2196F3;
        }
        .button-melody {
            background-color: #9C27B0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 제어 시스템</h1>
        
        <div class="status">
            <strong>AP SSID:</strong> <span id="apSSID">홍길동</span><br>
            <strong>접속 상태:</strong> <span id="connectionStatus">연결 대기 중...</span>
        </div>

        <button class="button button-led" onclick="goToLEDControl()">LED 제어 페이지</button>
        <button class="button button-display" onclick="goToDisplayControl()">디스플레이 제어 페이지</button>
        <button class="button button-sensor" onclick="goToSensorDisplay()">센서 데이터 페이지</button>
        <button class="button button-melody" onclick="goToMelodyPlay()">🎵 멜로디 재생 페이지</button>
        
        <div id="message" style="margin-top: 20px; color: #666;"></div>
    </div>

    <script>
        var websocket;
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                document.getElementById('connectionStatus').textContent = '연결됨';
                document.getElementById('connectionStatus').style.color = 'green';
            };
            
            websocket.onclose = function(event) {
                document.getElementById('connectionStatus').textContent = '연결 끊김';
                document.getElementById('connectionStatus').style.color = 'red';
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                document.getElementById('message').textContent = '수신: ' + event.data;
            };
        }
        
        function goToLEDControl() {
            window.location.href = "/led";
        }
        
        function goToDisplayControl() {
            window.location.href = "/display";
        }
        
        function goToSensorDisplay() {
            window.location.href = "/sensor";
        }
        
        function goToMelodyPlay() {
            window.location.href = "/melody";
        }
        
        window.onload = function() {
            initWebSocket();
        };
    </script>
</body>
</html>
)**";

#endif


