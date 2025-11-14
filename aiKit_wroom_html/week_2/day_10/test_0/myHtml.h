#ifndef MYHTML_H
#define MYHTML_H

const char* all_HTML = R"rawliteral(
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 LED Control</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin: 20px; }
        .container { max-width: 400px; margin: 0 auto; padding: 20px; border: 1px solid #ddd; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }
        .slider-container { margin: 20px 0; }
        .slider { width: 100%; }
        h2 { color: #333; }
        .led-title { display: flex; justify-content: space-between; align-items: center; margin-bottom: 5px; }
        .led-title span { font-weight: bold; }
        .led-title button { padding: 5px 10px; border: none; border-radius: 5px; cursor: pointer; }
        .red-btn { background-color: #ff4d4d; color: white; }
        .yellow-btn { background-color: #ffd700; color: white; }
        .blue-btn { background-color: #4da6ff; color: white; }
    </style>
</head>
<body>
    <div class="container">
        <h2>ESP32 WiFi AP: 홍길동</h2>
        <h3>LED Control</h3>

        <div class="slider-container">
            <div class="led-title">
                <span>Red LED</span>
                <button class="red-btn" onclick="toggleLed('red')">ON/OFF</button>
            </div>
            <input type="range" min="0" max="255" value="0" class="slider" id="redSlider" oninput="updateLed('red', this.value)">
        </div>
        
        <div class="slider-container">
            <div class="led-title">
                <span>Yellow LED</span>
                <button class="yellow-btn" onclick="toggleLed('yellow')">ON/OFF</button>
            </div>
            <input type="range" min="0" max="255" value="0" class="slider" id="yellowSlider" oninput="updateLed('yellow', this.value)">
        </div>

        <div class="slider-container">
            <div class="led-title">
                <span>Blue LED</span>
                <button class="blue-btn" onclick="toggleLed('blue')">ON/OFF</button>
            </div>
            <input type="range" min="0" max="255" value="0" class="slider" id="blueSlider" oninput="updateLed('blue', this.value)">
        </div>
    </div>
    
    <script>
        function updateLed(color, value) {
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/led?" + color + "=" + value, true);
            xhttp.send();
        }

        function toggleLed(color) {
            const slider = document.getElementById(color + 'Slider');
            if (slider.value > 0) {
                slider.value = 0;
            } else {
                slider.value = 255;
            }
            updateLed(color, slider.value);
        }
    </script>
</body>
</html>
)rawliteral";

#endif
