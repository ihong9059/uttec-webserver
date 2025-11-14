// myHtml.h
#pragma once

// %SSID% 와 %APIP% 는 서버에서 치환합니다.
const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>ESP32 AHT20 교실</title>
  <style>
    :root { font-family: Pretendard, system-ui, -apple-system, Segoe UI, Roboto, Apple SD Gothic Neo, "맑은 고딕", Noto Sans KR, sans-serif; }
    body { margin:0; background:#f6f8ff; min-height:100vh; display:flex; color:#111; }
    .wrap { margin:auto; width:min(720px,94vw); }
    .card { background:#fff; border-radius:24px; box-shadow:0 8px 28px rgba(0,0,0,.08); padding:24px; }
    h1 { margin:.2em 0 .4em; font-size:clamp(22px,5vw,34px); text-align:center; }
    .subtitle { color:#555; text-align:center; margin-bottom:18px; }
    .ssid { font-weight:700; color:#2a57ff; } .ip { font-weight:700; color:#0b8a55; }
    .grid { display:grid; grid-template-columns:1fr 1fr; gap:16px; margin-top:16px; }
    .tile { border-radius:18px; padding:18px; background:#f3f6ff; text-align:center; }
    .big { font-size: clamp(28px, 7vw, 42px); font-weight:800; }
    .unit { font-size:16px; color:#555; margin-left:6px; }
    .tag { display:inline-block; padding:3px 10px; border-radius:999px; font-size:12px; background:#eef2ff; color:#334; }
    .status { text-align:center; margin-top:12px; color:#666; font-size:14px; }
  </style>
</head>
<body>
  <div class="wrap">
    <div class="card">
      <div class="tag">ESP32 Wi-Fi AP 교실</div>
      <h1>🌤️ 온·습도 라이브 보기</h1>
      <div class="subtitle">
        지금 <span class="ssid">"%SSID%"</span> AP에 연결되어 있어요.<br />
        ESP32 주소: <span class="ip">%APIP%</span>
      </div>

      <div class="grid">
        <div class="tile">
          <div>온도</div>
          <div class="big"><span id="t">--.-</span><span class="unit">°C</span></div>
        </div>
        <div class="tile">
          <div>습도</div>
          <div class="big"><span id="h">--.-</span><span class="unit">%</span></div>
        </div>
      </div>

      <div class="status" id="status">연결 준비 중…</div>
    </div>
  </div>

<script>
(function(){
  const t = document.getElementById('t');
  const h = document.getElementById('h');
  const st = document.getElementById('status');

  // 같은 호스트 기준으로 WS 포트(81) 연결
  const wsUrl = (location.protocol === 'https:' ? 'wss://' : 'ws://') + location.hostname + ':81/';
  let ws;

  function connectWS(){
    st.textContent = '웹소켓 연결 중…';
    ws = new WebSocket(wsUrl);
    ws.onopen = () => { st.textContent = '연결됨! 1초마다 데이터가 와요 😊'; };
    ws.onmessage = (evt) => {
      try {
        const data = JSON.parse(evt.data);
        if (typeof data.t === 'number') t.textContent = data.t.toFixed(1);
        if (typeof data.h === 'number') h.textContent = data.h.toFixed(1);
      } catch(e) {
        // 텍스트일 수도 있음
      }
    };
    ws.onclose = () => { st.textContent = '연결 끊김. 다시 시도 중…'; setTimeout(connectWS, 1000); };
    ws.onerror = () => { st.textContent = '오류 발생. 재연결 시도…'; ws.close(); };
  }

  connectWS();
})();
</script>
</body>
</html>
)**";
