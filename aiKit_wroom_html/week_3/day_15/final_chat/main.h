#pragma once
const char* main_HTML = R"**(
<!DOCTYPE html><html lang="ko"><head>
<meta charset="UTF-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>ESP32 메인</title>
<style>
  body{font-family:system-ui,Apple SD Gothic Neo,Noto Sans KR,sans-serif;background:#f6f8ff;margin:0;display:flex;min-height:100vh;color:#111}
  .wrap{margin:auto;width:min(720px,94vw);text-align:center}
  .card{background:#fff;border-radius:24px;box-shadow:0 8px 28px rgba(0,0,0,.08);padding:24px}
  h1{margin:.2em 0 .4em;font-size:clamp(22px,5vw,34px)}
  .subtitle{color:#555;margin-bottom:18px}
  .ssid{color:#2a57ff;font-weight:700}.ip{color:#0b8a55;font-weight:700}
  .grid{display:grid;grid-template-columns:1fr 1fr;gap:14px;margin-top:10px}
  a.btn{display:block;padding:16px;border-radius:14px;background:#2a57ff;color:#fff;text-decoration:none;font-size:18px}
  .status{margin-top:12px;color:#666}
</style></head><body><div class="wrap"><div class="card">
  <h1>ESP32 교실 메인</h1>
  <div class="subtitle">지금 <span class="ssid">"%SSID%"</span> AP에 연결됨 · IP <span class="ip">%APIP%</span></div>
  <div class="grid">
    <a class="btn" href="/led">LED 제어</a>
    <a class="btn" href="/display">디스플레이</a>
    <a class="btn" href="/sensor">센서·스위치</a>
    <a class="btn" href="/melody">멜로디·알람</a>
  </div>
  <div class="status">빠른 통신을 위해 WebSocket(:81)을 사용합니다.</div>
</div></div></body></html>
)**";


