const int touchPin = 4; // 触摸引脚 D4
const int ledPin = 2;   // 板载LED引脚 D2
const int threshold = 20; // 触摸阈值，根据你刚测好的情况微调

int gear = 1;                // 当前档位 (1, 2, 3)
bool lastTouchState = false; // 记录上一次的触摸状态

// 呼吸灯变量
int dutyCycle = 0;
int fadeAmount = 5;

void setup() {
  Serial.begin(115200);
  // 初始化 PWM
  ledcAttach(ledPin, 5000, 8); 
}

void loop() {
  // === 1. 触摸检测与边缘触发（换挡） ===
  int touchValue = touchRead(touchPin);
  bool currentTouchState = touchValue < threshold;

  if (currentTouchState && !lastTouchState) {
    delay(50); // 防抖
    if (touchRead(touchPin) < threshold) {
      gear++; // 升档
      if (gear > 3) gear = 1; // 超过3档则回到1档
      
      Serial.print("当前档位: ");
      Serial.println(gear);
    }
  }
  lastTouchState = currentTouchState;

  // === 2. 执行 PWM 呼吸灯 ===
  ledcWrite(ledPin, dutyCycle);
  dutyCycle = dutyCycle + fadeAmount;

  if (dutyCycle <= 0 || dutyCycle >= 255) {
    fadeAmount = -fadeAmount; // 触顶或触底时反转方向
  }

  // === 3. 根据档位改变呼吸速度（delay时间） ===
  if (gear == 1) {
    delay(30); // 1档：慢速呼吸
  } else if (gear == 2) {
    delay(15); // 2档：中速呼吸
  } else {
    delay(5);  // 3档：急促呼吸
  }
}