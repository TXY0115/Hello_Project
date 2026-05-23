#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "iPhone";       // 换成你的WiFi名称
const char* password = "CC150025"; // 换成你的WiFi密码

WebServer server(80);
const int ledPin = 2; // 板载LED蓝灯

// 网页前端代码
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 Web调光器</title>
  <style>body {text-align: center; margin-top: 50px; font-family: Arial;}</style>
</head>
<body>
  <h1>LED 无极调光器</h1>
  <input type="range" min="0" max="255" value="0" id="pwmSlider" oninput="updatePWM(this.value)">
  <p>当前亮度: <span id="pwmValue">0</span></p>
  <script>
    function updatePWM(val) {
      document.getElementById('pwmValue').innerText = val;
      fetch('/set?val=' + val); // 发送滑动条的具体数值给ESP32
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  
  // 新版PWM初始化
  ledcAttach(ledPin, 5000, 8); 
  ledcWrite(ledPin, 0);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi已连接! IP地址:");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/set", []() {
    if (server.hasArg("val")) {
      int val = server.arg("val").toInt();
      ledcWrite(ledPin, val); // 解析URL中的数值并赋值给PWM
      server.send(200, "text/plain", "OK");
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}