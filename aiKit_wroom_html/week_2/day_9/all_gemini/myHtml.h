const char* all_HTML = R"rawliteral(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 AP 컨트롤</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
            color: #333;
        }
        .container {
            background-color: #fff;
            padding: 30px;
            border-radius: 12px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            text-align: center;
            max-width: 400px;
            width: 90%;
        }
        h1 {
            color: #4CAF50;
            font-size: 24px;
        }
        p {
            font-size: 18px;
            margin: 10px 0;
        }
        .button-row {
            display: flex;
            justify-content: space-around;
            margin-top: 20px;
            flex-wrap: wrap;
        }
        .button {
            border: none;
            color: white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 5px;
            cursor: pointer;
            border-radius: 8px;
            transition: background-color 0.3s;
        }
        .button.red-on, .button.red-off { background-color: #f44336; }
        .button.yellow-on, .button.yellow-off { background-color: #ffc107; }
        .button.blue-on, .button.blue-off { background-color: #2196F3; }
        .button:hover { opacity: 0.8; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 AP 모드</h1>
        <p>AP 이름: <span style="font-weight: bold;">홍길동</span></p>
        <div class="button-row">
            <a href="/control_led?color=red&action=on" class="button red-on">빨강 ON</a>
            <a href="/control_led?color=red&action=off" class="button red-off">빨강 OFF</a>
        </div>
        <div class="button-row">
            <a href="/control_led?color=yellow&action=on" class="button yellow-on">노랑 ON</a>
            <a href="/control_led?color=yellow&action=off" class="button yellow-off">노랑 OFF</a>
        </div>
        <div class="button-row">
            <a href="/control_led?color=blue&action=on" class="button blue-on">파랑 ON</a>
            <a href="/control_led?color=blue&action=off" class="button blue-off">파랑 OFF</a>
        </div>
    </div>
</body>
</html>
)rawliteral";