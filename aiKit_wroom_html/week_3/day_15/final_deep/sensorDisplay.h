#ifndef SENSORDISPLAY_H
#define SENSORDISPLAY_H

const char* sensor_HTML = R"**(
<!DOCTYPE html>
<html lang='ko'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>🌡️ 센서 데이터</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            font-family: 'Arial Rounded MT Bold', '맑은 고딕', sans-serif;
            background: linear-gradient(135deg, #fdcb6e 0%, #f39c12 100%);
            min-height: 100vh; padding: 20px; text-align: center;
        }
        .container {
            max-width: 500px; margin: 0 auto; background: rgba(255, 255, 255, 0.95);
            border-radius: 25px; padding: 30px; box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .header { margin-bottom: 25px; }
        h1 { color: #e17055; font-size: 2.5em; margin-bottom: 10px; }
        .home-btn {
            position: absolute; top: 20px; left: 20px; padding: 10px 20px;
            background: #74b9ff; color: white; border: none; border-radius: 15px;
            cursor: pointer; font-weight: bold;
        }
        .sensor-data { margin: 20px 0; }
        .data-container {
            display: grid; grid-template-columns: 1fr 1fr; gap: 15px; margin: 15px 0;
        }
        .data-box {
            background: rgba(255, 255, 255, 0.9); padding: 20px; border-radius: 15px;
            box-shadow: 0 3px 10px rgba(0,0,0,0.1);
        }
        .data-label { font-size: 1.1em; color: #636e72; margin-bottom: 10px; font-weight: bold; }
        .data-value { font-size: 2em; font-weight: bold; }
        .temp-value { color: #e17055; }
        .hum-value { color: #0984e3; }
        .unit { font-size: 0.6em; color: #636e72; }
        .switch-box {
            background: rgba(255, 255, 255, 0.9); padding: 20px; border-radius: 15px;
            margin: 15px 0; box-shadow: 0 3px 10px rgba(0,0,0,0.1);
        }
        .switch-status { font-size: 1.5em; font-weight: bold; margin: 10px 0; }
        .switch-on { color: #4caf50; }
        .switch-off { color: #f44336; }
        .emoji { font-size: 1.3em; margin-right: 8px; }
    </style>
</head>
<body>
    <button class='home-btn' onclick='location.href="/"'>🏠 홈으로</button>
    
    <div class='container'>
        <div class='header'>
            <h1>🌡️ 센서 데이터</h1>
            <p>실시간 온도, 습도, 스위치 상태를 확인해보세요!</p>
        </div>

        <div class='sensor-data'>
            <div class='data-container'>
                <div class='data-box'>
                    <div class='data-label'><span class='emoji'>🔥</span>온도</div>
                    <div id='temperature' class='data-value temp-value'>--.-<span class='unit'>°C</span></div>
                </div>
                <div class='data-box'>
                    <div class='data-label'><span class='emoji'>💧</span>습도</div>
                    <div id='humidity' class='data-value hum-value'>--.-<span class='unit'>%</span></div>
                </div>
            </div>

            <div class='switch-box'>
                <div class='data-label'><span class='emoji'>🔘</span>스위치 상태</div>
                <div id='switch-status' class='switch-status switch-off'>꺼짐</div>
                <p>GPIO 32번에 연결된 스위치입니다</p>
            </div>
        </div>
    </div>

<script>
    function updateSensorData() {
        fetch('/sensorData')
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.json();
            })
            .then(data => {
                document.getElementById('temperature').innerHTML = 
                    data.temperature.toFixed(1) + '<span class="unit">°C</span>';
                document.getElementById('humidity').innerHTML = 
                    data.humidity.toFixed(1) + '<span class="unit">%</span>';
                
                const switchStatus = document.getElementById('switch-status');
                if (data.switchState) {
                    switchStatus.textContent = '켜짐';
                    switchStatus.className = 'switch-status switch-on';
                } else {
                    switchStatus.textContent = '꺼짐';
                    switchStatus.className = 'switch-status switch-off';
                }
            })
            .catch(error => {
                console.error('Error fetching sensor data:', error);
            });
    }

    // 2초마다 데이터 업데이트
    setInterval(updateSensorData, 2000);
    
    // 페이지 로드 시 즉시 업데이트
    updateSensorData();
</script>
</body>
</html>
)**";

#endif