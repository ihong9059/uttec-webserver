#pragma once
const char* main_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>UTTEC 시스템 개요</title>
<style>
  body{font-family:system-ui,Segoe UI,Roboto,Apple SD Gothic Neo,Malgun Gothic,sans-serif;margin:24px}
  .card{max-width:720px;margin:auto;padding:20px;border:1px solid #ddd;border-radius:16px;box-shadow:0 6px 20px rgba(0,0,0,.08)}
  h1{margin:0 0 8px}
  .ssid{font-size:18px;color:#555;margin-bottom:16px}
  .grid{display:grid;gap:12px;grid-template-columns:repeat(auto-fit,minmax(160px,1fr));margin-top:16px}
  a.btn{display:block;text-align:center;padding:14px 16px;border-radius:12px;border:1px solid #ccc;text-decoration:none}
  a.btn:hover{background:#f5f5f5}
  .badge{display:inline-block;padding:4px 10px;border-radius:999px;background:#eef;border:1px solid #99f;margin-left:8px}
  footer{margin-top:18px;color:#777;font-size:12px}
</style>
</head>
<body>
<div class="card">
  <h1>ESP32 시스템 메인</h1>
  <div class="ssid">AP SSID: <strong id="ssid">연결 중...</strong><span class="badge">WebSocket</span></div>
  <p>아래에서 각 기능 테스트 페이지로 이동하세요.</p>
  <div class="grid">
    <a class="btn" href="/led">LED 제어</a>
    <a class="btn" href="/display">SSD1306 디스플레이</a>
    <a class="btn" href="/sensor">센서/스위치 보기</a>
    <a class="btn" href="/melody">알람/멜로디</a>
  </div>
  <footer>© UTTEC Lab AI</footer>
</div>

<script>
let ws;
function connectWs(){
  ws = new WebSocket(`ws://${location.host}/ws`);
  ws.onmessage = (ev)=>{
    try{
      const m = JSON.parse(ev.data);
      if(m.type==="SSID"){ document.getElementById('ssid').textContent = m.ssid; }
    }catch(e){}
  };
}
connectWs();
</script>
</body>
</html>
)**";
