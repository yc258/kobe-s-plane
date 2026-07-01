#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "科比直升机专用";
const char* pwd  = "2024117125";
WebServer server(80);
#define TOUCH_PIN 4   // Touch0 = GPIO4，解决T0未定义报错

String page = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>传感器仪表盘</title>
<style>
    .num{font-size:60px;text-align:center;margin-top:150px;color:blue;}
</style>
</head>
<body>
    <div class="num">当前数值：<span id="data">0</span></div>
<script>
// AJAX定时拉取数据
function update(){
    fetch("/getData").then(res=>res.text()).then(v=>{
        document.getElementById("data").innerText = v;
    })
}
setInterval(update, 80); // 80ms刷新一次
</script>
</body>
</html>
)HTML";

void indexPage()
{
  server.send(200, "text/html", page);
}

// 接口：返回触摸原始值
void sendData()
{
  int touchVal = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(touchVal));
}

void setup()
{
  Serial.begin(115200);
  Serial.print("连接WiFi中...");
  WiFi.begin(ssid, pwd);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功");
  Serial.print("设备IP:");
  Serial.println(WiFi.localIP());

  server.on("/", indexPage);
  server.on("/getData", sendData);
  server.begin();
  Serial.println("网页服务已启动");
}

void loop()
{
  server.handleClient();
}