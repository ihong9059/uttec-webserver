#pragma once

const char* melody_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>멜로디 제어</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body{font-family:"Noto Sans KR",sans-serif;margin:20px;background:#fff8f0;text-align:center;}
    h1{margin:0 0 20px;font-size:26px;}
    .row{margin:15px 0;}
    button{padding:16px 24px;font-size:20px;border-radius:14px;border:none;cursor:pointer;box-shadow:0 4px 8px rgba(0,0,0,0.2);}
    .alarm{background:#ff4d4d;color:white;}
    .song{background:#ffdd99;}
  </style>
</head>
<body>
  <h1>🎵 멜로디 제어</h1>
  <div class="row"><button onclick="location.href='/'">🏠 메인으로</button></div>
  <div class="row"><button class="alarm" onclick="sendCmd('ALARM')">🚨 Alarm</button></div>
  <div class="row"><button class="song" onclick="sendCmd('MELODY:1')">🎵 멜로디 1</button></div>
  <div class="row"><button class="song" onclick="sendCmd('MELODY:2')">🎵 멜로디 2</button></div>
  <div class="row"><button class="song" onclick="sendCmd('MELODY:3')">🎵 멜로디 3</button></div>
  <div class="row"><button class="song" onclick="sendCmd('MELODY:4')">🎵 멜로디 4</button></div>

  <script>
    let ws;
    function connectWS(){const proto=(location.protocol==='https:')?'wss://':'ws://';ws=new WebSocket(proto+location.host+'/ws');ws.onclose=()=>setTimeout(connectWS,1000);}
    function sendCmd(cmd){try{ws.send(cmd);}catch(e){}}
    connectWS();
  </script>
</body>
</html>
)**";

