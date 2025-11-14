#ifndef MYHTML_H
#define MYHTML_H

const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>📺 ESP32 디스플레이 제어</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);
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
            color: #ff6b6b;
            font-size: 2.5em;
            margin-bottom: 10px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.1);
        }
        .subtitle {
            color: #666;
            font-size: 1.2em;
            margin-bottom: 20px;
        }
        .wifi-info {
            background: linear-gradient(145deg, #e3f2fd, #bbdefb);
            padding: 15px;
            border-radius: 20px;
            margin: 20px 0;
            border: 3px solid #2196f3;
        }
        .wifi-info h3 {
            color: #1976d2;
            margin-bottom: 10px;
            font-size: 1.3em;
        }
        .sensor-data {
            background: linear-gradient(145deg, #ffeaa7, #fdcb6e);
            padding: 20px;
            border-radius: 20px;
            margin: 20px 0;
            border: 3px solid #e17055;
        }
        .data-container {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
            margin-bottom: 15px;
        }
        .data-box {
            background: rgba(255, 255, 255, 0.9);
            padding: 15px;
            border-radius: 15px;
            box-shadow: 0 3px 10px rgba(0,0,0,0.1);
        }
        .data-label {
            font-size: 1em;
            color: #636e72;
            margin-bottom: 8px;
            font-weight: bold;
        }
        .data-value {
            font-size: 2em;
            font-weight: bold;
        }
        .temp-value { color: #e17055; }
        .hum-value { color: #0984e3; }
        .unit { font-size: 0.6em; color: #636e72; }
        
        .display-control {
            background: linear-gradient(145deg, #d8f8ff, #a8edea);
            padding: 25px;
            border-radius: 20px;
            margin: 20px 0;
            border: 3px solid #00cec9;
        }
        .display-title {
            font-size: 1.5em;
            color: #00897b;
            margin-bottom: 20px;
            font-weight: bold;
        }
        .input-group {
            margin-bottom: 20px;
        }
        .text-input {
            width: 100%;
            padding: 15px;
            border: 2px solid #00cec9;
            border-radius: 15px;
            font-size: 1.1em;
            font-family: inherit;
            margin-bottom: 15px;
            text-align: center;
        }
        .send-btn {
            padding: 15px 30px;
            border: none;
            border-radius: 25px;
            background: linear-gradient(145deg, #00cec9, #00b894);
            color: white;
            font-size: 1.2em;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s;
            box-shadow: 0 5px 15px rgba(0,206,201,0.4);
        }
        .send-btn:hover {
            transform: translateY(-3px);
            box-shadow: 0 8px 20px rgba(0,206,201,0.6);
        }
        .send-btn:active {
            transform: translateY(0);
        }
        .status {
            margin-top: 15px;
            padding: 12px;
            border-radius: 12px;
            background: #e8f5e8;
            border: 2px solid #4caf50;
            color: #2e7d32;
            font-weight: bold;
        }
        .emoji {
            font-size: 1.3em;
            margin-right: 8px;
        }
        .display-preview {
            background: #2d3436;
            color: #00cec9;
            padding: 15px;
            border-radius: 12px;
            margin: 15px 0;
            font-family: 'Courier New', monospace;
            text-align: left;
        }
        .preview-line {
            margin: 5px 0;
            font-size: 0.9em;
        }
    </style>
</head>
<body>
    <div class='container'>
        <div class='header'>
            <h1>📺 ESP32 디스플레이</h1>
            <div class='subtitle'>OLED 화면에 메시지를 보내보세요!</div>
        </div>
        
        <div class='wifi-info'>
            <h3>📶 연결 정보</h3>
            <p><strong>와이파이 이름:</strong> {{SSID}}</p>
            <p><strong>주소:</strong> 192.168.4.1</p>
        </div>

        <div class='sensor-data'>
            <h3>🌡️ 실시간 측정값</h3>
            <div class='data-container'>
                <div class='data-box'>
                    <div class='data-label'><span class='emoji'>🔥</span>온도</div>
                    <div id='temperature' class='data-value temp-value'>--.-<span class='unit'>°C</span></div>
                </div>
                <div class='data-box'>
                    <div class='data-label'><span class='emoji'>💧</span>습도</div>
                    <div id='humidity' class='data-value hum-value'>--.-<span class='unit'>%</span></div>
                </div>
            </div>
        </div>

        <div class='display-control'>
            <div class='display-title'>
                <span class='emoji'>✏️</span>디스플레이 메시지 입력
            </div>
            
            <div class='display-preview'>
                <div class='preview-line'>1: UTTEC Lab Ai</div>
                <div class='preview-line'>2: 온도: --.-°C</div>
                <div class='preview-line'>3: 습도: --.-%</div>
                <div class='preview-line'>4: <span id='preview-text'>{{DISPLAY_TEXT}}</span></div>
            </div>
            
            <div class='input-group'>
                <input type='text' id='displayText' class='text-input' 
                       value='{{DISPLAY_TEXT}}' placeholder='여기에 메시지를 입력하세요' 
                       maxlength='20'>
                <button class='send-btn' onclick='sendText()'>
                    <span class='emoji'>🚀</span>디스플레이에 보내기
                </button>
            </div>
            
            <div id='status' class='status'>
                <span class='emoji'>⏳</span>메시지를 입력해주세요!
            </div>
        </div>
        
        <div style='margin-top: 20px; color: #636e72; font-size: 0.9em;'>
            <p>📺 SSD1306 OLED에 메시지가 표시됩니다</p>
            <p>🎯 SDA:21, SCL:22에 연결되어 있어요</p>
        </div>
    </div>

<script>
    var websocket;
    var lastUpdateTime = Date.now();
    
    function initWebSocket() {
        websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
        
        websocket.onopen = function(event) {
            updateStatus('✅ 실시간 연결됨', 'success');
        };
        
        websocket.onclose = function(event) {
            updateStatus('❌ 연결 끊김 - 3초 후 재연결...', 'error');
            setTimeout(initWebSocket, 3000);
        };
        
        websocket.onmessage = function(event) {
            const data = event.data;
            if (data === 'display_updated') {
                updateStatus('✅ 디스플레이 업데이트 완료!', 'success');
                updatePreview();
            } else {
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
            }
            lastUpdateTime = Date.now();
        };
    }
    
    function sendText() {
        const text = document.getElementById('displayText').value.trim();
        if (text === '') {
            updateStatus('❌ 메시지를 입력해주세요!', 'error');
            return;
        }
        
        updateStatus('🔄 디스플레이 업데이트 중...', 'loading');
        
        // WebSocket으로 전송
        if (websocket.readyState === WebSocket.OPEN) {
            websocket.send('text:' + text);
        } else {
            // WebSocket이 연결되지 않았으면 HTTP로 전송
            fetch('/update?text=' + encodeURIComponent(text))
                .then(response => {
                    if (response.ok) {
                        updateStatus('✅ 디스플레이 업데이트 완료!', 'success');
                        updatePreview();
                    } else {
                        updateStatus('❌ 전송 실패!', 'error');
                    }
                })
                .catch(error => {
                    updateStatus('❌ 통신 오류!', 'error');
                    console.error('Error:', error);
                });
        }
    }
    
    function updateStatus(message, type) {
        const statusElement = document.getElementById('status');
        if (statusElement) {
            statusElement.innerHTML = '<span class="emoji">⏱️</span>' + message;
            statusElement.style.background = type === 'success' ? '#e8f5e8' : 
                                           type === 'error' ? '#ffebee' : '#fff3e0';
            statusElement.style.borderColor = type === 'success' ? '#4caf50' : 
                                            type === 'error' ? '#f44336' : '#ff9800';
            statusElement.style.color = type === 'success' ? '#2e7d32' : 
                                      type === 'error' ? '#c62828' : '#e65100';
        }
    }
    
    function updatePreview() {
        const text = document.getElementById('displayText').value;
        document.getElementById('preview-text').textContent = text;
    }
    
    // 엔터키로 전송
    document.getElementById('displayText').addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            sendText();
        }
    });
    
    // WebSocket 초기화
    window.onload = initWebSocket;
</script>
</body>
</html>
)**";

#endif