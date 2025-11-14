#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>🌈 ESP32 LED 마법사</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #74ebd5 0%, #9face6 100%);
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
        .led-control {
            background: #f8f9fa;
            border-radius: 20px;
            padding: 20px;
            margin: 20px 0;
            border: 2px solid #ddd;
        }
        .led-title {
            font-size: 1.5em;
            font-weight: bold;
            margin-bottom: 15px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }
        .button-group {
            display: flex;
            gap: 10px;
            justify-content: center;
            margin-bottom: 15px;
            flex-wrap: wrap;
        }
        .btn {
            padding: 12px 20px;
            border: none;
            border-radius: 50px;
            font-size: 1.1em;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s;
            min-width: 100px;
            box-shadow: 0 4px 8px rgba(0,0,0,0.2);
        }
        .btn:hover {
            transform: translateY(-3px);
            box-shadow: 0 6px 12px rgba(0,0,0,0.3);
        }
        .btn:active {
            transform: translateY(0);
        }
        .btn-on {
            background: linear-gradient(145deg, #4caf50, #66bb6a);
            color: white;
        }
        .btn-off {
            background: linear-gradient(145deg, #f44336, #ef5350);
            color: white;
        }
        .slider-container {
            margin: 15px 0;
        }
        .slider {
            width: 100%;
            height: 40px;
            -webkit-appearance: none;
            appearance: none;
            background: linear-gradient(90deg, #ddd, #4caf50);
            outline: none;
            border-radius: 20px;
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background: #ff6b6b;
            cursor: pointer;
            border: 3px solid white;
            box-shadow: 0 2px 6px rgba(0,0,0,0.3);
        }
        .brightness-text {
            font-size: 1.1em;
            font-weight: bold;
            margin-top: 10px;
            color: #333;
        }
        .status {
            margin-top: 15px;
            padding: 12px;
            border-radius: 15px;
            font-weight: bold;
            font-size: 1.1em;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
        }
        .on { background: #e8f5e8; color: #2e7d32; border: 2px solid #4caf50; }
        .off { background: #ffebee; color: #c62828; border: 2px solid #f44336; }
        .dim { background: #fff3e0; color: #ef6c00; border: 2px solid #ff9800; }
        .red { color: #ff4444; }
        .yellow { color: #ffaa00; }
        .blue { color: #4488ff; }
        .emoji { font-size: 1.3em; }
    </style>
</head>
<body>
    <div class='container'>
        <div class='header'>
            <h1>🌈 LED 마법사</h1>
            <div class='subtitle'>ESP32로 빛을 조종해보세요!</div>
        </div>
        
        <div class='wifi-info'>
            <h3>📶 연결 정보</h3>
            <p><strong>와이파이 이름:</strong> {{SSID}}</p>
            <p><strong>주소:</strong> 192.168.4.1</p>
        </div>

        <!-- 빨간 LED -->
        <div class='led-control'>
            <div class='led-title'>
                <span class='emoji'>🔴</span>
                <span class='red'>빨간 불</span>
            </div>
            <div class='button-group'>
                <button class='btn btn-on' onclick='controlLED("red", "on")'>밝게 켜기</button>
                <button class='btn btn-off' onclick='controlLED("red", "off")'>끄기</button>
            </div>
            <div class='slider-container'>
                <input type='range' class='slider' id='red-slider' min='0' max='255' value='0' 
                       oninput='updateRedBrightness(this.value)'>
                <div class='brightness-text'>밝기: <span id='red-brightness'>0</span> / 255</div>
            </div>
            <div id='red-status' class='status off'>지금은 꺼져있어요</div>
        </div>

        <!-- 노란 LED -->
        <div class='led-control'>
            <div class='led-title'>
                <span class='emoji'>🟡</span>
                <span class='yellow'>노란 불</span>
            </div>
            <div class='button-group'>
                <button class='btn btn-on' onclick='controlLED("yellow", "on")'>밝게 켜기</button>
                <button class='btn btn-off' onclick='controlLED("yellow", "off")'>끄기</button>
            </div>
            <div class='slider-container'>
                <input type='range' class='slider' id='yellow-slider' min='0' max='255' value='0' 
                       oninput='updateYellowBrightness(this.value)'>
                <div class='brightness-text'>밝기: <span id='yellow-brightness'>0</span> / 255</div>
            </div>
            <div id='yellow-status' class='status off'>지금은 꺼져있어요</div>
        </div>

        <!-- 파란 LED -->
        <div class='led-control'>
            <div class='led-title'>
                <span class='emoji'>🔵</span>
                <span class='blue'>파란 불</span>
            </div>
            <div class='button-group'>
                <button class='btn btn-on' onclick='controlLED("blue", "on")'>밝게 켜기</button>
                <button class='btn btn-off' onclick='controlLED("blue", "off")'>끄기</button>
            </div>
            <div class='slider-container'>
                <input type='range' class='slider' id='blue-slider' min='0' max='255' value='0' 
                       oninput='updateBlueBrightness(this.value)'>
                <div class='brightness-text'>밝기: <span id='blue-brightness'>0</span> / 255</div>
            </div>
            <div id='blue-status' class='status off'>지금은 꺼져있어요</div>
        </div>
    </div>

    <script>
        function controlLED(color, action) {
            fetch('/led?color=' + color + '&action=' + action)
                .then(response => response.text())
                .then(data => {
                    updateStatus(color, action);
                    if (action === 'on') {
                        document.getElementById(color + '-slider').value = 255;
                        document.getElementById(color + '-brightness').textContent = '255';
                    } else if (action === 'off') {
                        document.getElementById(color + '-slider').value = 0;
                        document.getElementById(color + '-brightness').textContent = '0';
                    }
                });
        }

        function updateRedBrightness(value) {
            document.getElementById('red-brightness').textContent = value;
            fetch('/led?color=red&action=dim&value=' + value);
            updateStatus('red', value > 0 ? 'dim' : 'off');
        }

        function updateYellowBrightness(value) {
            document.getElementById('yellow-brightness').textContent = value;
            fetch('/led?color=yellow&action=dim&value=' + value);
            updateStatus('yellow', value > 0 ? 'dim' : 'off');
        }

        function updateBlueBrightness(value) {
            document.getElementById('blue-brightness').textContent = value;
            fetch('/led?color=blue&action=dim&value=' + value);
            updateStatus('blue', value > 0 ? 'dim' : 'off');
        }

        function updateStatus(color, action) {
            const statusDiv = document.getElementById(color + '-status');
            if (action === 'on') {
                statusDiv.textContent = '완전히 밝게 빛나고 있어요! ✨';
                statusDiv.className = 'status on';
            } else if (action === 'dim') {
                const brightness = document.getElementById(color + '-brightness').textContent;
                statusDiv.textContent = '살짝 빛나고 있어요 (' + brightness + ') 💡';
                statusDiv.className = 'status dim';
            } else {
                statusDiv.textContent = '지금은 꺼져있어요';
                statusDiv.className = 'status off';
            }
        }
    </script>
</body>
</html>
)**";

#endif

