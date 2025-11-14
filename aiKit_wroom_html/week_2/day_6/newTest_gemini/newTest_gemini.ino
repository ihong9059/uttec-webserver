// Include the Wi-Fi library
#include <WiFi.h>
#include <WebServer.h>

// Set AP credentials
const char *ssid = "홍광선";
const char *password = ""; // No password, empty string

// Set the IP address for the AP
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Create a WebServer object on port 80
WebServer server(80);

void setup() {
  // Start Serial communication for debugging
  Serial.begin(115200);
  delay(100);

  // Set up Wi-Fi in AP mode
  Serial.println("\nStarting Wi-Fi Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("Access Point is running with the following settings:");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Set up the web server's main handler
  server.on("/", handleRoot);
  
  // Handle any other requests
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
  Serial.println("Web Server started");
}

void loop() {
  // Handle client requests continuously
  server.handleClient();
}

// Function to handle the root URL "/"
void handleRoot() {
  // The HTML content to send to the client
  String htmlContent = "<!DOCTYPE html>";
  htmlContent += "<html>";
  htmlContent += "<head>";
  htmlContent += "<meta charset='UTF-8'>";
  htmlContent += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  htmlContent += "<title>Wi-Fi AP 정보</title>";
  htmlContent += "<style>";
  htmlContent += "body { font-family: sans-serif; text-align: center; background-color: #f0f0f0; margin-top: 50px; }";
  htmlContent += "h1 { color: #333; }";
  htmlContent += "p { font-size: 24px; color: #555; }";
  htmlContent += ".container { background-color: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); display: inline-block; }";
  htmlContent += "</style>";
  htmlContent += "</head>";
  htmlContent += "<body>";
  htmlContent += "<div class='container'>";
  htmlContent += "<h1>Wi-Fi AP 정보</h1>";
  htmlContent += "<p>현재 접속한 AP의 SSID는:</p>";
  htmlContent += "<h2>";
  htmlContent += ssid; // Display the SSID here
  htmlContent += "</h2>";
  htmlContent += "</div>";
  htmlContent += "</body>";
  htmlContent += "</html>";

  // Send the HTML content
  server.send(200, "text/html", htmlContent);
}

// Function to handle 404 Not Found errors
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  
  server.send(404, "text/plain", message);
}
