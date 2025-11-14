#pragma once

const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <title>ESP32 Beep Demo</title>
  <style>
    body { font-family: sans-serif; text-align:center; margin-top:50px; }
    button { font-size:20px; padding:15px 25px; background:#ff9800; color:#fff; border:none; border-radius:12px; cursor:pointer; }
    button:disabled { opacity:0.5; }
    .info { margin-top:20px; font-size:18px; }
  </style>
</head>
<body>
  <h1>🔔 ESP32 비프 테스트</h1>
  <p class="info">AP SSID: <b>%SSID%</b> <br> IP: <b>%APIP%</b></p>
  <button id="beepBtn" onclick="doBeep()">삐— (0.5초)</button>
  <p id="status">대기 중</p>

<script>
async function doBeep(){
  const btn = document.getElementById("beepBtn");
  const st = document.getElementById("status");
  btn.disabled = true;
  st.textContent = "동작 중...";
  try {
    const res = await fetch("/beep");
    const txt = await res.text();
    st.textContent = txt;
  } catch(e) {
    st.textContent = "오류 발생";
  }
  setTimeout(()=>{ btn.disabled=false; st.textContent="대기 중"; }, 700);
}
</script>
</body>
</html>
)**";
