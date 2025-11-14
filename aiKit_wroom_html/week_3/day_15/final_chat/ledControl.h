#pragma once
const char* led_HTML = R"**(
<!DOCTYPE html><html lang="ko"><head>
<meta charset="UTF-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>LED 제어</title>
<style>
 body{font-family:system-ui,Noto Sans KR,sans-serif;background:#f6f8ff;margin:0;display:flex;min-height:100vh}
 .wrap{margin:auto;width:min(720px,94vw)}
 .card{background:#fff;border-radius:24px;box-shadow:0 8px 28px rgba(0,0,0,.08);padding:24px}
 h1{margin:.2em 0 .4em;text-align:center}
 .grid{display:grid;grid-template-columns:1fr 1fr 1fr;gap:14px}
 .tile{background:#f3f6ff;border-radius:16px;padding:16px;text-align:center}
 input[type=range]{width:100%}
 .top{display:flex;gap:10px;justify-content:center;margin-bottom:12px}
 a.btn{padding:10px 16px;background:#777;color:#fff;border-radius:10px;text-decoration:none}
</style></head><body><div class="wrap"><div class="card">
  <div class="top"><a class="btn" href="/">메인으로</a></div>
  <h1>LED 밝기 조절</h1>
  <div class="grid">
    <div class="tile"><div>🔴 RED (D25)</div><div><span id="rv">0</span></div>
      <input id="r" type="range" min="0" max="255" value="0" oninput="send('red',this.value)"></div>
    <div class="tile"><div>🟡 YELLOW (D26)</div><div><span id="yv">0</span></div>
      <input id="y" type="range" min="0" max="255" value="0" oninput="send('yellow',this.value)"></div>
    <div class="tile"><div>🔵 BLUE (D27)</div><div><span id="bv">0</span></div>
      <input id="b" type="range" min="0" max="255" value="0" oninput="send('blue',this.value)"></div>
  </div>
</div></div>
<script>
 const wsUrl=(location.protocol==='https:'?'wss://':'ws://')+location.hostname+':81/';
 let ws; function connect(){ ws=new WebSocket(wsUrl); ws.onopen=()=>{}; ws.onclose=()=>setTimeout(connect,800); }
 function send(t,v){ document.getElementById(t[0]+'v').textContent=v;
   if(ws&&ws.readyState===1){ ws.send(JSON.stringify({cmd:'led',target:t,val:parseInt(v)})); } }
 connect();
</script></body></html>
)**";
