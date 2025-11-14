#pragma once

const char* sensor_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>센서 & 스위치 상태</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body{font-family:"Noto Sans KR",sans-serif;margin:20px;background:#f9fff0;text-align:center;}
    h1{margin:0 0 20px;font-size:26px;}
    .card{border:1px solid #ccc;border-radius:16px;padding:20px;margin:15px 0;font-size:22px;box-shadow:0 4px 8px rgba(0,0,0,0.1);}
    .value{font-weight:bold;font-size:26px;}
    button{padding:12px 20px;font-size:18px;border-radius:12px;border:none;background:#77c177;color:white;cursor:pointer;}
  </style>
</head>
<body>
  <h1>🌡 센서 & 스위치 상태</h1>
  <div><button onclick="location.href='/'">🏠 메인으로</button></div>
  <div class="card">🌡 온도: <span id="temp" class="value">--</span> °C</div>
  <div class="card">💧 습도: <span id="humi" class="value">--</span> %</div>
  <div class="card">🔘 스위치: <span id="sw" class="value">--</span></div>

  <script>
    let ws;
    function connectWS(){
      const proto=(location.protocol==='https:')?'wss://':'ws://';
      ws=new WebSocket(proto+location.host+'/ws');
      ws.onmessage=(ev)=>{
        if(ev.data.startsWith('SENSOR:')){
          const p=ev.data.split(':');
          if(p.length===5){temp.textContent=p[2];humi.textContent=p[4];}
        }else if(ev.data.startsWith('SWITCH:')){
          const st=ev.data.substring(7);
          sw.textContent=(st==="ON"?"눌림":"해제");
        }
      };
      ws.onclose=()=>setTimeout(connectWS,1000);
    }
    function requestSensor(){try{ws.send("SENSOR?");}catch(e){}}
    connectWS();
    setInterval(requestSensor,5000);
  </script>
</body>
</html>
)**";


