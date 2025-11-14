// myHtml.h
#pragma once

// %SSID% 와 %APIP% 는 서버에서 치환합니다.
const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>ESP32 AHT20 & SSD1306 교실</title>
  <style>
    :root { font-family: Pretendard, system-ui, -apple-system, Segoe UI, Roboto, "Apple SD Gothic Neo", "맑은 고딕", "Noto Sans KR", sans-serif; }
    body { margin:0; background:#f6f8ff; min-height:100vh; display:flex; color:#111; }
    .wrap { margin:auto; width:min(720px,94vw); }
    .card { background:#fff; border-radius:24px; box-shadow:0 8px 28px rgba(0,0,0,.08); padding:24px; }
    h1 { margin:.2em 0 .4em; font-size:clamp(22px,5vw,34px); text-align:center; }
    .subtitle { color:#555; text-align:center; margin-bottom:18px; }
    .ssid { font-weight:700; color:#2a57ff; } .ip { font-weight:700; color:#0b8a55; }
    .grid { display:grid; grid-template-columns:1fr 1fr; gap:16px; margin-top:16px; }
    .tile { border-radius:18px; padding:18px; background:#f3f6ff; text-align:center; }
    .big { font-size: clamp(30px, 7vw, 44px); font-weight:800; }
    .unit { font-size:16px; color:#555; margin-left:6px; }
    .tag { display:inline-block; padding:3px 10px; border-radius:999px; font-size:12px; background:#eef2ff; color:#334; }
    .status { text-align:center; margin-top:12px; color:#666; font-size:14px; }
    .row { margin-top:18px; display:flex; gap:10px; justify-content:center; }
    input[type=text] { width:min(480px,70vw); font-size:18px; padding:10px 12px; border:1px solid #d7dbff; border-radius:12px; }
    button { font-size:18px; padding:10px 16px; border:none; border-radius:12px; background:#2a57ff; color:#fff; cursor:pointer; }
    button:disabled{opacity:.6; cursor:not-allowed;}
    .hint { text-align:center; font-size:13px; color:#666; margin-top:8px; }
  </style>
</head>
<body>
  <div class="wrap">
    <div class="card">
      <div class="tag">ESP32 Wi-Fi AP 교실</div>
      <h1>🌤️ 온·습도 & 화면 문구 보내기</h1>
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

      <div class="row">
        <input id="line4" type="text" placeholder="4번째 줄에 보낼 문장을 입력하세요" maxlength="28"/>
        <button id="sendBtn" onclick="sendLine()">보내기</button>
      </div>
      <div class="hint">SSD1306 4번째 줄에 전송됩니다. (UTF-8 한글 지원)</div>

      <div class="status" id="status">웹소켓 연결 준비 중…</div>
    </div>
  </div>

<script>
(function(){
  const t = document.getElementById('t');
  const h = document.getElementById('h');
  const st = document.getElementById('status');
  const input = document.getElementById('line4');
  const sendBtn = document.getElementById('sendBtn');

  const wsUrl = (location.protocol === 'https:' ? 'wss://' : 'ws://') + location.hostname + ':81/';
  let ws;

  function connectWS(){
    st.textContent = '웹소켓 연결 중…';
    ws = new WebSocket(wsUrl);

    ws.onopen = () => {
      st.textContent = '연결됨! 1초마다 온·습도가 도착해요 😊';
      sendBtn.disabled = false;
    };

    ws.onmessage = (evt) => {
      try {
        const data = JSON.parse(evt.data);
        if (typeof data.t === 'number') t.textContent = data.t.toFixed(1);
        if (typeof data.h === 'number') h.textContent = data.h.toFixed(1);
      } catch(e) {
        // 텍스트일 수도 있으니 무시
      }
    };

    ws.onclose = () => {
      st.textContent = '연결 끊김. 다시 시도 중…';
      sendBtn.disabled = true;
      setTimeout(connectWS, 1000);
    };
    ws.onerror = () => {
      st.textContent = '오류 발생. 재연결 시도…';
      ws.close();
    };
  }

  window.sendLine = function(){
    if (!ws || ws.readyState !== 1) return;
    const msg = input.value || '';
    ws.send(JSON.stringify({ line4: msg }));
  };

  connectWS();
})();
</script>
</body>
</html>
)**";
