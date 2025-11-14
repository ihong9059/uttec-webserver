#pragma once
const char* display_HTML = R"**(
<!DOCTYPE html><html lang="ko"><head>
<meta charset="UTF-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>디스플레이</title>
<style>
 body{font-family:system-ui,Noto Sans KR,sans-serif;background:#f6f8ff;margin:0;display:flex;min-height:100vh}
 .wrap{margin:auto;width:min(720px,94vw)}
 .card{background:#fff;border-radius:24px;box-shadow:0 8px 28px rgba(0,0,0,.08);padding:24px}
 .top{display:flex;gap:10px;justify-content:center;margin-bottom:12px}
 a.btn{padding:10px 16px;background:#777;color:#fff;border-radius:10px;text-decoration:none}
 .row{display:flex;gap:10px;margin:8px 0;justify-content:center}
 input{width:min(520px,75vw);padding:10px 12px;border:1px solid #d7dbff;border-radius:12px;font-size:16px}
 button{padding:10px 14px;border:none;border-radius:12px;background:#2a57ff;color:#fff}
</style></head><body><div class="wrap"><div class="card">
  <div class="top"><a class="btn" href="/">메인으로</a></div>
  <h1>SSD1306(4줄) 텍스트 전송</h1>
  <div class="row"><input id="l1" placeholder="1행" value="UTTEC Lab Ai"><button onclick="send()">보내기</button></div>
  <div class="row"><input id="l2" placeholder="2행" value="2번째 line"></div>
  <div class="row"><input id="l3" placeholder="3행" value="3번째 line"></div>
  <div class="row"><input id="l4" placeholder="4행" value="환영 합니다"></div>
</div></div>
<script>
 const wsUrl=(location.protocol==='https:'?'wss://':'ws://')+location.hostname+':81/';
 let ws; function connect(){ ws=new WebSocket(wsUrl); ws.onclose=()=>setTimeout(connect,800); } connect();
 function send(){ if(ws&&ws.readyState===1){
   ws.send(JSON.stringify({cmd:'display', l1:document.getElementById('l1').value,
     l2:document.getElementById('l2').value, l3:document.getElementById('l3').value, l4:document.getElementById('l4').value}));
 } }
</script></body></html>
)**";
