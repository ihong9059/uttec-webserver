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
            margin: 40px;
            background-color: #f0f0f0;
        }
        .container {
            max-width: 600px;
            margin: 0 auto;
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        h1 {
            color: #333;
            text-align: center;
        }
        .info-box {
            background-color: #e8f5e8;
            padding: 20px;
            border-radius: 5px;
            margin: 20px 0;
        }
        .ip-address {
            font-size: 18px;
            font-weight: bold;
            color: #2c5aa0;
        }
        .ssid {
            font-size: 18px;
            font-weight: bold;
            color: #d35400;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 AP 모드 연결</h1>
        
        <div class="info-box">
            <p>현재 접속한 AP의 SSID:</p>
            <p class="ssid" id="ssid">로딩 중...</p>
        </div>
        
        <div class="info-box">
            <p>웹 서버 IP 주소:</p>
            <p class="ip-address">192.168.7.1</p>
        </div>
        
        <p>이 페이지는 ESP32-WROOM의 AP 모드에서 서비스되고 있습니다.</p>
    </div>

    <script>
        // 페이지 로드 시 SSID 정보를 서버에 요청
        window.addEventListener('load', function() {
            fetch('/getSSID')
                .then(response => response.text())
                .then(ssid => {
                    document.getElementById('ssid').textContent = ssid;
                })
                .catch(error => {
                    console.error('SSID 정보를 가져오는 중 오류 발생:', error);
                    document.getElementById('ssid').textContent = '정보를 가져올 수 없음';
                });
        });
    </script>
</body>
</html>
)**";

#endif