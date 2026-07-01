#define touchPin 4    // ESP32 Touch0 = GPIO4
#define ledPin 2
bool ledState = false;
int lastTouch = 100;   // 触摸阈值，数值越小代表摸到了
unsigned long debounce = 50;
unsigned long tmr = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  int val = touchRead(touchPin);
  unsigned long now = millis();

  if (now - tmr > debounce)
  {
    // 边沿检测：之前大于阈值（没摸），现在小于阈值（摸到）
    if(val < 30 && lastTouch >= 30)
    {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
    lastTouch = val;
    tmr = now;
  }
}