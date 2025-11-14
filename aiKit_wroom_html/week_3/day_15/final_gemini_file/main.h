const char* main_HTML = R"**(

<!DOCTYPE html>

<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>UTTEC Lab Ai</title>
<style>
body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
.container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
h1 { color: #007bff; margin-bottom: 20px; }
.ssid-box { background-color: #e2f0ff; padding: 15px; border-radius: 10px; margin-bottom: 20px; font-size: 1.2em; font-weight: bold; }
.button-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
.button-grid button { padding: 20px; font-size: 1em; font-weight: bold; border: none; border-radius: 10px; color: white; cursor: pointer; transition: transform 0.2s, box-shadow 0.2s; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }
.button-grid button:hover { transform: translateY(-3px); box-shadow: 0 6px 10px rgba(0,0,0,0.15); }
.led-btn { background-color: #ff6347; }
.oled-btn { background-color: #4CAF50; }
.sensor-btn { background-color: #2196F3; }
.melody-btn { background-color: #9c27b0; }
.footer { margin-top: 20px; font-size: 0.9em; color: #777; }
</style>
</head>
<body>
<div class="container">
<h1>UTTEC Lab Ai</h1>
<div class="ssid-box">
<span>AP SSID:</span> <span id="ssid-name">...</span>
</div>
<div class="button-grid">
<button class="led-btn" onclick="window.location.href='/led'">LED 제어</button>
<button class="oled-btn" onclick="window.location.href='/display'">OLED 제어</button>
<button class="sensor-btn" onclick="window.location.href='/sensor'">센서/스위치</button>
<button class="melody-btn" onclick="window.location.href='/melody'">멜로디 연주</button>
</div>
<div class="footer">
<p>직관적으로 쉽게 사용해보세요!</p>
</div>
</div>
<script>
var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
ws.onmessage = function(event) {
document.getElementById('ssid-name').innerText = event.data;
};
</script>
</body>
</html>
)**";