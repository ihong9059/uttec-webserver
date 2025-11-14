#ifndef MAIN_H
#define MAIN_H

const char* main_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>🏠 ESP32 마법 상자</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #ff9a9e 0%, #fad0c4 100%);
            min-height: 100vh; padding: 20px; text-align: center;
        }
        .container {
            max-width: 500px; margin: 0 auto; background: rgba(255, 255, 255, 0.95);
            border-radius: 25px; padding: 30px; box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .header { margin-bottom: 25px; }
        h1 { color: #ff6b6b; font-size: 2.5em; margin-bottom: 10px; }
        .subtitle { color: #666; font-size: 1.2em; margin-bottom: 20px; }
        .wifi-info {
            background: linear-gradient(145deg, #e3f2fd, #bbdefb);
            padding: 15px; border-radius: 20px; margin: 20px 0; border: 3px solid #2196f3;
        }
        .menu-grid {
            display: grid; grid-template-columns: 1fr; gap: 15px; margin: 25px 0;
        }
        .menu-btn {
            padding: 20px; border: none; border-radius: 20px; font-size: 1.2em;
            font-weight: bold; cursor: pointer; transition: all 0.3s; color: white;
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        .menu-btn:hover { transform: translateY(-3px); box-shadow: 0 8px 20px rgba(0,0,0,0.3); }
        .menu-btn:active { transform: translateY(0); }
        .led-btn { background: linear-gradient(145deg, #ff6b6b, #ff4757); }
        .display-btn { background: linear-gradient(145deg, #74b9ff, #0984e3); }
        .sensor-btn { background: linear-gradient(145deg, #fdcb6e, #f39c12); }
        .melody-btn { background: linear-gradient(145deg, #00cec9, #00b894); }
        .emoji { font-size: 1.3em; margin-right: 10px; }
    </style>
</head>
<body>
    <div class='container'>
        <div class='header'>
            <h1>🏠 ESP32 마법 상자</h1>
            <div class='subtitle'>버튼을 눌러 다양한 기능을体验해보세요!</div>
        </div>
        
        <div class='wifi-info'>
            <h3>📶 연결 정보</h3>
            <p><strong>와이파이 이름:</strong> {{SSID}}</p>
            <p><strong>주소:</strong> 192.168.4.1</p>
        </div>

        <div class='menu-grid'>
            <button class='menu-btn led-btn' onclick='location.href="/led"'>
                <span class='emoji'>💡</span>LED 제어하기
            </button>
            <button class='menu-btn display-btn' onclick='location.href="/display"'>
                <span class='emoji'>📺</span>디스플레이 글자보내기
            </button>
            <button class='menu-btn sensor-btn' onclick='location.href="/sensor"'>
                <span class='emoji'>🌡️</span>온도/습도 보기
            </button>
            <button class='menu-btn melody-btn' onclick='location.href="/melody"'>
                <span class='emoji'>🎵</span>멜로디 연주하기
            </button>
        </div>
    </div>
</body>
</html>
)**";

#endif