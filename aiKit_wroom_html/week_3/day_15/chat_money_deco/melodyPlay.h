#pragma once
const char* melody_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>멜로디</title>
<style>
 body{font-family:Arial;text-align:center;background:#f0f8ff;padding:20px}
 h2{font-size:24px}
 .grid{display:grid;gap:15px;grid-template-columns:1fr 1fr;max-width:400px;margin:auto}
 button{padding:20px;font-size:20px;border:none;border-radius:16px;background:#8e44ad;color:#fff}
 button.alarm{background:#e74c3c}
 a{display:block;margin-top:20px;text-decoration:none;color:#333;font-size:18px}
</style>
</head>
<body>
<h2>🎵 소리 실험 🎵</h2>
<p>버튼을 눌러 소리를 들어보세요.</p>
<div class="grid">
  <button class="alarm" id="alarm">⏰ 알람</button>
  <button onclick="play(1)">🎶 아침 산책</button>
  <button onclick="play(2)">🌞 맑은 날</button>
  <button onclick="play(3)">🌙 밤하늘</button>
  <button onclick="play(4)">🎉 작은 축제</button>
</div>
<a href="/">← 메인으로</a>
<script>
let ws=new WebSocket(`ws://${location.host}/ws`);
document.getElementById("alarm").onclick=()=>{ws.send(JSON.stringify({type:"ALARM_BEEP"}));};
function play(no){ws.send(JSON.stringify({type:"MELODY_PLAY",no}));}
</script>
</body>
</html>
)**";

