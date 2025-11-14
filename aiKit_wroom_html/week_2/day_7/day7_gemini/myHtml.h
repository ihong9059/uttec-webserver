const char* my_HTML = R"raw(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 AP Info</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial, Helvetica, sans-serif; text-align: center; background-color: #f0f0f0; margin-top: 50px; }
        .container { background-color: #ffffff; margin: auto; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); max-width: 400px; }
        h1 { color: #333; }
        p { color: #666; font-size: 1.1em; }
        .info { font-weight: bold; color: #007bff; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 Wi-Fi AP</h1>
        <p>AP SSID: <span class="info">%SSID%</span></p>
        <p>AP IP Address: <span class="info">%IP_ADDRESS%</span></p>
    </div>
</body>
</html>
)raw";