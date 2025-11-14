#ifndef LEDCONTROL_H
#define LEDCONTROL_H

const char* led_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED 제어</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f0f0f0; }
        .container { background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); display: inline-block; }
        h1 { color: #333; }
        .led-control { margin-top: 20px; }
        .slider-container { margin-bottom: 15px; }
        label { font-size: 1.1em; color: #555; display: block; margin-bottom: 5px; }
        input[type="range"] { width: 80%; }
        button { padding: 10px 20px; font-size: 1em; margin-top: 20px; cursor: pointer; border: none; border-radius: 5px; background-color: #007bff; color: white; }
        button:hover { background-color: #0056b3; }
    </style>
</head>
<body>
    <div class="container">
        <h1>LED 제어</h1>
        <div class="led-control">
            <div class="slider-container">
                <label>빨간색 LED 밝기:</label>
                <input type="range" min="0" max="255" value="0" id="redSlider">
            </div>
            <div class="slider-container">
                <label>노란색 LED 밝기:</label>
                <input type="range" min="0" max="255" value="0" id="yellowSlider">
            </div>
            <div class="slider-container">
                <label>파란색 LED 밝기:</label>
                <input type="range" min="0" max="255" value="0" id="blueSlider">
            </div>
        </div>
        <button onclick="window.location.href='/'">메인 페이지로 돌아가기</button>
    </div>
    <script>
        var ws = new WebSocket('ws://' + window.location.host + '/ws_led');
        document.getElementById('redSlider').oninput = function() {
            ws.send('R' + this.value);
        };
        document.getElementById('yellowSlider').oninput = function() {
            ws.send('Y' + this.value);
        };
        document.getElementById('blueSlider').oninput = function() {
            ws.send('B' + this.value);
        };
    </script>
</body>
</html>
)**";

#endif