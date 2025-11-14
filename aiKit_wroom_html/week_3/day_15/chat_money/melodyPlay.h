#pragma once
const char* melody_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>알람 & 멜로디</title>
<style>
  body{font-family:system-ui,Segoe UI,Roboto,Apple SD Gothic Neo,Malgun Gothic,sans-serif;margin:24px}
  .wrap{max-width:720px;margin:auto}
  .top{display:flex;gap:8px;margin-bottom:16px;align-items:center}
  a.btn{padding:8px 12px;border:1px solid #ccc;border-radius:10px;text-decoration:none}
  .grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(160px,1fr));gap:12px}
  button{padding:12px;border-radius:12px;border:1px solid #bbb}
</style>
</head>
<body>
<div class="wrap">
  <div class="top">
    <a class="btn" href="/">← 메인</a>
    <h2 style="margin:0">알람 & 멜로디 재생</h2>
  </div>
  <div class="grid">
    <button id="alarm">알람(0.5초 Beep)</button>
    <button onclick="play(1)">아침 산책</button>
    <button onclick="play(2)">맑은 날</button>
    <button onclick="play(3)">밤하늘</button>
    <button onclick="play(4)">작은 축제</button>
  </div>
</div>
<script>
let ws;
function connectWs(){ ws=new WebSocket(`ws://${location.host}/ws`); }
connectWs();
document.getElementById('alarm').onclick=()=>{
  ws?.send(JSON.stringify({type:"ALARM_BEEP"}));
};
function play(no){
  ws?.send(JSON.stringify({type:"MELODY_PLAY", no}));
}
</script>
</body>
</html>
)**";
