#include <WiFi.h>
#include <WebServer.h>

// 已经帮你填好了刚才成功的热点名字和密码！
const char* ssid = "iPhone";       
const char* password = "CC150025"; 

WebServer server(80);
const int touchPin = 4;   // 触摸引脚 D4
const int ledPin = 2;     // 报警灯用板载蓝灯
const int threshold = 20; // 触摸阈值

bool isArmed = false;    
bool isAlarming = false; 
bool ledState = false;
unsigned long previousMillis = 0;
const long interval = 100; // 狂闪频率

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 安防系统</title>
  <style>
    body {text-align: center; margin-top: 50px; font-family: Arial;}
    button {font-size: 24px; padding: 15px 30px; margin: 20px; cursor: pointer; border-radius: 8px;}
  </style>
</head>
<body>
  <h1>安防报警主机</h1>
  <button onclick="fetch('/arm')">布防 (Arm)</button>
  <button onclick="fetch('/disarm')">撤防 (Disarm)</button>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  Serial.println("\nWiFi已连接! IP地址:");
  Serial.println(WiFi.localIP());

  server.on("/", []() { server.send(200, "text/html", htmlPage); });
  
  server.on("/arm", []() { 
    isArmed = true; 
    server.send(200, "text/plain", "Armed"); 
  });
  
  server.on("/disarm", []() { 
    isArmed = false; 
    isAlarming = false; 
    digitalWrite(ledPin, LOW); 
    server.send(200, "text/plain", "Disarmed"); 
  });
  
  server.begin();
}

void loop() {
  server.handleClient();

  if (isArmed && !isAlarming) {
    if (touchRead(touchPin) < threshold) {
      isAlarming = true; 
    }
  }

  if (isAlarming) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
}