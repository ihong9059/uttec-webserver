#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Smart Controller</title>
  <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css" rel="stylesheet">
  <style>
    :root {
      --primary: #2c3e50;
      --secondary: #34495e;
      --accent-red: #e74c3c;
      --accent-yellow: #f39c12;
      --accent-blue: #3498db;
      --accent-green: #2ecc71;
      --text-light: #ecf0f1;
      --text-dark: #2c3e50;
      --shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
      --gradient-bg: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    }

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background: var(--gradient-bg);
      min-height: 100vh;
      padding: 20px;
      color: var(--text-light);
    }

    .container {
      max-width: 1200px;
      margin: 0 auto;
    }

    .header {
      text-align: center;
      margin-bottom: 30px;
      padding: 20px;
      background: rgba(255, 255, 255, 0.1);
      backdrop-filter: blur(10px);
      border-radius: 20px;
      border: 1px solid rgba(255, 255, 255, 0.2);
    }

    .header h1 {
      font-size: 2.5rem;
      margin-bottom: 10px;
      background: linear-gradient(45deg, #fff, #ddd);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    .header p {
      opacity: 0.9;
      font-size: 1.1rem;
    }

    .ap-info {
      background: rgba(255, 255, 255, 0.15);
      padding: 15px;
      border-radius: 15px;
      margin-top: 15px;
    }

    .dashboard {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
      gap: 25px;
      margin-bottom: 30px;
    }

    .card {
      background: rgba(255, 255, 255, 0.1);
      backdrop-filter: blur(15px);
      border-radius: 20px;
      padding: 25px;
      border: 1px solid rgba(255, 255, 255, 0.2);
      transition: transform 0.3s ease, box-shadow 0.3s ease;
    }

    .card:hover {
      transform: translateY(-5px);
      box-shadow: var(--shadow);
    }

    .card-header {
      display: flex;
      align-items: center;
      margin-bottom: 20px;
    }

    .card-header i {
      font-size: 2rem;
      margin-right: 15px;
    }

    .card-header h2 {
      font-size: 1.5rem;
      font-weight: 600;
    }

    .switch-card .card-header i { color: var(--accent-green); }
    .red-card .card-header i { color: var(--accent-red); }
    .yellow-card .card-header i { color: var(--accent-yellow); }
    .blue-card .card-header i { color: var(--accent-blue); }

    .switch-indicator {
      width: 100px;
      height: 100px;
      border-radius: 50%;
      margin: 0 auto 20px;
      display: flex;
      align-items: center;
      justify-content: center;
      font-size: 1.5rem;
      font-weight: bold;
      transition: all 0.3s ease;
      border: 4px solid;
    }

    .switch-on {
      background: var(--accent-green);
      border-color: rgba(255, 255, 255, 0.3);
      color: white;
    }

    .switch-off {
      background: #95a5a6;
      border-color: rgba(255, 255, 255, 0.2);
      color: white;
    }

    .control-buttons {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 15px;
      margin-bottom: 20px;
    }

    .btn {
      padding: 15px 20px;
      border: none;
      border-radius: 12px;
      font-size: 1rem;
      font-weight: 600;
      cursor: pointer;
      transition: all 0.3s ease;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
    }

    .btn-on {
      background: var(--accent-green);
      color: white;
    }

    .btn-off {
      background: #e74c3c;
      color: white;
    }

    .btn-on:hover { background: #27ae60; transform: scale(1.05); }
    .btn-off:hover { background: #c0392b; transform: scale(1.05); }

    .slider-container {
      margin: 20px 0;
    }

    .slider-label {
      display: flex;
      justify-content: between;
      margin-bottom: 10px;
      font-weight: 500;
    }

    .slider-value {
      font-size: 1.2rem;
      font-weight: bold;
    }

    .slider {
      width: 100%;
      height: 12px;
      -webkit-appearance: none;
      appearance: none;
      background: rgba(255, 255, 255, 0.2);
      outline: none;
      border-radius: 10px;
    }

    .red-slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: var(--accent-red);
      cursor: pointer;
      border: 3px solid white;
      box-shadow: 0 2px 8px rgba(231, 76, 60, 0.4);
    }

    .yellow-slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: var(--accent-yellow);
      cursor: pointer;
      border: 3px solid white;
      box-shadow: 0 2px 8px rgba(243, 156, 18, 0.4);
    }

    .blue-slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 25px;
      height: 25px;
      border-radius: 50%;
      background: var(--accent-blue);
      cursor: pointer;
      border: 3px solid white;
      box-shadow: 0 2px 8px rgba(52, 152, 219, 0.4);
    }

    .refresh-btn {
      background: var(--secondary);
      color: white;
      padding: 12px 25px;
      border: none;
      border-radius: 12px;
      cursor: pointer;
      transition: all 0.3s ease;
      width: 100%;
    }

    .refresh-btn:hover {
      background: #2c3e50;
      transform: scale(1.05);
    }

    .status-text {
      text-align: center;
      margin-top: 15px;
      font-size: 0.9rem;
      opacity: 0.8;
    }

    .led-visual {
      width: 50px;
      height: 50px;
      border-radius: 50%;
      margin: 15px auto;
      transition: all 0.3s ease;
      border: 3px solid rgba(255, 255, 255, 0.3);
    }

    .led-off {
      background: #7f8c8d;
      box-shadow: inset 0 0 20px rgba(0, 0, 0, 0.3);
    }

    .led-on {
      box-shadow: 0 0 30px currentColor;
    }

    .red-led { background: var(--accent-red); }
    .yellow-led { background: var(--accent-yellow); }
    .blue-led { background: var(--accent-blue); }

    @media (max-width: 768px) {
      .dashboard {
        grid-template-columns: 1fr;
      }
      
      .header h1 {
        font-size: 2rem;
      }
    }

    .pulse {
      animation: pulse 2s infinite;
    }

    @keyframes pulse {
      0% { transform: scale(1); }
      50% { transform: scale(1.05); }
      100% { transform: scale(1); }
    }
  </style>
