#pragma once
const char* main_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>UTTEC 시스템 메인</title>
<style>
 body{font-family:Arial,Helvetica,sans-serif;text-align:center;background:#fdf6e3;margin:0;padding:20px}
 h1{font-size:28px;color:#333;margin:10px 0}
 .ssid{font-size:20px;margin:15px 0;color:#444}
 .menu{display:grid;gap:20px;grid-template-columns:1fr 1fr;max-width:500px;margin:20px auto}
 a.btn{padding:30px 10px;font-size:20px;border-radius:20px;text-decoration:none;color:#fff;box-shadow:0 4px 10px rgba(0,0,0,.2)}
 a.red{background:#e74c3c}
 a.blue{background:#3498db}
 a.green{background:#27ae60}
 a.yellow{background:#f1c40f;color:#333}
 footer{margin-top:20px;color:#777;font-size:14px}
</style>
</head>
<body>
<h1>✨ UTTEC AI 놀이터 ✨</h1>
<div class="ssid">📡 WiFi 이름: <span id="ssid">연결 중...</span></div>
<div class="menu">
  <a href="/led" class="btn red">💡 LED</a>
  <a href="/display" class="btn blue">🖥 디스플레이</a>
  <a href="/sensor" class="btn yellow">🌡 센서</a>
  <a href="/melody" class="btn green">🎵 멜로디</a>
</div>
<h1>즐겁게 실험해 보세요!</h1>
<script>
let ws=new WebSocket(`ws://${location.host}/ws`);
ws.onmessage=(ev)=>{try{let m=JSON.parse(ev.data);if(m.type==="SSID"){document.getElementById("ssid").textContent=m.ssid;}}catch(e){}}; 
</script>
</body>
</html>
)**";

