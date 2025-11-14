#ifndef MYHTML_H
#define MYHTML_H

const char* red_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>ESP32 LED 제어</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin: 50px;
            background-color: #f0f0f0;
        }
        .container {
            background: white;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
            max-width: 400px;
            margin: 0 auto;
        }
        h1 {
            color: #333;
            margin-bottom: 20px;
        }
        .ssid-info {
            background: #e8f5e8;
            padding: 15px;
            border-radius: 8px;
            margin: 20px 0;
            border: 2px solid #4caf50;
        }
        .button-container {
            margin: 25px 0;
        }
        .btn {
            padding: 12px 25px;
            margin: 0 10px;
            border: none;
            border-radius: 25px;
            cursor: pointer;
            font-size: 16px;
            font-weight: bold;
            transition: all 0.3s;
        }
        .btn-on {
            background: #4caf50;
            color: white;
        }
        .btn-on:hover {
            background: #45a049;
            transform: scale(1.05);
        }
        .btn-off {
            background: #f44336;
            color: white;
        }
        .btn-off:hover {
            background: #da190b;
            transform: scale(1.05);
        }
        .status {
            margin-top: 20px;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        .on { background: #d4edda; color: #155724; }
        .off { background: #f8d7da; color: #721c24; }
    </style>
</head>
<body>
    <div class='container'>
        <h1>🔴 RED LED 제어</h1>
        
        <div class='ssid-info'>
            <h3>📶 접속된 AP 정보</h3>
            <p><strong>SSID:</strong> {{SSID}}</p>
        </div>

        <div class='button-container'>
            <button class='btn btn-on' onclick='controlLED("on")'>LED 켜기</button>
            <button class='btn btn-off' onclick='controlLED("off")'>LED 끄기</button>
        </div>

        <div id='status' class='status off'>현재 상태: LED 꺼짐</div>
    </div>

    <script>
        function controlLED(state) {
            fetch('/led?state=' + state)
                .then(response => response.text())
                .then(data => {
                    const statusDiv = document.getElementById('status');
                    if (state === 'on') {
                        statusDiv.textContent = '현재 상태: LED 켜짐';
                        statusDiv.className = 'status on';
                    } else {
                        statusDiv.textContent = '현재 상태: LED 꺼짐';
                        statusDiv.className = 'status off';
                    }
                })
                .catch(error => console.error('Error:', error));
        }
    </script>
</body>
</html>
)**";

#endif