#include <WiFi.h>
#include <WebServer.h>

// 你的 iPhone 热点已填好
const char* ssid = "iPhone";       
const char* password = "CC150025"; 

WebServer server(80);
const int touchPin = 4; // 触摸引脚

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 传感器仪表盘</title>
  <style>
    body {text-align: center; margin-top: 100px; font-family: Arial; background-color: #f4f4f9;}
    h1 {color: #333;}
    #sensorValue {font-size: 120px; color: #007BFF; font-weight: bold; margin-top: 20px;}
    .box {border: 2px solid #ccc; padding: 40px; display: inline-block; border-radius: 15px; background: white; box-shadow: 0 4px 8px rgba(0,0,0,0.1);}
  </style>
</head>
<body>
  <div class="box">
    <h1>实时触摸数值</h1>
    <div id="sensorValue">--</div>
  </div>
  <script>
    // AJAX 定时拉取数据
    setInterval(function() {
      fetch('/data')
        .then(response => response.text())
        .then(data => {
          document.getElementById('sensorValue').innerText = data; 
        });
    }, 150); // 每150毫秒刷新一次网页数字
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  Serial.println("\nWiFi已连接! IP地址:");
  Serial.println(WiFi.localIP());

  server.on("/", []() { 
    server.send(200, "text/html", htmlPage); 
  });
  
  server.on("/data", []() { 
    int val = touchRead(touchPin);
    server.send(200, "text/plain", String(val)); 
  });
  
  server.begin();
}

void loop() {
  server.handleClient();
}
