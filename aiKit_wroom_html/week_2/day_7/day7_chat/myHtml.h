const char* my_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 AP Mode</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f0f0f0;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
    }
    .box {
      background: white;
      padding: 30px;
      border-radius: 12px;
      box-shadow: 0 4px 8px rgba(0,0,0,0.2);
      text-align: center;
    }
    h1 {
      color: #333;
    }
    p {
      font-size: 18px;
      color: #555;
    }
  </style>
</head>
<body>
  <div class="box">
    <h1>연결된 SSID: __SSID__</h1>
    <p>AP IP 주소: __IP__</p>
  </div>
</body>
</html>
)**";
