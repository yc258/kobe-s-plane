// 作业6：警车双闪灯效（终极兼容版，无需任何PWM配置）
const int ledRedPin = 2;    // 红色LED引脚
const int ledBluePin = 16;  // 蓝色LED引脚
const int FADE_DELAY = 5;   // 调整此值改变整体闪烁速度

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  Serial.begin(115200);
  Serial.println("作业6：警车双闪灯效启动");
}

void loop() {
  // 红色渐亮，蓝色同步渐暗（反相关系）
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledRedPin, brightness);
    analogWrite(ledBluePin, brightness);
    delay(FADE_DELAY);
  }
   for (int brightness = 255; brightness >=0; brightness--) {
    analogWrite(ledRedPin, brightness);
    analogWrite(ledBluePin, brightness);
    delay(FADE_DELAY);
  }
}