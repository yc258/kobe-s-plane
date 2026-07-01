#define TOUCH_PIN 4   // ESP32 Touch0 = GPIO4，替换原来的T0
#define LED_PIN 2

// 档位变量：1慢、2中、3快
int speedGear = 1;
int lastTouchVal = 100;
unsigned long debounceTime = 60;
unsigned long timeStamp = 0;

// 呼吸灯变量
int brightness = 0;
int fadeStep;
bool fadeDir = true;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
}

void loop()
{
  unsigned long now = millis();
  int touchVal = touchRead(TOUCH_PIN);

  // 触摸边沿检测+软件防抖，切换档位
  if (now - timeStamp > debounceTime)
  {
    if (touchVal < 35 && lastTouchVal >= 35)
    {
      speedGear++;
      if(speedGear > 3) speedGear = 1;
    }
    lastTouchVal = touchVal;
    timeStamp = now;
  }

  // 根据档位设置步长，控制呼吸快慢
  switch(speedGear)
  {
    case 1: fadeStep = 1; break;
    case 2: fadeStep = 3; break;
    case 3: fadeStep = 6; break;
  }

  // 呼吸渐变逻辑
  if(fadeDir)
    brightness += fadeStep;
  else
    brightness -= fadeStep;

  if(brightness >= 255) fadeDir = false;
  if(brightness <= 0)   fadeDir = true;

  ledcWrite(0, brightness);
  delay(10);
}