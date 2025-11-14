#pragma once

const char* led_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>LED 제어</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: "Noto Sans KR", sans-serif; margin:20px; background:#fffbe6; text-align:center; }
    h1 { margin:0 0 20px; font-size:26px; }
    .back { margin-bottom:20px; }
    .ledbox { border:1px solid #ccc; border-radius:16px; padding:20px; margin:15px 0; }
    button { padding:14px 20px; margin:5px; font-size:18px; border-radius:12px; border:none; cursor:pointer; }
    .red { background:#ff4d4d; color:white; }
    .yellow { background:#ffd633; }
    .blue { background:#4da6ff; color:white; }
  </style>
</head>
<body>
  <h1>💡 LED 제어</h1>
  <div class="back"><button onclick="location.href='/'">🏠 메인으로</button></div>

  <div class="ledbox">
    <h2>🔴 RED LED</h2>
    <button class="red" onclick="send('LED:RED:ON')">켜기</button>
    <button onclick="send('LED:RED:OFF')">끄기</button>
    <input type="range" min="0" max="255" value="0" oninput="onRange('RED',this.value)">
    <div>밝기: <span id="valRED">0</span></div>
  </div>

  <div class="ledbox">
    <h2>🟡 YELLOW LED</h2>
    <button class="yellow" onclick="send('LED:YELLOW:ON')">켜기</button>
    <button onclick="send('LED:YELLOW:OFF')">끄기</button>
    <input type="range" min="0" max="255" value="0" oninput="onRange('YELLOW',this.value)">
    <div>밝기: <span id="valYELLOW">0</span></div>
  </div>

  <div class="ledbox">
    <h2>🔵 BLUE LED</h2>
    <button class="blue" onclick="send('LED:BLUE:ON')">켜기</button>
    <button onclick="send('LED:BLUE:OFF')">끄기</button>
    <input type="range" min="0" max="255" value="0" oninput="onRange('BLUE',this.value)">
    <div>밝기: <span id="valBLUE">0</span></div>
  </div>

  <script>
    let ws;
    const valSpan = {RED:document.getElementById('valRED'),YELLOW:document.getElementById('valYELLOW'),BLUE:document.getElementById('valBLUE')};
    function connectWS(){const proto=(location.protocol==='https:')?'wss://':'ws://';ws=new WebSocket(proto+location.host+'/ws');ws.onclose=()=>setTimeout(connectWS,1000);}
    function send(msg){try{ws.send(msg);}catch(e){}}
    function onRange(which,value){valSpan[which].textContent=value;send('PWM:'+which+':'+value);}
    connectWS();
  </script>
</body>
</html>
)**";

