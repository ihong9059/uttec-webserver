// myHtml.h
#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 3색 LED 제어</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Arial', sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        .container {
            background: rgba(255, 255, 255, 0.95);
            padding: 30px;
            border-radius: 20px;
            box-shadow: 0 20px 40px rgba(0,0,0,0.1);
            max-width: 600px;
            width: 100%;
            text-align: center;
        }
        h1 {
            color: #333;
            margin-bottom: 10px;
            font-size: 2.2em;
        }
        .subtitle {
            color: #666;
            margin-bottom: 30px;
            font-size: 1.1em;
        }
        .ssid-info {
            background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
            padding: 20px;
            border-radius: 15px;
            margin: 25px 0;
            border-left: 5px solid #667eea;
        }
        .ssid {
            font-size: 1.5em;
            font-weight: bold;
            color: #2c3e50;
            margin-top: 10px;
        }
        .leds-container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin: 30px 0;
        }
        .led-control {
            background: white;
            padding: 25px;
            border-radius: 15px;
            box-shadow: 0 5px 15px rgba(0,0,0,0.08);
            border: 3px solid transparent;
            transition: all 0.3s ease;
        }
        .led-control:hover {
            transform: translateY(-5px);
            box-shadow: 0 10px 25px rgba(0,0,0,0.15);
        }
        .led-control.red {
            border-color: #ff4757;
        }
        .led-control.yellow {
            border-color: #ffa502;
        }
        .led-control.blue {
            border-color: #3742fa;
        }
        .led-title {
            font-size: 1.3em;
            font-weight: bold;
            margin-bottom: 15px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }
        .led-status {
            font-size: 1.1em;
            padding: 12px;
            border-radius: 8px;
            margin: 15px 0;
            font-weight: bold;
        }
        .status-on {
            background: #e8f7ef;
            color: #2ed573;
            border: 2px solid #7bed9f;
        }
        .status-off {
            background: #fff5f5;
            color: #ff6b81;
            border: 2px solid #ffcccc;
        }
        .btn-group {
            display: flex;
            gap: 10px;
            justify-content: center;
            flex-wrap: wrap;
        }
        .btn {
            padding: 12px 20px;
            border: none;
            border-radius: 25px;
            cursor: pointer;
            font-weight: bold;
            transition: all 0.3s ease;
            min-width: 80px;
        }
        .btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        .btn-on {
            background: linear-gradient(135deg, #2ed573 0%, #1e90ff 100%);
            color: white;
        }
        .btn-off {
            background: linear-gradient(135deg, #ff4757 0%, #ff6b81 100%);
            color: white;
        }
        .btn-toggle {
            background: linear-gradient(135deg, #ffa502 0%, #ff6348 100%);
            color: white;
        }
        .info {
            color: #7f8c8d;
            font-size: 0.9em;
            margin-top: 30px;
            padding-top: 15px;
            border-top: 1px solid #ddd;
        }
        @media (max-width: 768px) {
            .container {
                padding: 20px;
                margin: 10px;
            }
            .leds-container {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🌈 3색 LED 제어 시스템</h1>
        <p class="subtitle">ESP32-WROOM WiFi AP 모드</p>
        
        <div class="ssid-info">
            <p>현재 연결된 WiFi 네트워크:</p>
            <div class="ssid" id="ssidDisplay">로딩 중...</div>
        </div>

        <div class="leds-container">
            <!-- RED LED -->
            <div class="led-control red">
                <div class="led-title">
                    <span style="color: #ff4757;">🔴</span>
                    RED LED
                </div>
                <div class="led-status" id="redStatus">상태 확인 중...</div>
                <div class="btn-group">
                    <button class="btn btn-on" onclick="controlLed('red', 'on')">ON</button>
                    <button class="btn btn-off" onclick="controlLed('red', 'off')">OFF</button>
                    <button class="btn btn-toggle" onclick="controlLed('red', 'toggle')">TOGGLE</button>
                </div>
            </div>

            <!-- YELLOW LED -->
            <div class="led-control yellow">
                <div class="led-title">
                    <span style="color: #ffa502;">🟡</span>
                    YELLOW LED
                </div>
                <div class="led-status" id="yellowStatus">상태 확인 중...</div>
                <div class="btn-group">
                    <button class="btn btn-on" onclick="controlLed('yellow', 'on')">ON</button>
                    <button class="btn btn-off" onclick="controlLed('yellow', 'off')">OFF</button>
                    <button class="btn btn-toggle" onclick="controlLed('yellow', 'toggle')">TOGGLE</button>
                </div>
            </div>

            <!-- BLUE LED -->
            <div class="led-control blue">
                <div class="led-title">
                    <span style="color: #3742fa;">🔵</span>
                    BLUE LED
                </div>
                <div class="led-status" id="blueStatus">상태 확인 중...</div>
                <div class="btn-group">
                    <button class="btn btn-on" onclick="controlLed('blue', 'on')">ON</button>
                    <button class="btn btn-off" onclick="controlLed('blue', 'off')">OFF</button>
                    <button class="btn btn-toggle" onclick="controlLed('blue', 'toggle')">TOGGLE</button>
                </div>
            </div>
        </div>

        <p class="info">ESP32-WROOM | GPIO 25(RED), 26(YELLOW), 27(BLUE) | LOW 활성화</p>
    </div>

    <script>
        // 페이지 로드 시 SSID와 모든 LED 상태 정보 요청
        window.onload = function() {
            // SSID 정보 요청
            fetch('/getssid')
                .then(response => response.text())
                .then(ssid => {
                    document.getElementById('ssidDisplay').textContent = ssid;
                })
                .catch(error => {
                    console.error('SSID Error:', error);
                    document.getElementById('ssidDisplay').textContent = '오류 발생';
                });

            // 모든 LED 상태 요청
            updateAllLedStatus();
        };

        // LED 제어 함수
        function controlLed(color, action) {
            fetch('/led?color=' + color + '&action=' + action)
                .then(response => response.text())
                .then(result => {
                    console.log(color + ' LED 제어 결과:', result);
                    updateAllLedStatus(); // 모든 상태 업데이트
                })
                .catch(error => {
                    console.error('LED 제어 오류:', error);
                    alert(color + ' LED 제어 중 오류가 발생했습니다.');
                });
        }

        // 모든 LED 상태 업데이트 함수
        function updateAllLedStatus() {
            fetch('/ledstatus')
                .then(response => response.json())
                .then(data => {
                    updateLedDisplay('red', data.red);
                    updateLedDisplay('yellow', data.yellow);
                    updateLedDisplay('blue', data.blue);
                })
                .catch(error => {
                    console.error('LED 상태 조회 오류:', error);
                    ['red', 'yellow', 'blue'].forEach(color => {
                        document.getElementById(color + 'Status').textContent = '상태 조회 오류';
                    });
                });
        }

        // 개별 LED 표시 업데이트
        function updateLedDisplay(color, state) {
            const element = document.getElementById(color + 'Status');
            if (state === 'on') {
                element.textContent = '🔴 ON';
                element.className = 'led-status status-on';
            } else {
                element.textContent = '⚫ OFF';
                element.className = 'led-status status-off';
            }
        }

        // 5초마다 자동 상태 업데이트
        setInterval(updateAllLedStatus, 5000);
    </script>
</body>
</html>
)**";

#endif