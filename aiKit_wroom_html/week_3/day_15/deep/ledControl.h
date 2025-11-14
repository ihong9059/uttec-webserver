#ifndef LEDCONTROL_H
#define LEDCONTROL_H

const char* led_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED 제어</title>
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
        .led-control {
            margin: 20px 0;
            padding: 15px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        .led-red { border-left: 4px solid #ff4444; }
        .led-yellow { border-left: 4px solid #ffbb33; }
        .led-blue { border-left: 4px solid #33b5e5; }
        
        .slider-container {
            margin: 10px 0;
        }
        
        .slider {
            width: 100%;
            height: 25px;
        }
        
        .button {
            display: block;
            width: 100%;
            padding: 15px;
            margin: 10px 0;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
        }
        
        .button-home {
            background-color: #2196F3;
        }
        
        .button-home:hover {
            background-color: #0b7dda;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>LED 제어 페이지</h1>
        
        <div class="led-control led-red">
            <h3>🔴 RED LED (GPIO 25)</h3>
            <div class="slider-container">
                <input type="range" min="0" max="255" value="0" class="slider" id="redSlider" onchange="controlLED('red', this.value)">
            </div>
            <div>밝기: <span id="redValue">0</span></div>
        </div>
        
        <div class="led-control led-yellow">
            <h3>🟡 YELLOW LED (GPIO 26)</h3>
            <div class="slider-container">
                <input type="range" min="0" max="255" value="0" class="slider" id="yellowSlider" onchange="controlLED('yellow', this.value)">
            </div>
            <div>밝기: <span id="yellowValue">0</span></div>
        </div>
        
        <div class="led-control led-blue">
            <h3>🔵 BLUE LED (GPIO 27)</h3>
            <div class="slider-container">
                <input type="range" min="0" max="255" value="0" class="slider" id="blueSlider" onchange="controlLED('blue', this.value)">
            </div>
            <div>밝기: <span id="blueValue">0</span></div>
        </div>
        
        <button class="button button-home" onclick="goToMain()">메인 페이지로 이동</button>
        
        <div id="message" style="margin-top: 20px; color: #666;"></div>
    </div>

    <script>
        var websocket;
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                document.getElementById('message').textContent = 'WebSocket 연결됨';
            };
            
            websocket.onclose = function(event) {
                document.getElementById('message').textContent = 'WebSocket 연결 끊김, 재연결 시도 중...';
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                document.getElementById('message').textContent = '수신: ' + event.data;
            };
        }
        
        function controlLED(color, value) {
            document.getElementById(color + 'Value').textContent = value;
            
            if(websocket.readyState == WebSocket.OPEN) {
                websocket.send(color + ':' + value);
            }
        }
        
        function goToMain() {
            window.location.href = "/";
        }
        
        window.onload = function() {
            initWebSocket();
            
            // 슬라이더 값 표시 업데이트
            document.getElementById('redSlider').oninput = function() {
                document.getElementById('redValue').textContent = this.value;
            };
            document.getElementById('yellowSlider').oninput = function() {
                document.getElementById('yellowValue').textContent = this.value;
            };
            document.getElementById('blueSlider').oninput = function() {
                document.getElementById('blueValue').textContent = this.value;
            };
        };
    </script>
</body>
</html>
)**";

#endif