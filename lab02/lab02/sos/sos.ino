// 1. 告诉板子灯在哪里
const int ledPin = 2; 

// 2. 准备工作
void setup() {
  pinMode(ledPin, OUTPUT); 
}

// 3. 循环执行 SOS 动作
void loop() {
  // S: 短闪3次
  for(int i=0; i<3; i++) { digitalWrite(ledPin, HIGH); delay(200); digitalWrite(ledPin, LOW); delay(200); }
  delay(500); // 字母间隔
  
  // O: 长闪3次
  for(int i=0; i<3; i++) { digitalWrite(ledPin, HIGH); delay(600); digitalWrite(ledPin, LOW); delay(200); }
  delay(500);
  
  // S: 短闪3次
  for(int i=0; i<3; i++) { digitalWrite(ledPin, HIGH); delay(200); digitalWrite(ledPin, LOW); delay(200); }
  delay(2000); // 单词间隔
}