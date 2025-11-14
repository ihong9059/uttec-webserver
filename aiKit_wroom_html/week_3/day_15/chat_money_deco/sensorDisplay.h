#pragma once
const char* sensor_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>센서</title>
<style>
 body{font-family:Arial;text-align:center;background:#f4fff2;padding:20px}
 h2{font-size:24px}
 .box{display:inline-block;width:140px;height:120px;margin:10px;padding:10px;border-radius:20px;background:#fff;box-shadow:0 4px 8px rgba(0,0,0,.1)}
 .big{font-size:28px;font-weight:700;margin:10px 0}
 .label{font-size:18px;color:#555}
 button{margin-top:15px;padding:12px 20px;font-size:18px;border-radius:12px;background:#2ecc71;color:#fff;border:none}
 a{display:block;margin-top:20px;text-decoration:none;color:#333;font-size:18px}
</style>
</head>
<body>
<h2>🌡 센서와 🔘 스위치</h2>
<div class="box"><div class="label">온도</div><div id="t" class="big">--</div>℃</div>
<div class="box"><div class="label">습도</div><div id="h" class="big">--</div>%</div>
<div class="box"><div class="label">스위치</div><div id="sw" class="big">--</div></div>
<br>
<button id="refresh">지금 읽기</button>
<a href="/">← 메인으로</a>
<script>
let ws=new WebSocket(`ws://${location.host}/ws`);
ws.onmessage=(ev)=>{let m=JSON.parse(ev.data);
 if(m.type==="SENSOR_DATA"){document.getElementById('t').textContent=m.t.toFixed(1);
   document.getElementById('h').textContent=m.h.toFixed(1);
   document.getElementById('sw').textContent=m.sw? "해제":"눌림";}};
document.getElementById("refresh").onclick=()=>{ws.send(JSON.stringify({type:"SENSOR_NOW"}));};
</script>
</body>
</html>
)**";

