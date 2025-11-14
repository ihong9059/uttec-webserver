// myHtml.h
#ifndef MYHTML_H
#define MYHTML_H

const char* my_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 AP 모드</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin: 50px;
            background-color: #f0f0f0;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            max-width: 500px;
            margin: 0 auto;
        }
        h1 {
            color: #333;
        }
        .ssid {
            font-size: 24px;
            font-weight: bold;
            color: #007bff;
            margin: 20px 0;
            padding: 10px;
            background-color: #e9ecef;
            border-radius: 5px;
        }
        .info {
            color: #666;
            font-size: 14px;
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 WiFi AP에 접속되었습니다</h1>
        <p>현재 연결된 AP의 SSID:</p>
        <div class="ssid" id="ssidDisplay">로딩 중...</div>
        <p class="info">이 페이지는 ESP32-WROOM에서 호스팅됩니다</p>
    </div>

    <script>
        // 페이지 로드 시 SSID 정보 요청
        window.onload = function() {
            fetch('/getssid')
                .then(response => response.text())
                .then(ssid => {
                    document.getElementById('ssidDisplay').textContent = ssid;
                })
                .catch(error => {
                    console.error('Error:', error);
                    document.getElementById('ssidDisplay').textContent = '오류 발생';
                });
        };
    </script>
</body>
</html>
)**";

#endif