#pragma once
const char* sensor_HTML = R"**(
<!DOCTYPE html><html lang="ko"><head>
<meta charset="UTF-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>센서·스위치</title>
<style>
 body{font-family:system-ui,Noto Sans KR,sans-serif;background:#f6f8ff;margin:0;display:flex;min-height:100vh}
 .wrap{margin:auto;width:min(720px,94vw)}
 .card{background:#fff;border-radius:24px;box-shadow:0 8px 28px rgba(0,0,0,.08);padding:24px;text-align:center}
 .top{display:flex;gap:10px;justify-content:center;margin-bottom:12px}
 a.btn{padding:10px 16px;background:#777;color:#fff;border-radius:10px;text-decoration:none}
 .grid{display:grid;grid-template-columns:1fr 1fr;gap:14px}
 .tile{background:#f3f6ff;border-radius:16px;padding:16px}
 .big{font-size:34px;font-weight:800}
</style></head><body><div class="wrap"><div class="card">
  <div class="top"><a class="btn" href="/">메인으로</a></div>
  <h1>센서 & 스위치</h1>
  <div class="grid">
    <div class="tile">온도<div class="big"><span id="t">--.-</span>°C</div></div>
    <div class="tile">습도<div class="big"><span id="h">--.-</span>%</div></div>
  </div>
  <p>스위치(32): <b id="sw">알 수 없음</b></p>
</div></div>
<script>
 const t=document.getElementById('t'), h=document.getElementById('h'), sw=document.getElementById('sw');
 const wsUrl=(location.protocol==='https:'?'wss://':'ws://')+location.hostname+':81/';
 let ws; function connect(){ ws=new WebSocket(wsUrl);
   ws.onmessage=(e)=>{ try{ const d=JSON.parse(e.data);
     if(typeof d.t==='number') t.textContent=d.t.toFixed(1);
     if(typeof d.h==='number') h.textContent=d.h.toFixed(1);
     if(typeof d.sw==='boolean') sw.textContent=d.sw?'눌림(LOW)':'떼짐(HIGH)';
   }catch{} }; ws.onclose=()=>setTimeout(connect,800); } connect();
</script></body></html>
)**";
