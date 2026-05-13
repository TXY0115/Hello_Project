const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 获取当前时间，并用 7000 毫秒（7秒）作为一个完整循环的时间轴
  unsigned long t = millis() % 7000; 
  bool state = LOW;

  // 根据时间轴决定灯亮还是灭 (严格按照三短、三长、三短)
  // --- 前面三个短闪 (S) ---
  if      (t < 200)  state = HIGH;  
  else if (t < 400)  state = LOW;
  else if (t < 600)  state = HIGH;
  else if (t < 800)  state = LOW;
  else if (t < 1000) state = HIGH;
  else if (t < 1400) state = LOW;   // 字母之间的停顿
  
  // --- 中间三个长闪 (O) ---
  else if (t < 2000) state = HIGH;
  else if (t < 2200) state = LOW;
  else if (t < 2800) state = HIGH;
  else if (t < 3000) state = LOW;
  else if (t < 3600) state = HIGH;
  else if (t < 4000) state = LOW;   // 字母之间的停顿
  
  // --- 后面三个短闪 (S) ---
  else if (t < 4200) state = HIGH;
  else if (t < 4400) state = LOW;
  else if (t < 4600) state = HIGH;
  else if (t < 4800) state = LOW;
  else if (t < 5000) state = HIGH;
  else               state = LOW;   // 剩下的时间(5000-7000)全灭，作为大停顿

  digitalWrite(ledPin, state);
}
