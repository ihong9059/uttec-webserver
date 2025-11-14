#ifndef DISPLAYCONTROL_H
#define DISPLAYCONTROL_H

const char* display_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>📺 디스플레이 제어</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #74b9ff 0%, #0984e3 100%);
            min-height: 100vh; padding: 20px; text-align: center;
        }
        .container {
            max-width: 500px; margin: 0 auto; background: rgba(255, 255, 255, 0.95);
            border-radius: 25px; padding: 30px; box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .header { margin-bottom: 25px; }
        h1 { color: #0984e3; font-size: 2.5em; margin-bottom: 10px; }
        .home-btn {
            position: absolute; top: 20px; left: 20px; padding: 10px 20px;
            background: #ff6b6b; color: white; border: none; border-radius: 15px;
            cursor: pointer; font-weight: bold;
        }
        .input-group { margin: 15px 0; }
        .input-label { font-size: 1.1em; margin-bottom: 8px; color: #444; }
        .text-input {
            width: 100%; padding: 12px; border: 2px solid #74b9ff; border-radius: 15px;
            font-size: 1em; margin-bottom: 10px; text-align: center;
        }
        .send-btn {
            padding: 15px 30px; background: #00cec9; color: white; border: none;
            border-radius: 20px; font-size: 1.2em; font-weight: bold; cursor: pointer;
            transition: all 0.3s;
        }
        .send-btn:hover { transform: translateY(-2px); background: #00b894; }
        .status { margin: 15px 0; padding: 12px; border-radius: 12px; font-weight: bold; }
        .success { background: #e8f5e8; color: #2e7d32; border: 2px solid #4caf50; }
        .preview {
            background: #2d3436; color: #00cec9; padding: 15px; border-radius: 12px;
            margin: 20px 0; font-family: 'Courier New', monospace; text-align: left;
        }
        .preview-line { margin: 5px 0; }
        .emoji { font-size: 1.3em; margin-right: 8px; }
    </style>
</head>
<body>
    <button class='home-btn' onclick='location.href="/"'>🏠 홈으로</button>
    
    <div class='container'>
        <div class='header'>
            <h1>📺 디스플레이 제어</h1>
            <p>OLED 화면에 표시할 글자를 입력해보세요!</p>
        </div>

        <div class='preview'>
            <div class='preview-line'>1: UTTEC Lab Ai</div>
            <div class='preview-line'>2: <span id='line2-preview'>2번째 line</span></div>
            <div class='preview-line'>3: <span id='line3-preview'>3번째 line</span></div>
            <div class='preview-line'>4: <span id='line4-preview'>환영 합니다</span></div>
        </div>

        <div class='input-group'>
            <div class='input-label'><span class='emoji'>2️⃣</span>두 번째 줄</div>
            <input type='text' id='line2' class='text-input' value='2번째 line' maxlength='16'>
        </div>

        <div class='input-group'>
            <div class='input-label'><span class='emoji'>3️⃣</span>세 번째 줄</div>
            <input type='text' id='line3' class='text-input' value='3번째 line' maxlength='16'>
        </div>

        <div class='input-group'>
            <div class='input-label'><span class='emoji'>4️⃣</span>네 번째 줄</div>
            <input type='text' id='line4' class='text-input' value='환영 합니다' maxlength='16'>
        </div>

        <button class='send-btn' onclick='sendText()'>
            <span class='emoji'>🚀</span>디스플레이에 보내기
        </button>

        <div id='status' class='status'>메시지를 입력해주세요!</div>
    </div>

<script>
    function updatePreview() {
        document.getElementById('line2-preview').textContent = document.getElementById('line2').value;
        document.getElementById('line3-preview').textContent = document.getElementById('line3').value;
        document.getElementById('line4-preview').textContent = document.getElementById('line4').value;
    }

    function sendText() {
        const line2 = document.getElementById('line2').value;
        const line3 = document.getElementById('line3').value;
        const line4 = document.getElementById('line4').value;
        
        if (!line2 && !line3 && !line4) {
            document.getElementById('status').textContent = '적어도 한 줄은 입력해주세요!';
            document.getElementById('status').className = 'status';
            return;
        }

        const data = {
            line2: line2,
            line3: line3,
            line4: line4
        };

        fetch('/displayControl', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(data)
        })
        .then(response => {
            if (response.ok) {
                document.getElementById('status').textContent = '디스플레이 업데이트 완료!';
                document.getElementById('status').className = 'status success';
            } else {
                throw new Error('Network response was not ok');
            }
        })
        .catch(error => {
            document.getElementById('status').textContent = '전송 실패!';
            document.getElementById('status').className = 'status';
            console.error('Error:', error);
        });
    }

    // 입력할 때마다 미리보기 업데이트
    document.querySelectorAll('.text-input').forEach(input => {
        input.addEventListener('input', updatePreview);
    });
</script>
</body>
</html>
)**";

#endif