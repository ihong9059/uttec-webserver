const char* myHtml = R"rawliteral(
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
        }
        h1 {
            color: #4CAF50;
            font-size: 24px;
        }
        p {
            font-size: 18px;
            margin: 10px 0;
        }
        .button-group {
            margin-top: 20px;
        }
        .button {
            background-color: #008CBA;
            border: none;
            color: white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 8px;
            cursor: pointer;
            border-radius: 8px;
            transition: background-color 0.3s;
        }
        .button.on {
            background-color: #4CAF50;
        }
        .button.off {
            background-color: #f44336;
        }
        .button:hover {
            opacity: 0.8;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 AP 모드</h1>
        <p>AP 이름: <span style="font-weight: bold;">홍길동</span></p>
        <p>이 웹페이지는 ESP32의 AP에 연결되었습니다.</p>
        <div class="button-group">
            <a href="/led_on" class="button on">LED 켜기</a>
            <a href="/led_off" class="button off">LED 끄기</a>
        </div>
    </div>
</body>
</html>
)rawliteral";
