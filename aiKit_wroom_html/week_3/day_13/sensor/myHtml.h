#ifndef MYHTML_H
#define MYHTML_H

const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 AHT20 모니터링</title>
    <style>
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
            text-align: center;
            max-width: 400px;
            width: 100%;
        }
        
        h1 {
            color: #333;
            margin-bottom: 30px;
            font-size: 24px;
        }
        
        .ap-info {
            background: #f8f9fa;
            padding: 15px;
            border-radius: 10px;
            margin-bottom: 20px;
            border-left: 4px solid #667eea;
        }
        
        .sensor-data {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
            margin-bottom: 20px;
        }
        
        .data-card {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 20px;
            border-radius: 15px;
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
        
        .label {
            font-size: 14px;
            opacity: 0.8;
        }
        
        .connected {
            color: #28a745;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🌡️ ESP32 AHT20 모니터링</h1>
        
        <div class="ap-info">
            <strong>접속된 AP:</strong> <span id="apSSID">로딩 중...</span>
        </div>
        
        <div class="sensor-data">
            <div class="data-card">
                <div class="label">온도</div>
                <div class="value" id="temperature">--</div>
                <div class="unit">°C</div>
            </div>
            
            <div class="data-card">
                <div class="label">습도</div>
                <div class="value" id="humidity">--</div>
                <div class="unit">%</div>
            </div>
        </div>
        
        <div class="connection-status">
            <span>웹소켓 상태: </span>
            <span id="wsStatus" class="connected">연결됨</span>
        </div>
    </div>

    <script>
        var websocket;
        var apSSID = "홍길동"; // AP SSID
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                console.log('WebSocket 연결됨');
                document.getElementById('wsStatus').textContent = '연결됨';
                document.getElementById('wsStatus').className = 'connected';
                
                // AP SSID 표시
                document.getElementById('apSSID').textContent = apSSID;
            };
            
            websocket.onclose = function(event) {
                console.log('WebSocket 연결 끊김');
                document.getElementById('wsStatus').textContent = '연결 끊김';
                document.getElementById('wsStatus').className = '';
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                var data = JSON.parse(event.data);
                console.log('수신 데이터:', data);
                
                document.getElementById('temperature').textContent = data.temperature.toFixed(1);
                document.getElementById('humidity').textContent = data.humidity.toFixed(1);
            };
            
            websocket.onerror = function(error) {
                console.error('WebSocket 오류:', error);
            };
        }
        
        window.onload = function() {
            initWebSocket();
        };
    </script>
</body>
</html>
)**";

#endif


