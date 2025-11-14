const char* sensor_HTML = R"**(

<!DOCTYPE html>

<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>센서/스위치 상태</title>
<style>
body { font-family: 'Arial', sans-serif; background-color: #f0f4f8; text-align: center; margin: 0; padding: 20px; color: #333; }
.container { max-width: 600px; margin: auto; background: #ffffff; padding: 20px; border-radius: 15px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); }
h1 { color: #2196F3; margin-bottom: 20px; }
.data-box { background-color: #e3f2fd; padding: 15px; border-radius: 10px; margin-bottom: 20px; }
.data-box p { margin: 10px 0; font-size: 1.2em; }
.data-box .label { font-weight: bold; color: #004d99; }
.back-btn { padding: 10px 20px; background-color: #6c757d; color: white; border: none; border-radius: 10px; margin-top: 20px; cursor: pointer; transition: background-color 0.2s; }
.back-btn:hover { background-color: #5a6268; }
</style>
</head>
<body>
<div class="container">
<h1>센서/스위치 상태</h1>
<div class="data-box">
<p><span class="label">온도:</span> <span id="temperature">...</span> °C</p>
<p><span class="label">습도:</span> <span id="humidity">...</span> %</p>
<p><span class="label">스위치:</span> <span id="switch-state">...</span></p>
</div>
<p>상태가 5초마다 자동으로 갱신됩니다.</p>
<button class="back-btn" onclick="window.location.href='/'">메인 페이지</button>
</div>
<script>
var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
ws.onmessage = function(event) {
var data = JSON.parse(event.data);
document.getElementById('temperature').innerText = data.temperature.toFixed(1);
document.getElementById('humidity').innerText = data.humidity.toFixed(1);
document.getElementById('switch-state').innerText = data.switch_state;
};
setInterval(function() {
ws.send("request_sensor_data");
}, 5000); // 5초마다 데이터 요청
</script>
</body>
</html>
)**";