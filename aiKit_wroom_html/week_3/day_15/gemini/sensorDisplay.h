#ifndef SENSORDISPLAY_H
#define SENSORDISPLAY_H

const char* sensor_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>센서 및 스위치 상태</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f0f0f0; }
        .container { background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); display: inline-block; width: 80%; max-width: 500px; }
        h1 { color: #333; }
        p { font-size: 1.2em; color: #666; }
        .data-display { margin-top: 20px; }
        .data-display span { font-weight: bold; font-size: 1.5em; }
        #temperature, #humidity, #switch-state { color: #007bff; }
        .back-btn { padding: 10px 20px; font-size: 1em; margin-top: 20px; cursor: pointer; border: none; border-radius: 5px; background-color: #6c757d; color: white; }
        .back-btn:hover { background-color: #5a6268; }
    </style>
</head>
<body>
    <div class="container">
        <h1>센서 및 스위치 상태</h1>
        <div class="data-display">
            <p>온도: <span id="temperature">-</span> °C</p>
            <p>습도: <span id="humidity">-</span> %</p>
            <p>스위치: <span id="switch-state">-</span></p>
        </div>
        <button class="back-btn" onclick="window.location.href='/'">메인 페이지로 돌아가기</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.host + '/ws_sensor');
        ws.onmessage = function(event) {
            var data = event.data.split(',');
            if (data.length === 3) {
                document.getElementById('temperature').innerText = data[0];
                document.getElementById('humidity').innerText = data[1];
                var switchState = parseInt(data[2], 10) === 0 ? "ON" : "OFF";
                document.getElementById('switch-state').innerText = switchState;
            }
        };
    </script>
</body>
</html>
)**";

#endif

