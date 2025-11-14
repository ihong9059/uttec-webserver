#ifndef MELODYPLAY_H
#define MELODYPLAY_H

const char* melody_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>🎵 멜로디 연주</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #00cec9 0%, #00b894 100%);
            min-height: 100vh; padding: 20px; text-align: center;
        }
        .container {
            max-width: 500px; margin: 0 auto; background: rgba(255, 255, 255, 0.95);
            border-radius: 25px; padding: 30px; box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .header { margin-bottom: 25px; }
        h1 { color: #00897b; font-size: 2.5em; margin-bottom: 10px; }
        .home-btn {
            position: absolute; top: 20px; left: 20px; padding: 10px 20px;
            background: #ff6b6b; color: white; border: none; border-radius: 15px;
            cursor: pointer; font-weight: bold;
        }
        .melody-grid {
            display: grid; grid-template-columns: 1fr; gap: 15px; margin: 25px 0;
        }
        .melody-btn {
            padding: 20px; border: none; border-radius: 20px; font-size: 1.2em;
            font-weight: bold; cursor: pointer; transition: all 0.3s; color: white;
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        .melody-btn:hover { transform: translateY(-3px); box-shadow: 0 8px 20px rgba(0,0,0,0.3); }
        .melody-btn:active { transform: translateY(0); }
        .alarm-btn { background: linear-gradient(145deg, #ff7675, #e17055); }
        .melody1-btn { background: linear-gradient(145deg, #74b9ff, #0984e3); }
        .melody2-btn { background: linear-gradient(145deg, #fdcb6e, #f39c12); }
        .melody3-btn { background: linear-gradient(145deg, #a29bfe, #6c5ce7); }
        .melody4-btn { background: linear-gradient(145deg, #dfe6e9, #b2bec3); color: #2d3436; }
        .status {
            margin: 15px 0; padding: 12px; border-radius: 12px; font-weight: bold;
            background: #e8f5e8; color: #2e7d32; border: 2px solid #4caf50;
        }
        .emoji { font-size: 1.3em; margin-right: 10px; }
    </style>
</head>
<body>
    <button class='home-btn' onclick='location.href="/"'>🏠 홈으로</button>
    
    <div class='container'>
        <div class='header'>
            <h1>🎵 멜로디 연주</h1>
            <p>버튼을 눌러 다양한 멜로리를 들어보세요!</p>
        </div>

        <div class='melody-grid'>
            <button class='melody-btn alarm-btn' onclick='playMelody("alarm")'>
                <span class='emoji'>🚨</span>알람 소리 (0.5초 비프음)
            </button>
            <button class='melody-btn melody1-btn' onclick='playMelody("happy")'>
                <span class='emoji'>😊</span>즐거운 날
            </button>
            <button class='melody-btn melody2-btn' onclick='playMelody("birthday")'>
                <span class='emoji'>🎂</span>생일 축하곡
            </button>
            <button class='melody-btn melody3-btn' onclick='playMelody("star")'>
                <span class='emoji'>⭐</span>작은 별
            </button>
            <button class='melody-btn melody4-btn' onclick='playMelody("game")'>
                <span class='emoji'>🎮</span>게임 BGM
            </button>
        </div>

        <div id='status' class='status'>멜로디를 선택해주세요!</div>
    </div>

    <script>
        function playMelody(type) {
            const statusDiv = document.getElementById('status');
            statusDiv.textContent = '🔄 연주 중...';
            
            fetch('/playMelody?type=' + type)
                .then(response => response.text())
                .then(data => {
                    statusDiv.textContent = '✅ 연주 완료: ' + getMelodyName(type);
                })
                .catch(error => {
                    statusDiv.textContent = '❌ 연주 실패';
                });
        }

        function getMelodyName(type) {
            const names = {
                'alarm': '알람 소리',
                'happy': '즐거운 날',
                'birthday': '생일 축하곡',
                'star': '작은 별',
                'game': '게임 BGM'
            };
            return names[type] || type;
        }
    </script>
</body>
</html>
)**";

#endif