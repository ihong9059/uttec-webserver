// myHtml.h
#pragma once

// %SSID% 와 %APIP% 는 서버가 전송 전에 문자열 치환합니다.
const char* all_HTML = R"**(
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>ESP32 Beep 교실</title>
  <style>
    :root { font-family: Pretendard, system-ui, -apple-system, Segoe UI, Roboto, Apple SD Gothic Neo, Noto Sans KR, "맑은 고딕", sans-serif; }
    body { margin:0; background:#f6f8ff; min-height:100vh; display:flex; color:#111; }
    .wrap { margin:auto; width:min(680px,94vw); text-align:center; }
    .card { background:#fff; border-radius:24px; box-shadow:0 6px 20px rgba(0,0,0,.08); padding:28px; }
    h1 { font-size: clamp(22px, 6vw, 36px); margin:.2em 0 .4em; }
    .subtitle { color:#555; margin-bottom:18px; }
    .ssid{ font-weight:700; color:#2a57ff; } .ip{ font-weight:700; color:#0b8a55; }
    .beepBox{ margin-top:18px; padding:22px; border-radius:20px; background:#fff3e0; }
    #beepBtn{ font-size:22px; padding:16px 22px; border:none; border-radius:16px; cursor:pointer; background:#ff9800; color:#fff; }
    #beepBtn:disabled{ opacity:.6; cursor:not-allowed; }
    .status{ margin-top:12px; font-size:16px; color:#333; }
    .ledHint{ margin-top:10px; font-size:14px; color:#666; }
    .pulse{ animation:pulse .5s ease; }
    @keyframes pulse { 0%{transform:scale(1)} 50%{transform:scale(1.06)} 100%{transform:scale(1)} }
  </style>
</head>
<body>
  <div class="wrap">
    <div class="card">
      <h1>🔔 비프 울리기</h1>
      <div class="subtitle">
        지금 <span class="ssid">"%SSID%"</span> AP에 연결되어 있어요.<br>
        ESP32 주소: <span class="ip">%APIP%</span>
      </div>

      <div class="beepBox" id="box">
        <button id="beepBtn" onclick="doBeep()">삐- (0.5초)</button>
        <div class="status" id="status">대기 중</div>
        <div class="ledHint">※ 비프와 함께 <b>빨간 LED(D25)</b>도 잠시 켜졌다가 꺼져요! (Active-Low)</div>
      </div>
    </div>
  </div>

<script>
async function doBeep(){
  const btn = document.getElementById('beepBtn');
  const st  = document.getElementById('status');
  const box = document.getElementById('box');
  try{
    btn.disabled = true;
    st.textContent = "비프 동작 중…";
    box.classList.remove('pulse');
    const res = await fetch('/beep');
    if(!res.ok) throw new Error('HTTP ' + res.status);
    const txt = await res.text();
    st.textContent = txt || "완료!";
    box.classList.add('pulse');
  }catch(e){
    st.textContent = "오류: " + (e.message || "연결 실패");
  }finally{
    setTimeout(()=>{ btn.disabled = false; st.textContent = "대기 중"; }, 700);
  }
}
</script>
</body>
</html>
)**";
