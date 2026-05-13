const int ledPin = 2;
unsigned long previousMillis = 0; // 记录上一次的时间
const long interval = 500;        // 间隔500毫秒（亮500，灭500，正好是1Hz）
bool ledState = LOW;              // 记录灯当前的状态

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis(); // 芯片看一眼现在的"手表时间"
  
  // 如果现在的时间 减去 上次的时间，大于等于 500 毫秒了
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // 把现在的时间记下来
    
    // 切换灯的状态（亮变灭，灭变亮）
    ledState = !ledState; 
    digitalWrite(ledPin, ledState);
  }
}