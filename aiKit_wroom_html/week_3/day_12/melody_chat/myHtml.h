#pragma once

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>ESP32 멜로디 교실</title>
  <style>
    body { font-family: sans-serif; text-align:center; margin-top:40px; }
    button { font-size:20px; margin:10px; padding:12px 20px;
             background:#4caf50; color:#fff; border:none; border-radius:10px; cursor:pointer; }
  </style>
</head>
<body>
  <h1>🎵 ESP32 멜로디 재생</h1>
  <p>AP SSID: <b>%SSID%</b><br>IP: <b>%APIP%</b></p>

  <button onclick="playMelody(1)">멜로디 1</button>
  <button onclick="playMelody(2)">멜로디 2</button>
  <button onclick="playMelody(3)">멜로디 3</button>
  <button onclick="playMelody(4)">멜로디 4</button>
  <button onclick="playMelody(5)">멜로디 5</button>
  <button onclick="playMelody(6)">멜로디 6</button>

  <script>
    async function playMelody(id){
      await fetch("/melody?id="+id);
    }
  </script>
</body>
</html>
)**";
