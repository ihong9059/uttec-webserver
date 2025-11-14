#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Beeper Control</title>
  <style>
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      text-align: center;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      min-height: 100vh;
      margin: 0;
      padding: 20px;
      color: white;
    }
    
    .container {
      max-width: 500px;
      margin: 50px auto;
      background: rgba(255, 255, 255, 0.1);
      backdrop-filter: blur(10px);
      border-radius: 20px;
      padding: 30px;
      border: 1px solid rgba(255, 255, 255, 0.2);
      box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
    }
    
    h1 {
      font-size: 2.5rem;
      margin-bottom: 20px;
      text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3);
    }
    
    .ap-info {
      background: rgba(255, 255, 255, 0.15);
      padding: 15px;
      border-radius: 15px;
      margin: 20px 0;
      font-size: 1.1rem;
    }
    
    .ap-info strong {
      color: #4CAF50;
    }
    
    .beep-btn {
      background: linear-gradient(45deg, #FF416C, #FF4B2B);
      color: white;
      border: none;
      padding: 20px 40px;
      font-size: 1.5rem;
      font-weight: bold;
      border-radius: 50px;
      cursor: pointer;
      margin: 30px 0;
      transition: all 0.3s ease;
      box-shadow: 0 6px 20px rgba(255, 75, 43, 0.4);
    }
    
    .beep-btn:hover {
      transform: scale(1.05);
      box-shadow: 0 8px 25px rgba(255, 75, 43, 0.6);
    }
    
    .beep-btn:active {
      transform: scale(0.95);
    }
    
    .beep-btn i {
      margin-right: 10px;
    }
    
    .status {
      margin-top: 20px;
      padding: 15px;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 10px;
      font-size: 1rem;
    }
    
    .pulse {
      animation: pulse 2s infinite;
    }
    
    @keyframes pulse {
      0% { transform: scale(1); }
      50% { transform: scale(1.05); }
      100% { transform: scale(1); }
    }
    
    .instructions {
      margin-top: 30px;
      padding: 15px;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 10px;
      text-align: left;
    }
    
    .instructions h3 {
      margin-top: 0;
      color: #FFD700;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>🎵 ESP32 Beeper Controller</h1>
    
    <div class="ap-info">
      <i class="fas fa-wifi"></i> Connected to: <strong>{{AP_SSID}}</strong>
    </div>
    
    <button class="beep-btn pulse" onclick="playBeep()">
      <i class="fas fa-volume-up"></i> Play Beep Sound
    </button>
    
    <div class="status" id="status">
      Ready to play beep sound...
    </div>
    
    <div class="instructions">
      <h3>📋 Instructions:</h3>
      <p>• Click the button to play a 0.5 second beep sound</p>
      <p>• Beeper is connected to GPIO 14</p>
      <p>• Sound activates when pin goes LOW</p>
    </div>
  </div>

  <script>
    function playBeep() {
      const btn = document.querySelector('.beep-btn');
      const status = document.getElementById('status');
      
      // 버튼 애니메이션
      btn.classList.remove('pulse');
      btn.style.opacity = '0.8';
      status.textContent = 'Playing beep sound...';
      
      // 서버에 beep 요청
      fetch('/beep')
        .then(response => response.text())
        .then(data => {
          status.textContent = data;
          // 0.5초 후에 버튼 상태 복원
          setTimeout(() => {
            btn.style.opacity = '1';
            btn.classList.add('pulse');
            status.textContent = 'Beep completed! Click to play again.';
          }, 500);
        })
        .catch(error => {
          status.textContent = 'Error: ' + error;
          btn.style.opacity = '1';
          btn.classList.add('pulse');
        });
    }
  </script>
  
  <script src="https://kit.fontawesome.com/a076d05399.js" crossorigin="anonymous"></script>
</body>
</html>
)**";

#endif

#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Beeper Control</title>
  <style>
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      text-align: center;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      min-height: 100vh;
      margin: 0;
      padding: 20px;
      color: white;
    }
    
    .container {
      max-width: 500px;
      margin: 50px auto;
      background: rgba(255, 255, 255, 0.1);
      backdrop-filter: blur(10px);
      border-radius: 20px;
      padding: 30px;
      border: 1px solid rgba(255, 255, 255, 0.2);
      box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
    }
    
    h1 {
      font-size: 2.5rem;
      margin-bottom: 20px;
      text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3);
    }
    
    .ap-info {
      background: rgba(255, 255, 255, 0.15);
      padding: 15px;
      border-radius: 15px;
      margin: 20px 0;
      font-size: 1.1rem;
    }
    
    .ap-info strong {
      color: #4CAF50;
    }
    
    .beep-btn {
      background: linear-gradient(45deg, #FF416C, #FF4B2B);
      color: white;
      border: none;
      padding: 20px 40px;
      font-size: 1.5rem;
      font-weight: bold;
      border-radius: 50px;
      cursor: pointer;
      margin: 30px 0;
      transition: all 0.3s ease;
      box-shadow: 0 6px 20px rgba(255, 75, 43, 0.4);
      position: relative;
      overflow: hidden;
    }
    
    .beep-btn:hover:not(:disabled) {
      transform: scale(1.05);
      box-shadow: 0 8px 25px rgba(255, 75, 43, 0.6);
    }
    
    .beep-btn:active:not(:disabled) {
      transform: scale(0.95);
    }
    
    .beep-btn:disabled {
      background: linear-gradient(45deg, #cccccc, #999999);
      cursor: not-allowed;
      opacity: 0.7;
    }
    
    .beep-btn i {
      margin-right: 10px;
    }
    
    .status {
      margin-top: 20px;
      padding: 15px;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 10px;
      font-size: 1rem;
      min-height: 60px;
      display: flex;
      align-items: center;
      justify-content: center;
      transition: all 0.3s ease;
    }
    
    .status.playing {
      background: rgba(255, 0, 0, 0.3);
      color: #FF0000;
      box-shadow: 0 0 20px rgba(255, 0, 0, 0.5);
    }
    
    .led-indicator {
      width: 20px;
      height: 20px;
      border-radius: 50%;
      background: #7f8c8d;
      margin: 0 auto 10px;
      transition: all 0.3s ease;
    }
    
    .led-indicator.active {
      background: #FF0000;
      box-shadow: 0 0 20px rgba(255, 0, 0, 0.8);
    }
    
    .pulse {
      animation: pulse 2s infinite;
    }
    
    .pulse-fast {
      animation: pulse 0.5s infinite;
    }
    
    @keyframes pulse {
      0% { transform: scale(1); opacity: 1; }
      50% { transform: scale(1.1); opacity: 0.8; }
      100% { transform: scale(1); opacity: 1; }
    }
    
    .instructions {
      margin-top: 30px;
      padding: 15px;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 10px;
      text-align: left;
    }
    
    .instructions h3 {
      margin-top: 0;
      color: #FFD700;
    }
    
    .visual-feedback {
      margin: 20px 0;
      padding: 15px;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 15px;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>🎵 ESP32 Beeper Controller</h1>
    
    <div class="ap-info">
      <i class="fas fa-wifi"></i> Connected to: <strong>{{AP_SSID}}</strong>
    </div>
    
    <div class="visual-feedback">
      <div class="led-indicator" id="ledIndicator"></div>
      <p>Red LED Status (GPIO 25)</p>
    </div>
    
    <button class="beep-btn pulse" id="beepBtn" onclick="playBeep()">
      <i class="fas fa-volume-up"></i> Play Beep Sound
    </button>
    
    <div class="status" id="status">
      Ready to play beep sound...
    </div>
    
    <div class="instructions">
      <h3>📋 Instructions:</h3>
      <p>• Click the button to play a 0.5 second beep sound</p>
      <p>• Beeper is connected to GPIO 14</p>
      <p>• Red LED is connected to GPIO 25 (LOW active)</p>
      <p>• Both beeper and LED will activate simultaneously</p>
    </div>
  </div>

  <script>
    let isBeeping = false;
    
    function playBeep() {
      if (isBeeping) return;
      
      const btn = document.getElementById('beepBtn');
      const status = document.getElementById('status');
      const ledIndicator = document.getElementById('ledIndicator');
      
      isBeeping = true;
      btn.disabled = true;
      btn.classList.remove('pulse');
      status.textContent = 'Playing beep sound...';
      status.className = 'status playing';
      ledIndicator.classList.add('active');
      ledIndicator.classList.add('pulse-fast');
      
      // 서버에 beep 요청
      fetch('/beep')
        .then(response => response.text())
        .then(data => {
          status.textContent = data;
          
          // 0.5초 후에 버튼 상태 복원
          setTimeout(() => {
            isBeeping = false;
            btn.disabled = false;
            btn.classList.add('pulse');
            status.textContent = 'Beep completed! Click to play again.';
            status.className = 'status';
            ledIndicator.classList.remove('active');
            ledIndicator.classList.remove('pulse-fast');
          }, 500);
        })
        .catch(error => {
          status.textContent = 'Error: ' + error;
          isBeeping = false;
          btn.disabled = false;
          btn.classList.add('pulse');
          status.className = 'status';
          ledIndicator.classList.remove('active');
          ledIndicator.classList.remove('pulse-fast');
        });
    }
  </script>
  
  <script src="https://kit.fontawesome.com/a076d05399.js" crossorigin="anonymous"></script>
</body>
</html>
)**";

#endif

