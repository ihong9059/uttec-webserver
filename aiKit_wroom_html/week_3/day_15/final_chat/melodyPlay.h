#pragma once
const char* melody_HTML = R"**(
<!DOCTYPE html><html lang="ko"><head>
<meta charset="UTF-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>멜로디 & 알람</title>
<style>
 body{font-family:system-ui,Noto Sans KR,sans-serif;background:#f6f8ff;margin:0;display:flex;min-height:100vh}
 .wrap{margin:auto;width:min(720px,94vw);text-align:center}
 .card{background:#fff;border-radius:24px;box-shadow:0 8px 28px rgba(0,0,0,.08);padding:24px}
 .top{display:flex;gap:10px;justify-content:center;margin-bottom:12px}
 a.btn{padding:10px 16px;background:#777;color:#fff;border-radius:10px;text-decoration:none}
 .grid{display:grid;grid-template-columns:1fr 1fr;gap:12px;margin-top:10px}
 button{padding:14px 16px;border:none;border-radius:12px;background:#2a57ff;color:#fff;font-size:16px}
</style></head><body><div class="wrap"><div class="card">
  <div class="top"><a class="btn" href="/">메인으로</a></div>
  <h1>멜로디 & 알람</h1>
  <button onclick="alarm()">🔔 알람(0.5초)</button>
  <div class="grid">
    <button onclick="mel(1)">🌟 작은별</button>
    <button onclick="mel(2)">🎵 학교종</button>
    <button onclick="mel(3)">🎶 도레미</button>
    <button onclick="mel(4)">🎼 코드순환</button>
  </div>
</div></div>
<script>
 const wsUrl=(location.protocol==='https:'?'wss://':'ws://')+location.hostname+':81/'; let ws;
 function connect(){ ws=new WebSocket(wsUrl); ws.onclose=()=>setTimeout(connect,800); } connect();
 function alarm(){ if(ws&&ws.readyState===1) ws.send(JSON.stringify({cmd:'alarm'})); }
 function mel(id){ if(ws&&ws.readyState===1) ws.send(JSON.stringify({cmd:'melody',id:id})); }
</script></body></html>
)**";
