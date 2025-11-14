#ifndef LEDCONTROL_H
#define LEDCONTROL_H

const char* led_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>💡 LED 제어</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #ff6b6b 0%, #ff4757 100%);
            min-height: 100vh; padding: 20px; text-align: center;
        }
        .container {
            max-width: 500px; margin: 0 auto; background: rgba(255, 255, 255, 0.95);
            border-radius: 25px; padding: 30px; box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .header { margin-bottom: 25px; }
        h1 { color: #ff6b6b; font-size: 2.5em; margin-bottom: 10px; }
        .home-btn {
            position: absolute; top: 20px; left: 20px; padding: 10px 20px;
            background: #74b9ff; color: white; border: none; border-radius: 15px;
            cursor: pointer; font-weight: bold;
        }
        .led-control { margin: 20px 0; }
        .led-title { font-size: 1.5em; margin-bottom: 15px; color: #444; }
        .button-group { display: flex; gap: 15px; justify-content: center; margin: 15px 0; }
        .btn {
            padding: 15px 25px; border: none; border-radius: 20px; font-size: 1.1em;
            font-weight: bold; cursor: pointer; transition: all 0.3s;
        }
        .btn-on { background: #4caf50; color: white; }
        .btn-off { background: #f44336; color: white; }
        .btn:hover { transform: translateY(-2px); }
        .status { margin: 15px 0; padding: 12px; border-radius: 12px; font-weight: bold; }
        .on { background: #e8f5e8; color: #2e7d32; border: 2px solid #4caf50; }
        .off { background: #ffebee; color: #c62828; border: 2px solid #f44336; }
        .emoji { font-size: 1.3em; margin-right: 8px; }
    </style>
</head>
<body>
    <button class='home-btn' onclick='location.href="/"'>🏠 홈으로</button>
    
    <div class='container'>
        <div class='header'>
            <h1>💡 LED 제어</h1>
            <p>빨간, 노란, 파란 LED를 켜고 끌 수 있어요!</p>
        </div>

        <!-- 빨간 LED -->
        <div class='led-control'>
            <div class='led-title'><span class='emoji'>🔴</span>빨간 LED</div>
            <div class='button-group'>
                <button class='btn btn-on' onclick='controlLED("red", "on")'>켜기</button>
                <button class='btn btn-off' onclick='controlLED("red", "off")'>끄기</button>
            </div>
            <div id='red-status' class='status off'>꺼짐</div>
        </div>

        <!-- 노란 LED -->
        <div class='led-control'>
            <div class='led-title'><span class='emoji'>🟡</span>노란 LED</div>
            <div class='button-group'>
                <button class='btn btn-on' onclick='controlLED("yellow", "on")'>켜기</button>
                <button class='btn btn-off' onclick='controlLED("yellow", "off")'>끄기</button>
            </div>
            <div id='yellow-status' class='status off'>꺼짐</div>
        </div>

        <!-- 파란 LED -->
        <div class='led-control'>
            <div class='led-title'><span class='emoji'>🔵</span>파란 LED</div>
            <div class='button-group'>
                <button class='btn btn-on' onclick='controlLED("blue", "on")'>켜기</button>
                <button class='btn btn-off' onclick='controlLED("blue", "off")'>끄기</button>
            </div>
            <div id='blue-status' class='status off'>꺼짐</div>
        </div>
    </div>

    <script>
        function controlLED(color, action) {
            fetch('/ledControl?color=' + color + '&action=' + action)
                .then(response => response.text())
                .then(data => {
                    const statusDiv = document.getElementById(color + '-status');
                    if (action === 'on') {
                        statusDiv.textContent = '켜짐';
                        statusDiv.className = 'status on';
                    } else {
                        statusDiv.textContent = '꺼짐';
                        statusDiv.className = 'status off';
                    }
                });
        }
    </script>
</body>
</html>
)**";

#endif