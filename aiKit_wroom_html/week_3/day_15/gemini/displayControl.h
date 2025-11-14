#ifndef DISPLAYCONTROL_H
#define DISPLAYCONTROL_H

const char* display_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OLED 제어</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f0f0f0; }
        .container { background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); display: inline-block; width: 80%; max-width: 500px; }
        h1 { color: #333; }
        .line-input { margin-bottom: 15px; text-align: left; }
        label { display: block; margin-bottom: 5px; color: #555; }
        input[type="text"] { width: calc(100% - 20px); padding: 10px; border: 1px solid #ccc; border-radius: 5px; }
        button { padding: 10px 20px; font-size: 1em; margin-top: 20px; cursor: pointer; border: none; border-radius: 5px; color: white; }
        .send-btn { background-color: #007bff; }
        .send-btn:hover { background-color: #0056b3; }
        .back-btn { background-color: #6c757d; margin-left: 10px; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>OLED 제어</h1>
        <p>아래 입력창에 텍스트를 입력하고 '전송' 버튼을 누르세요.</p>
        <div class="line-input">
            <label for="line1">1 Line:</label>
            <input type="text" id="line1" value="UTTEC Lab Ai">
        </div>
        <div class="line-input">
            <label for="line2">2 Line:</label>
            <input type="text" id="line2" value="2번째 line">
        </div>
        <div class="line-input">
            <label for="line3">3 Line:</label>
            <input type="text" id="line3" value="3번째 line">
        </div>
        <div class="line-input">
            <label for="line4">4 Line:</label>
            <input type="text" id="line4" value="환영 합니다">
        </div>
        <button class="send-btn" onclick="sendText()">전송</button>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지로 돌아가기</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.host + '/ws_display');

        function sendText() {
            var lines = [
                document.getElementById('line1').value,
                document.getElementById('line2').value,
                document.getElementById('line3').value,
                document.getElementById('line4').value
            ];
            // 각 줄을 구분자로 합쳐서 전송
            ws.send(lines.join('||'));
        }
    </script>
</body>
</html>
)**";

#endif

