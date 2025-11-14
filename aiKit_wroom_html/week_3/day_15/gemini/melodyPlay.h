#ifndef MELODYPLAY_H
#define MELODYPLAY_H

const char* melody_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>멜로디 연주</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f0f0f0; }
        .container { background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); display: inline-block; width: 80%; max-width: 500px; }
        h1 { color: #333; }
        .button-group { margin-top: 20px; }
        button { padding: 10px 20px; font-size: 1em; margin: 5px; cursor: pointer; border: none; border-radius: 5px; color: white; }
        .alarm-btn { background-color: #dc3545; }
        .alarm-btn:hover { background-color: #c82333; }
        .melody-btn { background-color: #007bff; }
        .melody-btn:hover { background-color: #0056b3; }
        .back-btn { background-color: #6c757d; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>멜로디 연주</h1>
        <div class="button-group">
            <button class="alarm-btn" onclick="sendCmd('alarm')">Alarm</button>
            <button class="melody-btn" onclick="sendCmd('melody1')">생일 축하 노래</button>
            <button class="melody-btn" onclick="sendCmd('melody2')">학교 종</button>
            <button class="melody-btn" onclick="sendCmd('melody3')">작은 별</button>
            <button class="melody-btn" onclick="sendCmd('melody4')">비행기</button>
        </div>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지로 돌아가기</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.host + '/ws_melody');

        function sendCmd(cmd) {
            ws.send(cmd);
        }
    </script>
</body>
</html>
)**";

#endif