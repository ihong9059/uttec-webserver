#pragma once

const char* main_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>ESP32 메인 제어판</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: "Noto Sans KR", sans-serif; margin:20px; background:#f0f8ff; text-align:center; }
    h1 { margin:0 0 20px; font-size:28px; }
    .grid { display:grid; grid-template-columns:repeat(auto-fit, minmax(150px, 1fr)); gap:20px; }
    .btn {
      display:flex; flex-direction:column; align-items:center; justify-content:center;
      padding:30px; font-size:22px; font-weight:bold;
      border-radius:20px; border:none; cursor:pointer;
      box-shadow:0 4px 10px rgba(0,0,0,0.2);
      transition:transform 0.2s;
    }
    .btn:hover { transform:scale(1.05); }
    .led { background:#ffe5e5; color:#c00; }
    .disp { background:#e5f0ff; color:#0040c0; }
    .sensor { background:#e8ffe8; color:#008000; }
    .melody { background:#fff0e5; color:#b85c00; }
    .ssid { margin:20px 0; font-size:20px; font-weight:bold; }
    .badge { background:#fff; border:1px solid #ccc; padding:6px 12px; border-radius:8px; }
  </style>
</head>
<body>
  <h1>🌟 ESP32 제어판 🌟</h1>
  <div class="ssid">📶 AP SSID: <span id="ssid" class="badge">연결 대기...</span></div>
  <div class="grid">
    <button class="btn led" onclick="location.href='/led'">💡 LED 제어</button>
    <button class="btn disp" onclick="location.href='/display'">🖥 디스플레이</button>
    <button class="btn sensor" onclick="location.href='/sensor'">🌡 센서 & 스위치</button>
    <button class="btn melody" onclick="location.href='/melody'">🎵 멜로디</button>
  </div>

  <script>
    let ws;
    function connectWS() {
      const proto = (location.protocol === 'https:') ? 'wss://' : 'ws://';
      ws = new WebSocket(proto + location.host + '/ws');
      ws.onopen = () => { setTimeout(() => { try { ws.send('GET_SSID'); } catch(e){} }, 200); };
      ws.onmessage = (ev) => {
        if (ev.data.startsWith('SSID:')) {
          document.getElementById('ssid').textContent = ev.data.substring(5);
        }
      };
      ws.onclose = () => setTimeout(connectWS, 1000);
    }
    connectWS();
  </script>
</body>
</html>
)**";

