#ifndef MELODYPLAY_H
#define MELODYPLAY_H

const char* melody_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>멜로디 재생</title>
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
            margin-bottom: 30px;
        }
        .button-grid {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
            margin-bottom: 20px;
        }
        .button {
            padding: 20px;
            border: none;
            border-radius: 10px;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            text-align: center;
            transition: all 0.3s ease;
        }
        .button:hover {
            transform: translateY(-2px);
            box-shadow: 0 4px 8px rgba(0,0,0,0.2);
        }
        .button:active {
            transform: translateY(0);
        }
        .button-alarm {
            background-color: #ff4444;
            color: white;
            grid-column: span 2;
        }
        .button-alarm:hover {
            background-color: #cc0000;
        }
        .button-melody1 {
            background-color: #33b5e5;
            color: white;
        }
        .button-melody1:hover {
            background-color: #0099cc;
        }
        .button-melody2 {
            background-color: #2bbbad;
            color: white;
        }
        .button-melody2:hover {
            background-color: #00695c;
        }
        .button-melody3 {
            background-color: #aa66cc;
            color: white;
        }
        .button-melody3:hover {
            background-color: #9933cc;
        }
        .button-melody4 {
            background-color: #ffbb33;
            color: white;
        }
        .button-melody4:hover {
            background-color: #ff8800;
        }
        .button-stop {
            background-color: #ff4444;
            color: white;
            grid-column: span 2;
        }
        .button-stop:hover {
            background-color: #cc0000;
        }
        .button-home {
            background-color: #6c757d;
            color: white;
            grid-column: span 2;
        }
        .button-home:hover {
            background-color: #5a6268;
        }
        .status {
            text-align: center;
            margin: 20px 0;
            padding: 15px;
            border-radius: 8px;
            font-weight: bold;
        }
        .status-playing {
            background-color: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
        }
        .status-stopped {
            background-color: #f8d7da;
            color: #721c24;
            border: 1px solid #f5c6cb;
        }
        .status-idle {
            background-color: #fff3cd;
            color: #856404;
            border: 1px solid #ffeaa7;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎵 멜로디 재생</h1>
        
        <div class="status" id="status">재생 대기 중...</div>
        
        <div class="button-grid">
            <button class="button button-alarm" onclick="playAlarm()">🔊 알람 소리 (0.5초 비프)</button>
            <button class="button button-melody1" onclick="playMelody('happy_birthday')">🎂 생일 축하歌</button>
            <button class="button button-melody2" onclick="playMelody('jingle_bells')">🔔 징글벨</button>
            <button class="button button-melody3" onclick="playMelody('twinkle')">✨ 반짝반짝 작은별</button>
            <button class="button button-melody4" onclick="playMelody('ode_to_joy')">🎻 환희의 송가</button>
            <button class="button button-stop" onclick="stopMelody()">⏹️ 재생 중지</button>
            <button class="button button-home" onclick="goToMain()">🏠 메인 페이지로 이동</button>
        </div>
    </div>

    <script>
        var websocket;
        var isPlaying = false;
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                console.log('WebSocket connected');
                updateStatus('idle', '재생 대기 중...');
            };
            
            websocket.onclose = function(event) {
                console.log('WebSocket disconnected, reconnecting...');
                updateStatus('stopped', '연결 끊김, 재연결 중...');
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                console.log('Received:', event.data);
                
                if (event.data.includes('playing')) {
                    isPlaying = true;
                    updateStatus('playing', '재생 중...');
                } else if (event.data.includes('stopped')) {
                    isPlaying = false;
                    updateStatus('stopped', '재생 중지됨');
                } else if (event.data.includes('finished')) {
                    isPlaying = false;
                    updateStatus('idle', '재생 완료');
                }
            };
        }
        
        function updateStatus(statusClass, message) {
            var statusDiv = document.getElementById('status');
            statusDiv.textContent = message;
            statusDiv.className = 'status status-' + statusClass;
        }
        
        function playAlarm() {
            if (websocket.readyState === WebSocket.OPEN) {
                websocket.send('play:alarm');
                updateStatus('playing', '알람 소리 재생 중...');
            }
        }
        
        function playMelody(melodyName) {
            if (websocket.readyState === WebSocket.OPEN) {
                websocket.send('play:' + melodyName);
                updateStatus('playing', melodyName + ' 재생 중...');
            }
        }
        
        function stopMelody() {
            if (websocket.readyState === WebSocket.OPEN) {
                websocket.send('stop:melody');
                updateStatus('stopped', '재생 중지됨');
            }
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