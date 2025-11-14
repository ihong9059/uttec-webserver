const char* display_HTML = R"**(

<!DOCTYPE html>

<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>OLED 제어</title>
<style>
body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
.container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
h1 { color: #4CAF50; margin-bottom: 20px; }
.input-group { margin-bottom: 15px; }
.input-group label { display: block; margin-bottom: 5px; font-weight: bold; }
.input-group input { width: 80%; padding: 8px; border: 1px solid #ccc; border-radius: 5px; }
#send-btn { padding: 10px 20px; background-color: #4CAF50; color: white; border: none; border-radius: 10px; cursor: pointer; transition: background-color 0.2s; margin-top: 10px; }
#send-btn:hover { background-color: #45a049; }
.back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
.back-btn:hover { background-color: #5a6268; }
</style>
</head>
<body>
<div class="container">
<h1>OLED 제어</h1>
<p>OLED에 출력할 내용을 입력하고 버튼을 누르세요.</p>
<div class="input-group">
<label for="line1">1번째 줄:</label>
<input type="text" id="line1" value="UTTEC Lab Ai">
</div>
<div class="input-group">
<label for="line2">2번째 줄:</label>
<input type="text" id="line2" value="2번째 line">
</div>
<div class="input-group">
<label for="line3">3번째 줄:</label>
<input type="text" id="line3" value="3번째 line">
</div>
<div class="input-group">
<label for="line4">4번째 줄:</label>
<input type="text" id="line4" value="환영 합니다">
</div>
<button id="send-btn" onclick="sendText()">내용 보내기</button>
<button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
</div>
<script>
var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
function sendText() {
var text1 = document.getElementById('line1').value;
var text2 = document.getElementById('line2').value;
var text3 = document.getElementById('line3').value;
var text4 = document.getElementById('line4').value;
var message = oled_update:${text1}|${text2}|${text3}|${text4};
ws.send(message);
}
</script>
</body>
</html>
)**";