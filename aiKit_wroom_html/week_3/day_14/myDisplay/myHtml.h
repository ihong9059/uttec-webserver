#ifndef MYHTML_H
#define MYHTML_H

const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 SSD1306 제어</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        
        body {
            font-family: 'Arial', sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            margin: 0;
            padding: 20px;
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        
        .container {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 20px;
            padding: 30px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            max-width: 500px;
            width: 100%;
        }
        
        h1 {
            color: #333;
            margin-bottom: 25px;
            text-align: center;
            font-size: 24px;
        }
        
        .ap-info {
            background: #f8f9fa;
            padding: 15px;
            border-radius: 10px;
            margin-bottom: 25px;
            border-left: 4px solid #667eea;
            text-align: center;
        }
        
        .sensor-data {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
            margin-bottom: 25px;
        }
        
        .data-card {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 20px;
            border-radius: 15px;
            text-align: center;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.1);
        }
        
        .value {
            font-size: 28px;
            font-weight: bold;
            margin: 10px 0;
        }
        
        .unit {
            font-size: 14px;
            opacity: 0.9;
        }
        
        .input-section {
            margin-bottom: 20px;
        }
        
        .input-group {
            margin-bottom: 15px;
        }
        
        label {
            display: block;
            margin-bottom: 8px;
            font-weight: bold;
            color: #333;
        }
        
        input[type="text"] {
            width: 100%;
            padding: 12px;
            border: 2px solid #ddd;
            border-radius: 8px;
            font-size: 16px;
            transition: border-color 0.3s;
        }
        
        input[type="text"]:focus {
            outline: none;
            border-color: #667eea;
        }
        
        button {
            width: 100%;
            padding: 12px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            transition: transform 0.2s;
        }
        
        button:hover {
            transform: translateY(-2px);
        }
        
        button:active {
            transform: translateY(0);
        }
        
        .status {
            text-align: center;
            margin-top: 15px;
            padding: 10px;
            border-radius: 8px;
            font-weight: bold;
        }
        
        .connected {
            background-color: #d4edda;
            color: #155724;
        }
        
        .disconnected {
            background-color: #f8d7da;
            color: #721c24;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🖥️ ESP32 SSD1306 제어판</h1>
        
        <div class="ap-info">
            <strong>접속된 AP:</strong> <span id="apSSID">로딩 중...</span>
        </div>
        
        <div class="sensor-data">
            <div class="data-card">
                <div>온도</div>
                <div class="value" id="temperature">--</div>
                <div class="unit">°C</div>
            </div>
            
            <div class="data-card">
                <div>습도</div>
                <div class="value" id="humidity">--</div>
                <div class="unit">%</div>
            </div>
        </div>
        
        <div class="input-section">
            <div class="input-group">
                <label for="displayText">SSD1306 4라인에 표시할 텍스트:</label>
                <input type="text" id="displayText" placeholder="한글 텍스트를 입력하세요" maxlength="20">
            </div>
            
            <button onclick="sendText()">📤 텍스트 전송</button>
        </div>
        
        <div class="status">
            웹소켓 상태: <span id="wsStatus" class="connected">연결됨</span>
        </div>
    </div>

    <script>
        var websocket;
        var apSSID = "홍길동"; // AP SSID
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                console.log('WebSocket 연결됨');
                updateStatus('연결됨', true);
                
                // AP SSID 표시
                document.getElementById('apSSID').textContent = apSSID;
                
                // 연결 시 현재 데이터 요청
                websocket.send('getData');
            };
            
            websocket.onclose = function(event) {
                console.log('WebSocket 연결 끊김');
                updateStatus('연결 끊김', false);
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                try {
                    var data = JSON.parse(event.data);
                    console.log('수신 데이터:', data);
                    
                    if (data.type === 'sensor') {
                        document.getElementById('temperature').textContent = data.temperature.toFixed(1);
                        document.getElementById('humidity').textContent = data.humidity.toFixed(1);
                    } else if (data.type === 'message') {
                        alert('메시지: ' + data.text);
                    }
                } catch (e) {
                    console.log('메시지:', event.data);
                }
            };
            
            websocket.onerror = function(error) {
                console.error('WebSocket 오류:', error);
                updateStatus('오류', false);
            };
        }
        
        function updateStatus(text, isConnected) {
            var statusElement = document.getElementById('wsStatus');
            statusElement.textContent = text;
            statusElement.className = isConnected ? 'connected' : 'disconnected';
        }
        
        function sendText() {
            var textInput = document.getElementById('displayText');
            var text = textInput.value.trim();
            
            if (text) {
                var message = {
                    type: 'display',
                    text: text
                };
                websocket.send(JSON.stringify(message));
                textInput.value = '';
                alert('텍스트가 전송되었습니다: ' + text);
            } else {
                alert('텍스트를 입력해주세요');
            }
        }
        
        // Enter 키로 전송
        document.getElementById('displayText').addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                sendText();
            }
        });
        
        window.onload = function() {
            initWebSocket();
        };
    </script>
</body>
</html>
)**";

#endif