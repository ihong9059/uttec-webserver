const char* aht20_HTML = R"**(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 제어판</title>
  <script>
    var socket;
    function init() {
      socket = new WebSocket('ws://' + window.location.hostname + ':81/');
      socket.onmessage = function(event) {
        console.log('메시지 수신:', event.data);
      };
    }
    
    function sendText() {
      var inputText = document.getElementById("textInput").value;
      if(socket.readyState === WebSocket.OPEN) {
        socket.send(inputText);
        console.log('텍스트 전송:', inputText);
      }
    }
  </script>
</head>
<body onload="init()">
  <h1>ESP32 OLED 제어</h1>
  <div>
    <label for="textInput">OLED에 표시할 텍스트:</label><br>
    <input type="text" id="textInput" placeholder="텍스트를 입력하세요">
    <button onclick="sendText()">전송</button>
  </div>
</body>
</html>
)**";

