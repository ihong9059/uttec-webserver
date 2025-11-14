#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>ESP32 3색 LED 제어</title>
    <style>
        body {
            font-family: 'Malgun Gothic', '맑은 고딕', sans-serif;
            text-align: center;
            margin: 20px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }
        .container {
            background: rgba(255, 255, 255, 0.95);
            padding: 30px;
            border-radius: 20px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
            max-width: 500px;
            margin: 0 auto;
            backdrop-filter: blur(10px);
        }
        h1 {
            color: #333;
            margin-bottom: 10px;
            font-size: 28px;
        }
        .ssid-info {
            background: linear-gradient(145deg, #e8f5e8, #d0ebd0);
            padding: 15px;
            border-radius: 12px;
            margin: 20px 0;
            border: 2px solid #4caf50;
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        }
        .ssid-info h3 {
            margin: 0 0 10px 0;
            color: #2e7d32;
            font-size: 18px;
        }
        .ssid-info p {
            margin: 5px 0;
            font-size: 16px;
            color: #555;
        }
        .led-section {
            margin: 25px 0;
            padding: 20px;
            border-radius: 15px;
            background: #f8f9fa;
            box-shadow: inset 0 2px 5px rgba(0,0,0,0.05);
        }
        .led-title {
            font-size: 20px;
            font-weight: bold;
            margin-bottom: 15px;
            color: #444;
        }
        .button-container {
            display: flex;
            justify-content: center;
            gap: 15px;
            margin: 15px 0;
        }
        .btn {
            padding: 12px 25px;
            border: none;
            border-radius: 25px;
            cursor: pointer;
            font-size: 16px;
            font-weight: bold;
            transition: all 0.3s ease;
            min-width: 100px;
            box-shadow: 0 4px 8px rgba(0,0,0,0.2);
        }
        .btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 12px rgba(0,0,0,0.3);
        }
        .btn:active {
            transform: translateY(0);
        }
        .btn-on {
            background: linear-gradient(145deg, #4caf50, #45a049);
            color: white;
        }
        .btn-off {
            background: linear-gradient(145deg, #f44336, #da190b);
            color: white;
        }
        .btn-yellow-on {
            background: linear-gradient(145deg, #ffeb3b, #fbc02d);
            color: #333;
        }
        .btn-yellow-off {
            background: linear-gradient(145deg, #ff9800, #f57c00);
            color: white;
        }
        .btn-blue-on {
            background: linear-gradient(145deg, #2196f3, #1976d2);
            color: white;
        }
        .btn-blue-off {
            background: linear-gradient(145deg, #1565c0, #0d47a1);
            color: white;
        }
        .status {
            margin-top: 15px;
            padding: 12px;
            border-radius: 8px;
            font-weight: bold;
            font-size: 14px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .red-status { background: #ffebee; color: #c62828; border-left: 4px solid #f44336; }
        .yellow-status { background: #fffde7; color: #f57f17; border-left: 4px solid #ffeb3b; }
        .blue-status { background: #e3f2fd; color: #1565c0; border-left: 4px solid #2196f3; }
        .on { background: #e8f5e8; color: #2e7d32; border-left: 4px solid #4caf50; }
        .off { background: #ffebee; color: #c62828; border-left: 4px solid #f44336; }
        .led-icon {
            font-size: 24px;
            margin-right: 10px;
            vertical-align: middle;
        }
    </style>
</head>
<body>
    <div class='container'>
        <h1>🌈 ESP32 3색 LED 제어 시스템</h1>
        
        <div class='ssid-info'>
            <h3>📶 접속 정보</h3>
            <p><strong>AP SSID:</strong> {{SSID}}</p>
            <p><strong>IP 주소:</strong> 192.168.4.1</p>
        </div>

        <!-- Red LED Section -->
        <div class='led-section'>
            <div class='led-title'>🔴 RED LED</div>
            <div class='button-container'>
                <button class='btn btn-on' onclick='controlLED("red", "on")'>켜기</button>
                <button class='btn btn-off' onclick='controlLED("red", "off")'>끄기</button>
            </div>
            <div id='red-status' class='status red-status off'>현재 상태: 꺼짐</div>
        </div>

        <!-- Yellow LED Section -->
        <div class='led-section'>
            <div class='led-title'>🟡 YELLOW LED</div>
            <div class='button-container'>
                <button class='btn btn-yellow-on' onclick='controlLED("yellow", "on")'>켜기</button>
                <button class='btn btn-yellow-off' onclick='controlLED("yellow", "off")'>끄기</button>
            </div>
            <div id='yellow-status' class='status yellow-status off'>현재 상태: 꺼짐</div>
        </div>

        <!-- Blue LED Section -->
        <div class='led-section'>
            <div class='led-title'>🔵 BLUE LED</div>
            <div class='button-container'>
                <button class='btn btn-blue-on' onclick='controlLED("blue", "on")'>켜기</button>
                <button class='btn btn-blue-off' onclick='controlLED("blue", "off")'>끄기</button>
            </div>
            <div id='blue-status' class='status blue-status off'>현재 상태: 꺼짐</div>
        </div>
    </div>

    <script>
        function controlLED(color, state) {
            fetch('/led?color=' + color + '&state=' + state)
                .then(response => response.text())
                .then(data => {
                    const statusDiv = document.getElementById(color + '-status');
                    if (state === 'on') {
                        statusDiv.textContent = '현재 상태: 켜짐';
                        statusDiv.className = 'status ' + color + '-status on';
                    } else {
                        statusDiv.textContent = '현재 상태: 꺼짐';
                        statusDiv.className = 'status ' + color + '-status off';
                    }
                })
                .catch(error => console.error('Error:', error));
        }
    </script>
</body>
</html>
)**";

#endif