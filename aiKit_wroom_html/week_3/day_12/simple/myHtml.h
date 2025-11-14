#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { 
            font-family: 'Malgun Gothic', '맑은 고딕', Arial, sans-serif; 
            text-align: center; 
            background-color: #f0f0f0;
            margin: 0;
            padding: 20px;
        }
        .container {
            max-width: 600px;
            margin: 0 auto;
            background: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        h1 {
            color: #333;
            margin-bottom: 20px;
        }
        .ap-info {
            background: #e3f2fd;
            padding: 15px;
            border-radius: 5px;
            margin-bottom: 20px;
            font-size: 18px;
        }
        .melody-buttons {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 10px;
            margin-top: 20px;
        }
        .melody-btn {
            padding: 15px;
            border: none;
            border-radius: 5px;
            background: #2196F3;
            color: white;
            font-size: 16px;
            cursor: pointer;
            transition: background 0.3s;
        }
        .melody-btn:hover {
            background: #1976D2;
        }
        .led-container {
            display: flex;
            justify-content: center;
            gap: 20px;
            margin: 20px 0;
        }
        .led {
            width: 50px;
            height: 50px;
            border-radius: 50%;
            background-color: #ccc;
            border: 2px solid #999;
            transition: all 0.3s ease;
        }
        .led.red { background-color: #ff4444; }
        .led.yellow { background-color: #ffcc00; }
        .led.blue { background-color: #4444ff; }
        .led.on { 
            box-shadow: 0 0 20px rgba(255,255,255,0.8);
            transform: scale(1.1);
        }
        .status {
            margin-top: 20px;
            padding: 10px;
            background: #f5f5f5;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎵 ESP32 멜로디 플레이어 🎵</h1>
        
        <div class="ap-info">
            <h2>현재 접속한 AP 정보</h2>
            <p id="apSSID">SSID: 로딩 중...</p>
        </div>

        <div class="led-container">
            <div class="led red" id="redLed"></div>
            <div class="led yellow" id="yellowLed"></div>
            <div class="led blue" id="blueLed"></div>
        </div>

        <div class="melody-buttons">
            <button class="melody-btn" onclick="playMelody(1)">🎵 도레미파솔라시도</button>
            <button class="melody-btn" onclick="playMelody(2)">🎂 생일축하곡</button>
            <button class="melody-btn" onclick="playMelody(3)">🔔 징글벨</button>
            <button class="melody-btn" onclick="playMelody(4)">🎭 오델로</button>
            <button class="melody-btn" onclick="playMelody(5)">⭐ 반짝반짝 작은별</button>
            <button class="melody-btn" onclick="playMelody(6)">🏔️ 아리랑</button>
        </div>

        <div class="status" id="statusMessage">준비됨</div>
    </div>

    <script>
        // 페이지 로드 시 AP SSID 표시
        window.onload = function() {
            document.getElementById('apSSID').textContent = 'SSID: 홍길동 (암호 없음)';
        };

        function playMelody(melodyNumber) {
            const statusElem = document.getElementById('statusMessage');
            const melodies = [
                '도레미파솔라시도',
                '생일축하곡', 
                '징글벨',
                '오델로',
                '반짝반짝 작은별',
                '아리랑'
            ];
            
            statusElem.textContent = '재생 중: ' + melodies[melodyNumber - 1];
            
            fetch('/play?melody=' + melodyNumber)
                .then(response => response.text())
                .then(data => {
                    console.log('Melody played:', data);
                    animateLeds();
                    statusElem.textContent = '재생 완료: ' + melodies[melodyNumber - 1];
                })
                .catch(error => {
                    console.error('Error:', error);
                    statusElem.textContent = '오류 발생';
                });
        }

        function animateLeds() {
            const leds = [
                document.getElementById('redLed'),
                document.getElementById('yellowLed'), 
                document.getElementById('blueLed')
            ];
            
            let current = 0;
            const interval = setInterval(() => {
                // 모든 LED 끄기
                leds.forEach(led => led.classList.remove('on'));
                
                // 현재 LED 켜기
                leds[current].classList.add('on');
                
                // 다음 LED로 이동
                current = (current + 1) % leds.length;
            }, 300);
            
            // 6초 후 애니메이션停止
            setTimeout(() => {
                clearInterval(interval);
                leds.forEach(led => led.classList.remove('on'));
            }, 6000);
        }
    </script>
</body>
</html>
)**";

#endif
