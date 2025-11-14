const char* red_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>ESP32 LED 제어</title>
  <style>
    body { text-align: center; font-family: Arial, sans-serif; margin-top: 50px; }
    h1 { color: red; }
    button { font-size: 20px; padding: 10px 20px; margin: 10px; }
  </style>
</head>
<body>
  <h1>ESP32 WiFi AP: 홍길도</h1>
  <p>Red LED 제어</p>
  <button onclick="location.href='/ledon'">LED 켜기</button>
  <button onclick="location.href='/ledoff'">LED 끄기</button>
</body>
</html>
)**";
