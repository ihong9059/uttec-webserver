#ifndef MYHTML_H
#define MYHTML_H

const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>🌡️ ESP32 날씨 관측소</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #74b9ff 0%, #0984e3 100%);
            min-height: 100vh;
            padding: 20px;
            text-align: center;
        }
        .container {
            max-width: 500px;
            margin: 0 auto;
            background: rgba(255, 255, 255, 0.95);
            border-radius: 25px;
            padding: 30px;
            box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .header {
            margin-bottom: 25px;
        }
        h1 {
            color: #2d3436;
            font-size: 2.5em;
            margin-bottom: 10px;
            text-shadow: 2px 2px 4px rgba(255,255,255,0.5);
        }
        .subtitle {
            color: #636e72;
            font-size: 1.2em;
            margin-bottom: 20px;
        }
        .wifi-info {
            background: linear-gradient(145deg, #dfe6e9, #b2bec3);
            padding: 15px;
            border-radius: 20px;
            margin: 20px 0;
            border: 3px solid #636e72;
        }
        .wifi-info h3 {
            color: #2d3436;
            margin-bottom: 10px;
            font-size: 1.3em;
        }
        .sensor-data {
            background: linear-gradient(145deg, #ffeaa7, #fdcb6e);
            padding: 25px;
            border-radius: 20px;
            margin: 20px 0;
            border: 3px solid #e17055;
        }
        .sensor-title {
            font-size: 1.8em;
            color: #d63031;
            margin-bottom: 20px;
            font-weight: bold;
        }
        .data-container {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 20px;
            margin-bottom: 20px;
        }
        .data-box {
            background: rgba(255, 255, 255, 0.9);
            padding: 20px;
            border-radius: 15px;
            box-shadow: 0 5px 15px rgba(0,0,0,0.1);
        }
        .data-label {
            font-size: 1.1em;
            color: #636e72;
            margin-bottom: 10px;
            font-weight: bold;
        }
        .data-value {
            font-size: 2.5em;
            font-weight: bold;
            color: #2d3436;
        }
        .temp-value {
            color: #e17055;
        }
        .hum-value {
            color: #0984e3;
        }
        .unit {
            font-size: 0.6em;
            color: #636e72;
        }
        .emoji {
            font-size: 1.5em;
            margin-right: 10px;
        }
        .status {
            margin-top: 20px;
            padding: 15px;
            border-radius: 15px;
            background: #d8f8ff;
            border: 2px solid #00cec9;
            color: #00897b;
            font-weight: bold;
        }
        .update-info {
            margin-top: 15px;
            color: #636e72;
            font-size: 0.9em;
        }
        .sensor-image {
            width: 100px;
            height: 100px;
            margin: 15px auto;
            background: #74b9ff;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 2.5em;
            color: white;
            box-shadow: 0 5px 15px rgba(116, 185, 255, 0.4);
        }
    </style>
</head>
<body>
    <div class='container'>
        <div class='header'>
            <h1>🌡️ ESP32 날씨 관측소</h1>
            <div class='subtitle'>실시간 온도와 습도를 확인해보세요!</div>
        </div>
        
        <div class='wifi-info'>
            <h3>📶 연결 정보</h3>
            <p><strong>와이파이 이름:</strong> {{SSID}}</p>
            <p><strong>주소:</strong> 192.168.4.1</p>
        </div>

        <div class='sensor-data'>
            <div class='sensor-title'>
                <span class='emoji'>🔍</span>실시간 측정값
            </div>
            
            <div class='sensor-image'>🌡️</div>
            
            <div class='data-container'>
                <div class='data-box'>
                    <div class='data-label'>
                        <span class='emoji'>🔥</span>온도
                    </div>
                    <div id='temperature' class='data-value temp-value'>--.-<span class='unit'>°C</span></div>
                </div>
                
                <div class='data-box'>
                    <div class='data-label'>
                        <span class='emoji'>💧</span>습도
                    </div>
                    <div id='humidity' class='data-value hum-value'>--.-<span class='unit'>%</span></div>
                </div>
            </div>
            
            <div class='status'>
                <span class='emoji'>🔄</span>실시간 업데이트 중...
            </div>
            
            <div class='update-info'>
                1초마다 자동으로 새로고침됩니다!
            </div>
        </div>
        
        <div style='margin-top: 20px; color: #636e72; font-size: 0.9em;'>
            <p>📍 AHT20 센서가 측정한 정확한 데이터입니다</p>
            <p>📊 SDA:21, SCL:22에 연결되어 있어요</p>
        </div>
    </div>

    <script>
        var websocket;
        var lastUpdateTime = Date.now();
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                console.log('WebSocket 연결 성공!');
                updateStatus('✅ 실시간 연결됨');
            };
            
            websocket.onclose = function(event) {
                console.log('WebSocket 연결 끊김');
                updateStatus('❌ 연결 끊김 - 3초 후 재연결...');
                setTimeout(initWebSocket, 3000);
            };
            
            websocket.onmessage = function(event) {
                const data = event.data;
                const parts = data.split(',');
                
                parts.forEach(part => {
                    const [key, value] = part.split(':');
                    if (key === 'temp') {
                        document.getElementById('temperature').innerHTML = 
                            value + '<span class="unit">°C</span>';
                    } else if (key === 'hum') {
                        document.getElementById('humidity').innerHTML = 
                            value + '<span class="unit">%</span>';
                    }
                });
                
                lastUpdateTime = Date.now();
                updateStatus('✅ 실시간 데이터 수신 중...');
            };
            
            websocket.onerror = function(error) {
                console.error('WebSocket 오류:', error);
                updateStatus('❌ 통신 오류 발생');
            };
        }
        
        function updateStatus(message) {
            const statusElement = document.querySelector('.status');
            if (statusElement) {
                statusElement.innerHTML = '<span class="emoji">⏱️</span>' + message;
            }
        }
        
        // 연결 상태 주기적 확인
        setInterval(function() {
            const now = Date.now();
            if (now - lastUpdateTime > 5000) {
                updateStatus('⚠️ 데이터 업데이트 지연됨');
            }
        }, 1000);
        
        // WebSocket 초기화
        window.onload = initWebSocket;
    </script>
</body>
</html>
)**";

#endif