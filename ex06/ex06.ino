// LED_A 使用 D15(GPIO15)，LED_B 使用 GPIO2
#define LED_A_PIN 15
#define LED_B_PIN 2

int brightness = 0;
int step = 2;

void setup()
{
    // 配置两路独立的PWM通道，8位分辨率
    ledcSetup(0, 5000, 8);
    ledcSetup(1, 5000, 8);

    ledcAttachPin(LED_A_PIN, 0);
    ledcAttachPin(LED_B_PIN, 1);
}

void loop()
{
    brightness += step;

    // 数值触顶之后反向
    if (brightness >= 255 || brightness <= 0)
    {
        step = -step;
    }

    // 两个LED亮度完全反相
    ledcWrite(0, brightness);
    ledcWrite(1, 255 - brightness);

    delay(8);
}