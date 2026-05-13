const int ledPin = 2; // GPIO2

// PWM 属性
const int freq = 5000;
const int resolution = 8;
// 新版不需要手动分配 channel（通道）了，系统会自动管

void setup() {
  // 配置 PWM 并绑定引脚（新版把老版的两句合成了一句）
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  // 逐渐变亮
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    // 新版直接对引脚(ledPin)写入，不用对通道写入了
    ledcWrite(ledPin, dutyCycle); 
    delay(15);
  }
  
  // 逐渐变暗
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPin, dutyCycle);
    delay(15);
  }
}