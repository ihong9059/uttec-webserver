#pragma once

const char* display_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>디스플레이 제어</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family:"Noto Sans KR", sans-serif; margin:20px; background:#eef7ff; text-align:center; }
    h1 { margin:0 0 20px; font-size:26px; }
    .row { margin:10px 0; }
    input[type=text]{width:90%; padding:12px; font-size:18px; border-radius:8px; border:1px solid #ccc;}
    button{padding:14px 20px; margin-top:10px; font-size:18px; border-radius:12px; border:none; background:#4da6ff; color:white; cursor:pointer;}
  </style>
</head>
<body>
  <h1>🖥 디스플레이 제어</h1>
  <div class="row"><button onclick="location.href='/'">🏠 메인으로</button></div>
  <hr>
  <form onsubmit="sendLines(); return false;">
    <div class="row">1행: <input id="line1" type="text" value="UTTEC Lab Ai"></div>
    <div class="row">2행: <input id="line2" type="text" value="2번째 line"></div>
    <div class="row">3행: <input id="line3" type="text" value="3번째 line"></div>
    <div class="row">4행: <input id="line4" type="text" value="환영 합니다"></div>
    <div class="row"><button type="submit">📤 화면에 보내기</button></div>
  </form>

  <script>
    let ws;
    function connectWS(){const proto=(location.protocol==='https:')?'wss://':'ws://';ws=new WebSocket(proto+location.host+'/ws');ws.onclose=()=>setTimeout(connectWS,1000);}
    function sendLines(){try{ws.send("DISP:1:"+line1.value);ws.send("DISP:2:"+line2.value);ws.send("DISP:3:"+line3.value);ws.send("DISP:4:"+line4.value);}catch(e){}}
    connectWS();
  </script>
</body>
</html>
)**";

