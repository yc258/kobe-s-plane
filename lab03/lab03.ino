// 定义LED引脚
const int ledPin = 2;
const int ledChannel = 0;  // 手动指定PWM通道 0~15

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);

  // 传统标准写法：先配置通道，再绑定引脚
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  // 逐渐变亮
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    // 旧版必须填通道号，不是引脚
    ledcWrite(ledChannel, dutyCycle);
    delay(10);
  }

  // 逐渐变暗
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledChannel, dutyCycle);
    delay(10);
  }

  Serial.println("Breathing cycle completed");
}