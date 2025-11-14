#ifndef DISPLAYCONTROL_H
#define DISPLAYCONTROL_H

const char* display_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OLED 디스플레이 제어</title>
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
        .line-control {
            margin: 15px 0;
            padding: 15px;
            border: 1px solid #ddd;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .line-label {
            font-weight: bold;
            margin-bottom: 5px;
            color: #555;
        }
        input[type="text"] {
            width: 100%;
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
            font-size: 14px;
            box-sizing: border-box;
        }
        .button {
            display: block;
            width: 100%;
            padding: 15px;
            margin: 10px 0;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
        }
        .button-send {
            background-color: #4CAF50;
            color: white;
        }
        .button-send:hover {
            background-color: #45a049;
        }
        .button-home {
            background-color: #2196F3;
            color: white;
        }
        .button-home:hover {
            background-color: #0b7dda;
        }
        #message {
            margin-top: 20px;
            padding: 10px;
            border-radius: 4px;
            display: none;
        }
        .success {
            background-color: #dff0d8;
            color: #3c763d;
            border: 1px solid #d6e9c6;
        }
        .error {
            background-color: #f2dede;
            color: #a94442;
            border: 1px solid #ebccd1;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>OLED 디스플레이 제어</h1>
        
        <div class="line-control">
            <div class="line-label">1번째 라인:</div>
            <input type="text" id="line1" value="UTTEC Lab Ai" maxlength="20">
        </div>
        
        <div class="line-control">
            <div class="line-label">2번째 라인:</div>
            <input type="text" id="line2" value="2번째 line" maxlength="20">
        </div>
        
        <div class="line-control">
            <div class="line-label">3번째 라인:</div>
            <input type="text" id="line3" value="3번째 line" maxlength="20">
        </div>
        
        <div class="line-control">
            <div class="line-label">4번째 라인:</div>
            <input type="text" id="line4" value="환영 합니다" maxlength="20">
        </div>
        
        <button class="button button-send" onclick="sendDisplayText()">디스플레이에 표시</button>
        <button class="button button-home" onclick="goToMain()">메인 페이지로 이동</button>
        
        <div id="message"></div>
    </div>

    <script>
        var websocket;
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                console.log('WebSocket connected');
            };
            
            websocket.onclose = function(event) {
                console.log('WebSocket disconnected, reconnecting...');
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                showMessage(event.data, 'success');
            };
            
            websocket.onerror = function(event) {
                showMessage('WebSocket error', 'error');
            };
        }
        
        function sendDisplayText() {
            var line1 = document.getElementById('line1').value;
            var line2 = document.getElementById('line2').value;
            var line3 = document.getElementById('line3').value;
            var line4 = document.getElementById('line4').value;
            
            if(websocket.readyState === WebSocket.OPEN) {
                var message = 'display:' + line1 + '|' + line2 + '|' + line3 + '|' + line4;
                websocket.send(message);
                showMessage('메시지 전송 중...', 'success');
            } else {
                showMessage('WebSocket 연결이 없습니다', 'error');
            }
        }
        
        function showMessage(text, type) {
            var messageDiv = document.getElementById('message');
            messageDiv.textContent = text;
            messageDiv.className = type;
            messageDiv.style.display = 'block';
            
            setTimeout(function() {
                messageDiv.style.display = 'none';
            }, 3000);
        }
        
        function goToMain() {
            window.location.href = "/";
        }
        
        window.onload = function() {
            initWebSocket();
        };
    </script>
</body>
</html>
)**";

#endif