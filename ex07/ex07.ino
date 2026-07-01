#include <WiFi.h>
#include <WebServer.h>

// ========= 配置区 =========
const char* ssid     = "科比直升机专用";
const char* password = "2024117125";
#define LED_PIN 15        // LED接D15(GPIO15)
#define PWM_CH 0
WebServer server(80);
int brightness = 0;

// 网页页面：包含range滑动条，JS用fetch实时发送数值
String htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>无极调光器</title>
</head>
<body style="text-align:center;margin-top:80px;">
    <h2>LED亮度调节</h2>
    <input type="range" id="slider" min="0" max="255" value="0" style="width:350px;">
    <p>当前值：<span id="val">0</span></p >
<script>
const slider = document.getElementById('slider');
const showVal = document.getElementById('val');

slider.oninput = function(){
    let v = this.value;
    showVal.innerText = v;
    // GET请求把数值传给ESP32
    fetch("/set?val="+v);
}
</script>
</body>
</html>
)HTML";

void handleRoot()
{
  server.send(200, "text/html", htmlPage);
}

void handleSet()
{
  if(server.hasArg("val"))
  {
    brightness = server.arg("val").toInt();
    ledcWrite(PWM_CH, brightness);
  }
  server.send(200, "text/plain", "ok");
}

void setup()
{
  Serial.begin(115200);
  // PWM初始化
  ledcSetup(PWM_CH, 5000, 8);
  ledcAttachPin(LED_PIN, PWM_CH);

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  // 绑定网页接口
  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();

  Serial.print("IP地址：");
  Serial.println(WiFi.localIP());
}

void loop()
{
  server.handleClient();
}