</head>
<body>
  <div class="container">
    <div class="header">
      <h1><i class="fas fa-microchip"></i> ESP32 Smart Controller</h1>
      <p>Wireless IoT Device Management</p>
      <div class="ap-info">
        <p><i class="fas fa-wifi"></i> Connected to: <strong>{{AP_SSID}}</strong></p>
      </div>
    </div>

    <div class="dashboard">
      <!-- Switch Card -->
      <div class="card switch-card">
        <div class="card-header">
          <i class="fas fa-toggle-on"></i>
          <h2>Switch Status</h2>
        </div>
        <div class="switch-indicator {{SWITCH_CLASS}} pulse" id="switchIndicator">
          <i class="fas {{#if SWITCH_STATE}}fa-check{{else}}fa-times{{/if}}"></i>
        </div>
        <p style="text-align: center; margin-bottom: 20px; font-size: 1.2rem;">
          GPIO 32: <strong id="switchStatusText">{{SWITCH_STATE}}</strong>
        </p>
        <button class="refresh-btn" onclick="updateSwitchStatus()">
          <i class="fas fa-sync-alt"></i> Refresh Status
        </button>
        <p class="status-text">Auto-refreshing every 2 seconds</p>
      </div>

      <!-- Red LED Card -->
      <div class="card red-card">
        <div class="card-header">
          <i class="fas fa-lightbulb"></i>
          <h2>Red LED Control</h2>
        </div>
        <div class="led-visual red-led led-off" id="redLedVisual"></div>
        <div class="control-buttons">
          <button class="btn btn-on" onclick="controlLED('red', 'on')">
            <i class="fas fa-power-off"></i> ON
          </button>
          <button class="btn btn-off" onclick="controlLED('red', 'off')">
            <i class="fas fa-times"></i> OFF
          </button>
        </div>
        <div class="slider-container">
          <div class="slider-label">
            <span>Brightness:</span>
            <span class="slider-value" id="redValue">0%</span>
          </div>
          <input type="range" min="0" max="255" value="0" class="slider red-slider" 
                 id="redSlider" oninput="dimLED('red', this.value)">
        </div>
      </div>

      <!-- Yellow LED Card -->
      <div class="card yellow-card">
        <div class="card-header">
          <i class="fas fa-lightbulb"></i>
          <h2>Yellow LED Control</h2>
        </div>
        <div class="led-visual yellow-led led-off" id="yellowLedVisual"></div>
        <div class="control-buttons">
          <button class="btn btn-on" onclick="controlLED('yellow', 'on')">
            <i class="fas fa-power-off"></i> ON
          </button>
          <button class="btn btn-off" onclick="controlLED('yellow', 'off')">
            <i class="fas fa-times"></i> OFF
          </button>
        </div>
        <div class="slider-container">
          <div class="slider-label">
            <span>Brightness:</span>
            <span class="slider-value" id="yellowValue">0%</span>
          </div>
          <input type="range" min="0" max="255" value="0" class="slider yellow-slider" 
                 id="yellowSlider" oninput="dimLED('yellow', this.value)">
        </div>
      </div>

      <!-- Blue LED Card -->
      <div class="card blue-card">
        <div class="card-header">
          <i class="fas fa-lightbulb"></i>
          <h2>Blue LED Control</h2>
        </div>
        <div class="led-visual blue-led led-off" id="blueLedVisual"></div>
        <div class="control-buttons">
          <button class="btn btn-on" onclick="controlLED('blue', 'on')">
            <i class="fas fa-power-off"></i> ON
          </button>
          <button class="btn btn-off" onclick="controlLED('blue', 'off')">
            <i class="fas fa-times"></i> OFF
          </button>
        </div>
        <div class="slider-container">
          <div class="slider-label">
            <span>Brightness:</span>
            <span class="slider-value" id="blueValue">0%</span>
          </div>
          <input type="range" min="0" max="255" value="0" class="slider blue-slider" 
                 id="blueSlider" oninput="dimLED('blue', this.value)">
        </div>
      </div>
    </div>
  </div>

  <script>
    function controlLED(color, action) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/control?color=" + color + "&action=" + action, true);
      xhr.send();
      
      const ledVisual = document.getElementById(color + 'LedVisual');
      const slider = document.getElementById(color + 'Slider');
      
      if (action === 'on') {
        slider.value = 255;
        updateSliderValue(color, 255);
        ledVisual.classList.remove('led-off');
        ledVisual.classList.add('led-on');
      } else if (action === 'off') {
        slider.value = 0;
        updateSliderValue(color, 0);
        ledVisual.classList.remove('led-on');
        ledVisual.classList.add('led-off');
      }
    }

    function dimLED(color, value) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/control?color=" + color + "&action=dim&value=" + value, true);
      xhr.send();
      
      updateSliderValue(color, value);
      
      const ledVisual = document.getElementById(color + 'LedVisual');
      if (value > 0) {
        ledVisual.classList.remove('led-off');
        ledVisual.classList.add('led-on');
        // Adjust LED brightness visual effect
        ledVisual.style.opacity = value / 255;
      } else {
        ledVisual.classList.remove('led-on');
        ledVisual.classList.add('led-off');
      }
    }

    function updateSliderValue(color, value) {
      const percentage = Math.round((value / 255) * 100);
      document.getElementById(color + 'Value').textContent = percentage + '%';
    }

    function updateSwitchStatus() {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          const isPressed = this.responseText === 'PRESSED';
          const indicator = document.getElementById('switchIndicator');
          const statusText = document.getElementById('switchStatusText');
          
          statusText.textContent = this.responseText;
          
          if (isPressed) {
            indicator.className = 'switch-indicator switch-on pulse';
            indicator.innerHTML = '<i class="fas fa-check"></i>';
          } else {
            indicator.className = 'switch-indicator switch-off';
            indicator.innerHTML = '<i class="fas fa-times"></i>';
          }
        }
      };
      xhr.open("GET", "/switch", true);
      xhr.send();
    }
    
    // 자동 갱신
    setInterval(updateSwitchStatus, 2000);
    
    // 초기 로드 시 설정
    window.onload = function() {
      updateSwitchStatus();
      
      // 슬라이더 이벤트 리스너
      ['red', 'yellow', 'blue'].forEach(color => {
        const slider = document.getElementById(color + 'Slider');
        slider.addEventListener('input', function() {
          updateSliderValue(color, this.value);
        });
      });
    };
  </script>
</body>
</html>
)**";

#endif