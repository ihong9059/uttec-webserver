#pragma once
const char* display_HTML = R"**(
<!doctype html>
<html lang="ko">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>디스플레이</title>
<style>
 body{font-family:Arial;text-align:center;background:#fff5f5;padding:20px}
 h2{font-size:24px}
 input{width:80%;padding:10px;margin:6px;border-radius:10px;border:1px solid #ccc;font-size:18px}
 button{margin-top:15px;padding:12px 20px;font-size:20px;border-radius:12px;background:#3498db;color:#fff;border:none}
 a{display:block;margin-top:20px;text-decoration:none;color:#333;font-size:18px}
</style>
</head>
<body>
<h2>🖥 화면에 글자 써보기</h2>
<p>아래 칸에 글씨를 쓰고 “보내기” 버튼을 눌러 보세요.</p>
<input id="l1" placeholder="첫 줄"><br>
<input id="l2" placeholder="둘째 줄"><br>
<input id="l3" placeholder="셋째 줄"><br>
<input id="l4" placeholder="넷째 줄"><br>
<button onclick="send()">보내기</button>
<a href="/">← 메인으로</a>
<script>
let ws=new WebSocket(`ws://${location.host}/ws`);
function send(){
  ws.send(JSON.stringify({type:"DISP_SET_LINES",
    l1:document.getElementById('l1').value,
    l2:document.getElementById('l2').value,
    l3:document.getElementById('l3').value,
    l4:document.getElementById('l4').value}));
}
</script>
</body>
</html>
)**";

