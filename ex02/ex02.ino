// LED引脚定义
const int ledPin = 2;

// 时间控制变量
unsigned long previousTime = 0;  // 记录上次状态切换时间
const unsigned long interval = 500; // 间隔500ms，1Hz闪烁
bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // 获取当前系统运行总毫秒数
  unsigned long currentTime = millis();

  // 判断是否到达切换时间
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;  // 更新时间戳
    ledState = !ledState;       // 翻转LED状态
    digitalWrite(ledPin, ledState);
  }

  // 这里可以放其他代码，不会被闪烁阻塞
}