#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>🌈 ESP32 음악 상자</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #ff9a9e 0%, #fad0c4 100%);
            min-height: 100vh;
            padding: 20px;
            text-align: center;
        }
        .container {
            max-width: 600px;
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
        .melody-section {
            background: linear-gradient(145deg, #f8f9fa, #e9ecef);
            border-radius: 20px;
            padding: 25px;
            margin: 20px 0;
            border: 2px solid #dee2e6;
        }
        .melody-title {
            font-size: 1.8em;
            color: #495057;
            margin-bottom: 20px;
            font-weight: bold;
        }
        .melody-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 15px;
            margin-bottom: 20px;
        }
        .melody-btn {
            padding: 20px 15px;
            border: none;
            border-radius: 20px;
            font-size: 1.1em;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s;
            background: linear-gradient(145deg, #74b9ff, #0984e3);
            color: white;
            box-shadow: 0 5px 15px rgba(116, 185, 255, 0.4);
        }
        .melody-btn:hover {
            transform: translateY(-3px);
            box-shadow: 0 8px 20px rgba(116, 185, 255, 0.6);
        }
        .melody-btn:active {
            transform: translateY(0);
        }
        .melody-btn:nth-child(2) {
            background: linear-gradient(145deg, #fd79a8, #e84393);
        }
        .melody-btn:nth-child(3) {
            background: linear-gradient(145deg, #fdcb6e, #f39c12);
        }
        .melody-btn:nth-child(4) {
            background: linear-gradient(145deg, #00cec9, #00b894);
        }
        .melody-btn:nth-child(5) {
            background: linear-gradient(145deg, #a29bfe, #6c5ce7);
        }
        .melody-btn:nth-child(6) {
            background: linear-gradient(145deg, #dfe6e9, #b2bec3);
            color: #2d3436;
        }
        .status {
            margin-top: 20px;
            padding: 15px;
            border-radius: 15px;
            font-weight: bold;
            font-size: 1.2em;
            background: #fff3e0;
            border: 2px solid #ff9800;
            color: #e65100;
        }
        .playing {
            background: #e8f5e8;
            border-color: #4caf50;
            color: #2e7d32;
        }
        .emoji {
            font-size: 1.3em;
            margin-right: 8px;
        }
        .led-info {
            background: linear-gradient(145deg, #fff, #f1f3f4);
            padding: 15px;
            border-radius: 15px;
            margin: 20px 0;
            border: 2px dashed #ddd;
        }
        .led-info h4 {
            color: #5f6368;
            margin-bottom: 10px;
        }
        .led-icons {
            display: flex;
            justify-content: center;
            gap: 20px;
            font-size: 2em;
            margin: 10px 0;
        }
    </style>
</head>
<body>
    <div class='container'>
        <div class='header'>
            <h1>🎵 ESP32 음악 상자</h1>
            <div class='subtitle'>버튼을 눌러 아름다운 멜로리를 들어보세요!</div>
        </div>
        
        <div class='wifi-info'>
            <h3>📶 연결 정보</h3>
            <p><strong>와이파이 이름:</strong> {{SSID}}</p>
            <p><strong>주소:</strong> 192.168.4.1</p>
        </div>

        <div class='led-info'>
            <h4>🎨 LED 표시등</h4>
            <p>음악이 연주될 때 LED가 함께 빛나요!</p>
            <div class='led-icons'>
                <span style='color: #ff4444;'>🔴</span>
                <span style='color: #ffaa00;'>🟡</span>
                <span style='color: #4488ff;'>🔵</span>
            </div>
            <p>빨간불 · 노란불 · 파란불이 순서대로 켜져요!</p>
        </div>

        <div class='melody-section'>
            <div class='melody-title'>🎹 재생할 멜로디 선택</div>
            
            <div class='melody-grid'>
                <button class='melody-btn' onclick='playMelody(1)'>
                    <span class='emoji'>🎂</span>생일 축하곡
                </button>
                <button class='melody-btn' onclick='playMelody(2)'>
                    <span class='emoji'>⭐</span>작은 별
                </button>
                <button class='melody-btn' onclick='playMelody(3)'>
                    <span class='emoji'>🏠</span>즐거운 나의 집
                </button>
                <button class='melody-btn' onclick='playMelody(4)'>
                    <span class='emoji'>🎵</span>도레미 송
                </button>
                <button class='melody-btn' onclick='playMelody(5)'>
                    <span class='emoji'>🎬</span>영화 테마
                </button>
                <button class='melody-btn' onclick='playMelody(6)'>
                    <span class='emoji'>🎮</span>게임 BGM
                </button>
            </div>

            <div id='status' class='status'>
                <span class='emoji'>⏸️</span>멜로디를 선택해주세요!
            </div>
        </div>
    </div>

    <script>
        function playMelody(number) {
            const statusDiv = document.getElementById('status');
            const melodies = [
                "🎂 생일 축하곡", "⭐ 작은 별", "🏠 즐거운 나의 집",
                "🎵 도레미 송", "🎬 영화 테마", "🎮 게임 BGM"
            ];
            
            statusDiv.innerHTML = `<span class='emoji'>🎵</span>재생 중: ${melodies[number-1]}...`;
            statusDiv.className = 'status playing';
            
            fetch('/melody?number=' + number)
                .then(response => response.text())
                .then(data => {
                    console.log(data);
                    // 25초 후에 상태 초기화 (멜로디 길이 고려)
                    setTimeout(() => {
                        statusDiv.innerHTML = `<span class='emoji'>⏸️</span>멜로디를 선택해주세요!`;
                        statusDiv.className = 'status';
                    }, 25000);
                })
                .catch(error => {
                    console.error('Error:', error);
                    statusDiv.innerHTML = `<span class='emoji'>❌</span>재생 중 오류가 발생했어요!`;
                    statusDiv.className = 'status';
                });
        }
    </script>
</body>
</html>
)**";

#endif