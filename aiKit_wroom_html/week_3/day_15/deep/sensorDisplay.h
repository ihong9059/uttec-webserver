#ifndef SENSORDISPLAY_H
#define SENSORDISPLAY_H

const char* sensor_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>센서 및 스위치 데이터</title>
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
        .sensor-data {
            margin: 20px 0;
            padding: 20px;
            background-color: #f8f9fa;
            border-radius: 8px;
            border-left: 4px solid #007bff;
        }
        .switch-data {
            margin: 20px 0;
            padding: 20px;
            background-color: #fff3cd;
            border-radius: 8px;
            border-left: 4px solid #ffc107;
        }
        .sensor-value {
            font-size: 24px;
            font-weight: bold;
            color: #007bff;
            margin: 5px 0;
        }
        .switch-value {
            font-size: 24px;
            font-weight: bold;
            color: #ffc107;
            margin: 5px 0;
        }
        .sensor-unit {
            font-size: 16px;
            color: #6c757d;
        }
        .sensor-label {
            font-size: 18px;
            font-weight: bold;
            color: #495057;
            margin-bottom: 5px;
        }
        .switch-status {
            display: inline-block;
            padding: 8px 16px;
            border-radius: 20px;
            font-weight: bold;
            margin-top: 10px;
        }
        .switch-on {
            background-color: #d4edda;
            color: #155724;
        }
        .switch-off {
            background-color: #f8d7da;
            color: #721c24;
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
        .button-refresh {
            background-color: #28a745;
            color: white;
        }
        .button-refresh:hover {
            background-color: #218838;
        }
        .button-home {
            background-color: #6c757d;
            color: white;
        }
        .button-home:hover {
            background-color: #5a6268;
        }
        .last-update {
            text-align: center;
            color: #6c757d;
            font-size: 14px;
            margin-top: 20px;
        }
        .auto-refresh {
            margin: 15px 0;
            text-align: center;
        }
        .auto-refresh label {
            margin-left: 8px;
        }
        .section-title {
            font-size: 20px;
            font-weight: bold;
            color: #343a40;
            margin-bottom: 15px;
            padding-bottom: 5px;
            border-bottom: 2px solid #dee2e6;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>센서 및 스위치 데이터</h1>
        
        <div class="section-title">🌡️ 환경 센서</div>
        <div class="sensor-data">
            <div class="sensor-label">온도</div>
            <div class="sensor-value" id="temperature">--</div>
            <div class="sensor-unit">°C</div>
        </div>
        
        <div class="sensor-data">
            <div class="sensor-label">💧 습도</div>
            <div class="sensor-value" id="humidity">--</div>
            <div class="sensor-unit">%</div>
        </div>
        
        <div class="section-title">🔘 스위치 상태</div>
        <div class="switch-data">
            <div class="sensor-label">스위치 (GPIO 32)</div>
            <div class="switch-value" id="switchState">--</div>
            <div class="switch-status" id="switchStatus">--</div>
        </div>
        
        <div class="auto-refresh">
            <input type="checkbox" id="autoRefresh" checked onchange="toggleAutoRefresh()">
            <label for="autoRefresh">3초마다 자동 갱신</label>
        </div>
        
        <button class="button button-refresh" onclick="refreshData()">데이터 새로고침</button>
        <button class="button button-home" onclick="goToMain()">메인 페이지로 이동</button>
        
        <div class="last-update" id="lastUpdate">마지막 업데이트: --</div>
    </div>

    <script>
        var websocket;
        var autoRefreshInterval;
        
        function initWebSocket() {
            websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            websocket.onopen = function(event) {
                console.log('WebSocket connected');
                // 연결 시 즉시 데이터 요청
                requestSensorData();
            };
            
            websocket.onclose = function(event) {
                console.log('WebSocket disconnected, reconnecting...');
                clearInterval(autoRefreshInterval);
                setTimeout(initWebSocket, 2000);
            };
            
            websocket.onmessage = function(event) {
                processSensorData(event.data);
            };
        }
        
        function processSensorData(data) {
            if (data.startsWith('sensor:')) {
                var sensorData = data.substring(7);
                var values = sensorData.split(',');
                
                if (values.length === 3) {
                    // 온도, 습도, 스위치 상태
                    document.getElementById('temperature').textContent = parseFloat(values[0]).toFixed(1);
                    document.getElementById('humidity').textContent = parseFloat(values[1]).toFixed(1);
                    
                    var switchState = values[2];
                    document.getElementById('switchState').textContent = switchState;
                    
                    var switchStatus = document.getElementById('switchStatus');
                    if (switchState === 'ON') {
                        switchStatus.textContent = '스위치 눌림';
                        switchStatus.className = 'switch-status switch-on';
                    } else {
                        switchStatus.textContent = '스위치 떨어짐';
                        switchStatus.className = 'switch-status switch-off';
                    }
                    
                    var now = new Date();
                    var timeString = now.toLocaleTimeString('ko-KR');
                    document.getElementById('lastUpdate').textContent = '마지막 업데이트: ' + timeString;
                }
            }
        }
        
        function requestSensorData() {
            if (websocket.readyState === WebSocket.OPEN) {
                websocket.send('get_sensor');
            }
        }
        
        function refreshData() {
            requestSensorData();
        }
        
        function toggleAutoRefresh() {
            var autoRefresh = document.getElementById('autoRefresh').checked;
            
            clearInterval(autoRefreshInterval);
            
            if (autoRefresh) {
                autoRefreshInterval = setInterval(function() {
                    requestSensorData();
                }, 3000);
            }
        }
        
        function goToMain() {
            window.location.href = "/";
        }
        
        window.onload = function() {
            initWebSocket();
            // 자동 갱신 시작
            autoRefreshInterval = setInterval(function() {
                requestSensorData();
            }, 3000);
        };
        
        window.onbeforeunload = function() {
            clearInterval(autoRefreshInterval);
            if (websocket) {
                websocket.close();
            }
        };
    </script>
</body>
</html>
)**";

#endif

