const char* led_HTML = R"**(

<!DOCTYPE html>

<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>LED 제어</title>
<style>
body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
.container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
h1 { color: #ff6347; margin-bottom: 20px; }
.led-buttons { display: flex; justify-content: space-around; flex-wrap: wrap; margin-bottom: 20px; }
.led-buttons button { padding: 15px 30px; font-size: 1.2em; font-weight: bold; border: none; border-radius: 10px; color: white; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 4px 6px rgba(0,0,0,0.1); margin: 10px; }
.led-buttons button:hover { transform: translateY(-3px); box-shadow: 0 6px 10px rgba(0,0,0,0.15); }
.led-red { background-color: #ff4136; }
.led-yellow { background-color: #ffc400; }
.led-blue { background-color: #0074d9; }
.status-box { background-color: #e8f5e9; padding: 15px; border-radius: 10px; }
.status-box p { margin: 0; font-weight: bold; }
.back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
.back-btn:hover { background-color: #5a6268; }
</style>
</head>
<body>
<div class="container">
<h1>LED 제어</h1>
<div class="led-buttons">
<button class="led-red" onclick="toggleLED('red')">빨강 LED</button>
<button class="led-yellow" onclick="toggleLED('yellow')">노랑 LED</button>
<button class="led-blue" onclick="toggleLED('blue')">파랑 LED</button>
</div>
<div class="status-box">
<p>LED 상태를 변경하려면 버튼을 누르세요.</p>
</div>
<button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
</div>
<script>
var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
function toggleLED(color) {
ws.send("toggle_led:" + color);
}
</script>
</body>
</html>
)**";