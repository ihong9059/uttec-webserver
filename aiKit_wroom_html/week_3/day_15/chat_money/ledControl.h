#pragma once
const char* led_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>LED 제어</title>
<style>
  body{font-family:system-ui,Segoe UI,Roboto,Apple SD Gothic Neo,Malgun Gothic,sans-serif;margin:24px}
  .wrap{max-width:720px;margin:auto}
  .top{display:flex;gap:8px;margin-bottom:16px;align-items:center}
  a.btn{padding:8px 12px;border:1px solid #ccc;border-radius:10px;text-decoration:none}
  .card{border:1px solid #ddd;border-radius:16px;padding:16px;box-shadow:0 6px 20px rgba(0,0,0,.08)}
  .row{display:grid;grid-template-columns:100px 1fr 80px;gap:10px;align-items:center;margin:10px 0}
  input[type=range]{width:100%}
</style>
</head>
<body>
<div class="wrap">
  <div class="top">
    <a class="btn" href="/">← 메인</a>
    <h2 style="margin:0">LED 제어 (LOW=ON)</h2>
  </div>
  <div class="card">
    <div class="row"><strong>Red</strong> <input id="r" type="range" min="0" max="255" value="0"><span id="rv">0</span></div>
    <div class="row"><strong>Yellow</strong> <input id="y" type="range" min="0" max="255" value="0"><span id="yv">0</span></div>
    <div class="row"><strong>Blue</strong> <input id="b" type="range" min="0" max="255" value="0"><span id="bv">0</span></div>
    <div style="margin-top:10px;display:flex;gap:10px">
      <button id="offAll">모두 끄기</button>
    </div>
  </div>
</div>
<script>
let ws;
function connectWs(){
  ws = new WebSocket(`ws://${location.host}/ws`);
}
function sendLed(c,v){
  ws?.send(JSON.stringify({type:"LED_SET", color:c, value:parseInt(v)}));
}
function offAll(){
  ws?.send(JSON.stringify({type:"LED_OFFALL"}));
  // UI도 0으로
  ["r","y","b"].forEach(id=>{document.getElementById(id).value=0; document.getElementById(id+"v").textContent="0";});
}
connectWs();
["r","y","b"].forEach(id=>{
  const el=document.getElementById(id), lbl=document.getElementById(id+"v");
  el.addEventListener("input", e=>{ lbl.textContent=e.target.value; });
  el.addEventListener("change", e=>{
    const map={r:"red", y:"yellow", b:"blue"};
    sendLed(map[id], e.target.value);
  });
});
document.getElementById("offAll").onclick=offAll;
</script>
</body>
</html>
)**";
