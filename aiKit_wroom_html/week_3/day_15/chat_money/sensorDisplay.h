#pragma once
const char* sensor_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>센서/스위치</title>
<style>
  body{font-family:system-ui,Segoe UI,Roboto,Apple SD Gothic Neo,Malgun Gothic,sans-serif;margin:24px}
  .wrap{max-width:720px;margin:auto}
  .top{display:flex;gap:8px;margin-bottom:16px;align-items:center}
  a.btn{padding:8px 12px;border:1px solid #ccc;border-radius:10px;text-decoration:none}
  .card{border:1px solid #ddd;border-radius:16px;padding:16px;box-shadow:0 6px 20px rgba(0,0,0,.08)}
  .grid{display:grid;grid-template-columns:1fr 1fr;gap:12px}
  .tile{padding:16px;border:1px solid #eee;border-radius:12px;text-align:center}
  .big{font-size:28px;font-weight:700}
  .sm{color:#666}
</style>
</head>
<body>
<div class="wrap">
  <div class="top">
    <a class="btn" href="/">← 메인</a>
    <h2 style="margin:0">센서 & 스위치 상태</h2>
  </div>
  <div class="card">
    <div class="grid">
      <div class="tile"><div class="sm">온도(℃)</div><div id="t" class="big">--</div></div>
      <div class="tile"><div class="sm">습도(%)</div><div id="h" class="big">--</div></div>
      <div class="tile"><div class="sm">스위치</div><div id="sw" class="big">--</div></div>
      <div class="tile"><button id="refresh">지금 읽기</button></div>
    </div>
  </div>
</div>
<script>
let ws;
function connectWs(){
  ws = new WebSocket(`ws://${location.host}/ws`);
  ws.onmessage=(ev)=>{
    try{
      const m=JSON.parse(ev.data);
      if(m.type==="SENSOR_DATA"){
        if(typeof m.t==="number") document.getElementById('t').textContent=m.t.toFixed(1);
        if(typeof m.h==="number") document.getElementById('h').textContent=m.h.toFixed(1);
        if(typeof m.sw!=="undefined") document.getElementById('sw').textContent = (m.sw? "해제(1)":"눌림(0)");
      }
    }catch(e){}
  };
}
connectWs();
document.getElementById('refresh').onclick=()=>{
  ws?.send(JSON.stringify({type:"SENSOR_NOW"}));
};
</script>
</body>
</html>
)**";
