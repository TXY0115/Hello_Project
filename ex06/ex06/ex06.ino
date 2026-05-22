const int ledPinA = 2;  // 灯A：直接用板子上自带的蓝灯！
const int ledPinB = 15; // 灯B：虚拟灯（没接硬件，但我们用串口监视器看它的数据）

void setup() {
  Serial.begin(115200); // 打开串口

  // 新版 ESP32 库的 PWM 初始化：直接指定 引脚、频率、分辨率
  // 底层会自动为它们分配两个独立的通道，完美符合老师要求
  ledcAttach(ledPinA, 5000, 8);
  ledcAttach(ledPinB, 5000, 8);
}

void loop() {
  // 阶段一：灯A变亮(0->255)，灯B变暗(255->0)
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledPinA, dutyCycle);       // 给A写正向值
    ledcWrite(ledPinB, 255 - dutyCycle); // 给B写反向值
    
    // 在电脑上实时打印两路数据
    Serial.print("灯A亮度: ");
    Serial.print(dutyCycle);
    Serial.print(" \t灯B亮度: ");
    Serial.println(255 - dutyCycle);
    
    delay(15); 
  }
  
  // 阶段二：灯A变暗(255->0)，灯B变亮(0->255)
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledPinA, dutyCycle);
    ledcWrite(ledPinB, 255 - dutyCycle);
    
    Serial.print("灯A亮度: ");
    Serial.print(dutyCycle);
    Serial.print(" \t灯B亮度: ");
    Serial.println(255 - dutyCycle);
    
    delay(15);
  }
}