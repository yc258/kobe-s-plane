#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "科比直升机专用";
const char* pwd  = "2024117125";

WebServer server(80);
#define TOUCH_PIN 4    // Touch0 对应GPIO4，替换原来的T0
#define LED_PIN 15      // D15报警LED

bool isArmed = false;    // 是否布防
bool alarmLock = false;  // 报警锁定状态

String html = R"HTML(
<!DOCTYPE html>
<html>
<body style="text-align:center;padding-top:100px;">
    <h2>安防报警器控制台</h2>
    <br>
    <button onclick="fetch('/arm')" style="font-size:20px;padding:10px 30px;margin:10px;">布防 Arm</button>
    <button onclick="fetch('/disarm')" style="font-size:20px;padding:10px 30px;margin:10px;">撤防 Disarm</button>
</body>
</html>
)HTML";

void handleRoot() {
  server.send(200, "text/html", html);
}

// 布防接口
void handleArm() {
  isArmed = true;
  server.send(200, "text/plain", "armed");
}

// 撤防接口，同时清除报警
void handleDisarm() {
  isArmed = false;
  alarmLock = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "disarmed");
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);

  WiFi.begin(ssid, pwd);
  Serial.print("正在连接WiFi...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功，设备IP：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
  Serial.println("网页服务器启动完成");
}

void loop()
{
  server.handleClient();

  // 布防状态下检测触摸触发报警
  if(isArmed && !alarmLock)
  {
    int val = touchRead(TOUCH_PIN);
    if(val < 35)
    {
      alarmLock = true;
      Serial.println("触摸触发报警，已锁定");
    }
  }

  // 报警锁定，高频闪烁，松手也不会停
  if(alarmLock)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(80);
    digitalWrite(LED_PIN, LOW);
    delay(80);
  }
}