#include <WiFi.h>
#include <WebServer.h>
#include "myHtml.h" // myHtml.h 파일 포함

const char* ssid = "홍길동";
// 비밀번호는 설정하지 않으므로 주석 처리하거나 빈 문자열로 둡니다.
// const char* password = "your_password"; 

IPAddress local_ip(192, 168, 7, 1);
IPAddress gateway(192, 168, 7, 1); // 게이트웨이를 AP IP와 동일하게 설정
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

void handleRoot() {
  String html = my_HTML;
  html.replace("%SSID%", WiFi.softAPSSID());
  html.replace("%IP_ADDRESS%", WiFi.softAPIP().toString());
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\nConfiguring access point...");

  // AP 모드 설정
  // SSID는 "홍길동", 비밀번호는 없습니다.
  WiFi.softAPConfig(local_ip, gateway, subnet);
  if (WiFi.softAP(ssid)) {
    Serial.print("AP created with SSID: ");
    Serial.println(ssid);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("AP creation failed!");
  }
  
  // 웹 서버 핸들러 설정
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

// Esp32wroom, 아두이노에서, wifi ap mode로 설정하고, ssid는 홍길동, password는 없는것으로 하여, 핸드폰이 접속하면, ap의 ssid를 보내서 화면에 나타나도록 하는 프로그램을 만들어 주세요. web page부분은 const char* my_HTML = R”**( )**”; 의 형태로 만들어 주세요.
// Web page부분은 myHtml.h로 분리하여 만들어 주세요. 
// webServer ip는 192.168.7.1로 하고, ip주소를 web page에 나타나게 해 주세요.
