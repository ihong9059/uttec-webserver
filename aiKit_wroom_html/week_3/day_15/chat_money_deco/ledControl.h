#pragma once
const char* led_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>LED 제어</title>
<style>
 body{font-family:Arial;text-align:center;background:#eef7fa;padding:20px}
 h2{font-size:24px}
 .ledbtn{width:120px;height:120px;font-size:22px;border:none;border-radius:20px;color:#fff;margin:15px}
 .red{background:#e74c3c}
 .yellow{background:#f1c40f;color:#333}
 .blue{background:#3498db}
 .off{background:#7f8c8d}
 a{display:inline-block;margin-top:20px;text-decoration:none;color:#333;font-size:18px}
</style>
</head>
<body>
<h2>💡 LED 불빛 켜기/끄기</h2>
<p>버튼을 눌러 불빛을 켜거나 꺼 보세요!</p>
<div>
  <button class="ledbtn red" onclick="setLed('red',255)">🔴 켜기</button>
  <button class="ledbtn off" onclick="setLed('red',0)">끄기</button>
</div>
<div>
  <button class="ledbtn yellow" onclick="setLed('yellow',255)">🟡 켜기</button>
  <button class="ledbtn off" onclick="setLed('yellow',0)">끄기</button>
</div>
<div>
  <button class="ledbtn blue" onclick="setLed('blue',255)">🔵 켜기</button>
  <button class="ledbtn off" onclick="setLed('blue',0)">끄기</button>
</div>
<a href="/">← 메인으로</a>
<script>
let ws=new WebSocket(`ws://${location.host}/ws`);
function setLed(c,v){ws.send(JSON.stringify({type:"LED_SET",color:c,value:v}));}
</script>
</body>
</html>
)**";

