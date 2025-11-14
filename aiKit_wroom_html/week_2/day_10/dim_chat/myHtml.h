// myHtml.h
#pragma once

// %SSID% 와 %APIP% 는 서버가 전송 전에 문자열 치환합니다.
const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>ESP32 LED 교실</title>
  <style>
    :root { font-family: Pretendard, system-ui, -apple-system, Segoe UI, Roboto, Apple SD Gothic Neo, Noto Sans KR, "맑은 고딕", sans-serif; }
    body { margin: 0; background: #f6f8ff; color:#111; display:flex; min-height:100vh; }
    .wrap { margin:auto; width:min(720px, 94vw); text-align:center; }
    .card { background:#fff; border-radius:24px; box-shadow:0 6px 20px rgba(0,0,0,.08); padding:24px; }
    h1 { font-size: clamp(22px, 5vw, 34px); margin:.2em 0 .4em; }
    .subtitle { color:#555; margin-bottom:16px; }
    .ssid { font-weight:700; color:#2a57ff; }
    .ip   { font-weight:600; color:#0b8a55; }
    .grid { display:grid; grid-template-columns: repeat(3, 1fr); gap:14px; margin-top:18px; }
    .tile { border-radius:18px; padding:16px; background:#f3f6ff; }
    .name { font-size:18px; margin-bottom:8px; }
    .btns { display:grid; grid-template-columns:1fr 1fr; gap:10px; margin:10px 0 8px; }
    button { font-size:18px; padding:12px 10px; border:none; border-radius:14px; cursor:pointer; }
    .on  { background:#00c853; color:#fff; }
    .off { background:#ff5252; color:#fff; }
    .slider-wrap { margin-top:8px; }
    input[type=range] { width:100%; }
    .tag { display:inline-block; padding:2px 10px; border-radius:999px; font-size:12px; background:#eef2ff; color:#334; }
    footer { margin-top:20px; color:#666; font-size:13px; }
  </style>
</head>
<body>
  <div class="wrap">
    <div class="card">
      <div class="tag">ESP32 Wi-Fi AP 교실</div>
      <h1>안녕하세요! 😊</h1>
      <div class="subtitle">지금 <span class="ssid">"%SSID%"</span> AP에 연결되어 있어요.<br>ESP32 주소: <span class="ip">%APIP%</span></div>

      <div class="grid">
        <div class="tile" id="redBox">
          <div class="name">🔴 빨간색 (D25)</div>
          <div class="btns">
            <button class="on"  onclick="ledOn('red')">켜기</button>
            <button class="off" onclick="ledOff('red')">끄기</button>
          </div>
          <div class="slider-wrap">
            밝기: <span id="redVal">0</span>
            <input type="range" min="0" max="255" value="0" oninput="setDim('red', this.value)">
          </div>
        </div>

        <div class="tile" id="yellowBox">
          <div class="name">🟡 노란색 (D26)</div>
          <div class="btns">
            <button class="on"  onclick="ledOn('yellow')">켜기</button>
            <button class="off" onclick="ledOff('yellow')">끄기</button>
          </div>
          <div class="slider-wrap">
            밝기: <span id="yellowVal">0</span>
            <input type="range" min="0" max="255" value="0" oninput="setDim('yellow', this.value)">
          </div>
        </div>

        <div class="tile" id="blueBox">
          <div class="name">🔵 파란색 (D27)</div>
          <div class="btns">
            <button class="on"  onclick="ledOn('blue')">켜기</button>
            <button class="off" onclick="ledOff('blue')">끄기</button>
          </div>
          <div class="slider-wrap">
            밝기: <span id="blueVal">0</span>
            <input type="range" min="0" max="255" value="0" oninput="setDim('blue', this.value)">
          </div>
        </div>
      </div>

      <footer>※ LED는 <b>Low일 때 켜지는</b> 회로입니다 (학습 포인트!)</footer>
    </div>
  </div>

<script>
  const valSpan = {
    red:    document.getElementById('redVal'),
    yellow: document.getElementById('yellowVal'),
    blue:   document.getElementById('blueVal')
  };

  async function ledOn(name){ await fetch(`/on?led=${name}`); }
  async function ledOff(name){ await fetch(`/off?led=${name}`); }
  async function setDim(name, v){
    valSpan[name].textContent = v;
    await fetch(`/dim?led=${name}&val=${v}`);
  }
</script>
</body>
</html>
)**";
