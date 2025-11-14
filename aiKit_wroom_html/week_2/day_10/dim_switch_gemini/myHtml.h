const char* all_HTML = R"rawliteral(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 제어기</title>
    <style>
        body { font-family: 'Arial', sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 20px; }
        .container { max-width: 600px; margin: auto; background-color: #fff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); }
        h1 { color: #3498db; margin-bottom: 5px; }
        .ap-info, .status-info { font-size: 18px; margin: 10px 0; padding: 10px; border-radius: 8px; }
        .ap-info { background-color: #e8f5e9; color: #2e7d32; }
        .status-info { background-color: #ffebee; color: #c62828; }
        .led-section { margin-top: 20px; padding: 15px; border-radius: 10px; background-color: #f9f9f9; }
        .led-section h2 { margin-top: 0; }
        .led-control { margin-bottom: 15px; padding: 10px; border-radius: 8px; border: 1px solid #ddd; }
        .red { background-color: #ffcccc; }
        .yellow { background-color: #fff9c4; }
        .blue { background-color: #bbdefb; }
        .button-group { display: flex; justify-content: center; gap: 10px; margin-top: 10px; }
        .button { padding: 10px 20px; border-radius: 5px; border: none; color: white; font-size: 16px; cursor: pointer; transition: transform 0.2s; }
        .button:active { transform: scale(0.95); }
        .button.on { background-color: #4CAF50; }
        .button.off { background-color: #f44336; }
        .slider-label { font-size: 14px; margin-top: 5px; }
        input[type="range"] { width: 80%; }
        #switch-status { font-weight: bold; }
    </style>
</head>
<body>
    <div class="container">
        <h1>나만의 ESP32 제어기</h1>
        <div class="ap-info">
            <p>지금 연결된 AP 이름: <span>홍길동</span></p>
        </div>

        <div class="led-section">
            <h2>반짝반짝 LED 제어</h2>
            <div class="led-control red">
                <h3>빨강 LED</h3>
                <div class="button-group">
                    <a href="/control_led?color=red&action=on" class="button on">켜기</a>
                    <a href="/control_led?color=red&action=off" class="button off">끄기</a>
                </div>
                <div class="slider-label">밝기 조절: <span id="red-value">0</span></div>
                <input type="range" min="0" max="255" value="0" oninput="dimLed('red', this.value)">
            </div>
            
            <div class="led-control yellow">
                <h3>노랑 LED</h3>
                <div class="button-group">
                    <a href="/control_led?color=yellow&action=on" class="button on">켜기</a>
                    <a href="/control_led?color=yellow&action=off" class="button off">끄기</a>
                </div>
                <div class="slider-label">밝기 조절: <span id="yellow-value">0</span></div>
                <input type="range" min="0" max="255" value="0" oninput="dimLed('yellow', this.value)">
            </div>

            <div class="led-control blue">
                <h3>파랑 LED</h3>
                <div class="button-group">
                    <a href="/control_led?color=blue&action=on" class="button on">켜기</a>
                    <a href="/control_led?color=blue&action=off" class="button off">끄기</a>
                </div>
                <div class="slider-label">밝기 조절: <span id="blue-value">0</span></div>
                <input type="range" min="0" max="255" value="0" oninput="dimLed('blue', this.value)">
            </div>
        </div>

        <div class="status-info">
            <h2>스위치 상태</h2>
            <p>지금 스위치는: <span id="switch-status">확인 중...</span></p>
        </div>
    </div>

    <script>
        // LED 밝기 조절 함수
        function dimLed(color, value) {
            document.getElementById(color + '-value').textContent = value;
            fetch('/control_led?color=' + color + '&action=dim&value=' + value);
        }

        // 스위치 상태를 주기적으로 확인하는 함수
        function getSwitchStatus() {
            fetch('/switch_status')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('switch-status').textContent = data.status;
                })
                .catch(error => console.error('Error fetching switch status:', error));
        }

        // 1초마다 스위치 상태 업데이트
        setInterval(getSwitchStatus, 1000);
    </script>
</body>
</html>
)rawliteral";


