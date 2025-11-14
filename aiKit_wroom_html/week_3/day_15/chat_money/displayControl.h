#pragma once
const char* display_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>SSD1306 디스플레이</title>
<style>
  body{font-family:system-ui,Segoe UI,Roboto,Apple SD Gothic Neo,Malgun Gothic,sans-serif;margin:24px}
  .wrap{max-width:720px;margin:auto}
  .top{display:flex;gap:8px;margin-bottom:16px;align-items:center}
  a.btn{padding:8px 12px;border:1px solid #ccc;border-radius:10px;text-decoration:none}
  .card{border:1px solid #ddd;border-radius:16px;padding:16px;box-shadow:0 6px 20px rgba(0,0,0,.08)}
  .row{display:grid;grid-template-columns:100px 1fr;gap:10px;align-items:center;margin:10px 0}
  input[type=text]{width:100%;padding:8px;border:1px solid #ccc;border-radius:8px}
  button{padding:10px 14px;border-radius:10px;border:1px solid #bbb}
</style>
</head>
<body>
<div class="wrap">
  <div class="top">
    <a class="btn" href="/">← 메인</a>
    <h2 style="margin:0">SSD1306 한글 표시(U8g2)</h2>
  </div>
  <div class="card">
    <div class="row"><label>1 Line</label><input id="l1" type="text" placeholder="UTTEC Lab Ai"></div>
    <div class="row"><label>2 Line</label><input id="l2" type="text" placeholder="2번째 line"></div>
    <div class="row"><label>3 Line</label><input id="l3" type="text" placeholder="3번째 line"></div>
    <div class="row"><label>4 Line</label><input id="l4" type="text" placeholder="환영 합니다"></div>
    <div style="margin-top:12px">
      <button id="send">Send</button>
    </div>
  </div>
</div>
<script>
let ws;
function connectWs(){ ws=new WebSocket(`ws://${location.host}/ws`); }
connectWs();
document.getElementById('send').onclick=()=>{
  const l1=document.getElementById('l1').value;
  const l2=document.getElementById('l2').value;
  const l3=document.getElementById('l3').value;
  const l4=document.getElementById('l4').value;
  ws?.send(JSON.stringify({type:"DISP_SET_LINES", l1, l2, l3, l4}));
};
</script>
</body>
</html>
)**";
