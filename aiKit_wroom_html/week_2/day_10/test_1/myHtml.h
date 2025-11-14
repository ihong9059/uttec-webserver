#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 LED & Switch Control</title>
  <style>
    body { 
      font-family: Arial, sans-serif; 
      text-align: center; 
      margin: 0 auto; 
      padding: 20px;
      background-color: #f0f0f0;
    }
    .btn { 
      padding: 12px 24px; 
      font-size: 16px; 
      margin: 8px; 
      border: none;
      border-radius: 5px;
      cursor: pointer;
      font-weight: bold;
    }
    .red-btn { background-color: #ff4444; color: white; }
    .red-btn:hover { background-color: #cc0000; }
    .yellow-btn { background-color: #ffcc00; color: black; }
    .yellow-btn:hover { background-color: #ff9900; }
    .blue-btn { background-color: #4488ff; color: white; }
    .blue-btn:hover { background-color: #0066cc; }
    
    .slider { 
      width: 80%; 
      margin: 15px; 
      height: 25px;
    }
    .red-slider::-webkit-slider-thumb { background: #ff4444; }
    .yellow-slider::-webkit-slider-thumb { background: #ffcc00; }
    .blue-slider::-webkit-slider-thumb { background: #4488ff; }
    
    .container { 
      margin: 25px auto; 
      padding: 20px;
      max-width: 400px;
      background: white;
      border-radius: 10px;
      box-shadow: 0 2px 10px rgba(0,0,0,0.1);
    }
    .red-container { border-top: 4px solid #ff4444; }
    .yellow-container { border-top: 4px solid #ffcc00; }
    .blue-container { border-top: 4px solid #4488ff; }
    .switch-container { border-top: 4px solid #666; }
    
    h1 { color: #333; }
    h2 { color: #555; }
    p { color: #666; }
    
    .switch-status {
      font-size: 24px;
      font-weight: bold;
      padding: 15px;
      border-radius: 10px;
      margin: 10px;
      display: inline-block;
      min-width: 100px;
    }
    .switch-on { background-color: #4CAF50; color: white; }
    .switch-off { background-color: #f44336; color: white; }
    
    .refresh-btn {
      background-color: #666;
      color: white;
      padding: 10px 20px;
      margin-top: 10px;
    }
  </style>
</head>
<body>
  <h1>ESP32 LED & Switch Control</h1>
  <p>Connected AP SSID: <strong>{{AP_SSID}}</strong></p>
  
  <div class="container switch-container">
    <h2>Switch Status (GPIO 32)</h2>
    <div class="switch-status {{SWITCH_CLASS}}" id="switchStatus">
      {{SWITCH_STATE}}
    </div>
    <br>
    <button class="btn refresh-btn" onclick="updateSwitchStatus()">Refresh Status</button>
    <p>Auto refresh every 2 seconds</p>
  </div>
  
  <div class="container red-container">
    <h2 style="color: #ff4444;">Red LED</h2>
    <button class="btn red-btn" onclick="controlLED('red', 'on')">ON</button>
    <button class="btn" onclick="controlLED('red', 'off')">OFF</button>
    <br>
    <input type="range" min="0" max="255" value="0" class="slider red-slider" id="redSlider" oninput="dimLED('red', this.value)">
    <p>Brightness: <span id="redValue">0</span></p>
  </div>

  <div class="container yellow-container">
    <h2 style="color: #ffcc00;">Yellow LED</h2>
    <button class="btn yellow-btn" onclick="controlLED('yellow', 'on')">ON</button>
    <button class="btn" onclick="controlLED('yellow', 'off')">OFF</button>
    <br>
    <input type="range" min="0" max="255" value="0" class="slider yellow-slider" id="yellowSlider" oninput="dimLED('yellow', this.value)">
    <p>Brightness: <span id="yellowValue">0</span></p>
  </div>

  <div class="container blue-container">
    <h2 style="color: #4488ff;">Blue LED</h2>
    <button class="btn blue-btn" onclick="controlLED('blue', 'on')">ON</button>
    <button class="btn" onclick="controlLED('blue', 'off')">OFF</button>
    <br>
    <input type="range" min="0" max="255" value="0" class="slider blue-slider" id="blueSlider" oninput="dimLED('blue', this.value)">
    <p>Brightness: <span id="blueValue">0</span></p>
  </div>

  <script>
    function controlLED(color, action) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/control?color=" + color + "&action=" + action, true);
      xhr.send();
      
      if (action === 'on') {
        document.getElementById(color + 'Slider').value = 255;
        document.getElementById(color + 'Value').textContent = '255';
      } else if (action === 'off') {
        document.getElementById(color + 'Slider').value = 0;
        document.getElementById(color + 'Value').textContent = '0';
      }
    }

    function dimLED(color, value) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/control?color=" + color + "&action=dim&value=" + value, true);
      xhr.send();
      document.getElementById(color + 'Value').textContent = value;
    }
    
    function updateSwitchStatus() {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var statusElement = document.getElementById('switchStatus');
          statusElement.textContent = this.responseText;
          statusElement.className = 'switch-status ' + 
            (this.responseText === 'ON' ? 'switch-on' : 'switch-off');
        }
      };
      xhr.open("GET", "/switch", true);
      xhr.send();
    }
    
    // 자동 갱신
    setInterval(updateSwitchStatus, 2000);
    
    // 초기 로드 시 스위치 상태 업데이트
    window.onload = function() {
      updateSwitchStatus();
      
      // 슬라이더 값 실시간 표시
      document.getElementById('redSlider').addEventListener('input', function() {
        document.getElementById('redValue').textContent = this.value;
      });
      document.getElementById('yellowSlider').addEventListener('input', function() {
        document.getElementById('yellowValue').textContent = this.value;
      });
      document.getElementById('blueSlider').addEventListener('input', function() {
        document.getElementById('blueValue').textContent = this.value;
      });
    };
  </script>
</body>
</html>
)**";

#endif
