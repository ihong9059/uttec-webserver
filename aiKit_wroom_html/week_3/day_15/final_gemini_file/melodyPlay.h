const char* melody_HTML = R"**(

<!DOCTYPE html>

<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>멜로디 연주</title>
<style>
body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
.container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
h1 { color: #9c27b0; margin-bottom: 20px; }
.melody-buttons { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; margin-bottom: 20px; }
.melody-buttons button { padding: 15px; font-size: 1.1em; font-weight: bold; border: none; border-radius: 10px; color: white; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }
.melody-buttons button:hover { transform: translateY(-3px); box-shadow: 0 6px 10px rgba(0,0,0,0.15); }
.alarm-btn { background-color: #f44336; }
.melody-btn-1 { background-color: #28a745; }
.melody-btn-2 { background-color: #ffc107; }
.melody-btn-3 { background-color: #17a2b8; }
.melody-btn-4 { background-color: #6f42c1; }
.back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
.back-btn:hover { background-color: #5a6268; }
</style>
</head>
<body>
<div class="container">
<h1>멜로디 연주</h1>
<p>원하는 멜로디 버튼을 눌러보세요.</p>
<div class="melody-buttons">
<button class="alarm-btn" onclick="playMelody('alarm')">삐 소리</button>
<button class="melody-btn-1" onclick="playMelody('melody1')">생일 축하</button>
<button class="melody-btn-2" onclick="playMelody('melody2')">작은 별</button>
<button class="melody-btn-3" onclick="playMelody('melody3')">엘리제를 위하여</button>
<button class="melody-btn-4" onclick="playMelody('melody4')">떴다 떴다 비행기</button>
</div>
<button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
</div>
<script>
var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
function playMelody(melody) {
ws.send("play_melody:" + melody);
}
</script>
</body>
</html>
)**";