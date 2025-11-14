#ifndef MYHTML_H
#define MYHTML_H

const char* my_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 AP Mode</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
    h1 { color: #2c3e50; }
    p  { font-size: 20px; }
  </style>
</head>
<body>
  <h1>ESP32 WiFi AP 모드</h1>
  <p>연결된 SSID: <b>{{SSID}}</b></p>
</body>
</html>
)**";

#endif
