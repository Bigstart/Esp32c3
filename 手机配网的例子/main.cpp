#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "errorpassword.h"

const char *ssid = "ESP32-C3-AP";
const char *password = "password";

WebServer server(80);

void handleRoot()
{
  String content = "<style>\
                    body {\
                        font-family: Arial, sans-serif;\
                        margin: 0;\
                        padding: 20px;\
                        background-color: #f3f3f3;\
                    }\
                    form {\
                        max-width: 100%;\
                        width: 80%;\
                        height:30%;\
                        margin: 0 auto;\
                        background-color: #fff;\
                        padding: 20px;\
                        border-radius: 10px;\
                        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\
                    }\
                    h2 {\
                        margin-top: 0;\
                        text-align: center;\
                        font-size:60px;\
                    }\
                    select, input[type='password'] {\
                        width: 100%;\
                        height:25%;\
                        padding: 10px;\
                        border-radius: 5px;\
                        border: 1px solid #ccc;\
                        margin-bottom: 10px;\
                        box-sizing: border-box; /* 解决输入框宽度问题 */\
                        margin-top: 40px; /* 设置按钮上边距 */\
                        font-size:30px;\
                    }\
                    button[type='submit'] {\
                        width: 100%;\
                        height:30%;\
                        padding: 10px;\
                        border-radius: 5px;\
                        border: none;\
                        background-color: #007bff;\
                        color: #fff;\
                        cursor: pointer;\
                        transition: background-color 0.3s;\
                        margin-top: 90px; /* 设置按钮上边距 */\
                        font-size:43px;\
                    }\
                    button[type='submit']:hover {\
                        background-color: #0056b3;\
                    }\
                    @media (max-width: 600px) {\
                        form {\
                            width: 100%;\
                        }\
                    }\
                    </style>";

  content += "<form method='post' action='/connect'>";
  content += "<h2>链接无线网络</h2>";
  content += "<select name='ssid'>";

  // 使用先前扫描到的网络列表
  int numNetworks = WiFi.scanComplete();
  for (int i = 0; i < numNetworks; ++i)
  {
    content += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
  }

  content += "</select>";
  content += "<input type='password' name='password' placeholder='请输入密码'>";
  content += "<button type='submit'>Connect</button></form>";

  server.send(200, "text/html", content);
}

void handleConnect()
{
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  // 尝试连接到WiFi网络
  WiFi.begin(ssid.c_str(), password.c_str());

  // 等待WiFi连接
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 3) // 最多尝试3次
  {
    delay(500);
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    //密码错误 外链一个h的网页 
    // 发送页面内容
    server.send(200, "text/html", errorpassword);
  }
  else
  {
    // 连接成功，发送成功页面
    IPAddress apIP = WiFi.softAPIP();
    String successContent = "<style>\
                            body {\
                                font-family: Arial, sans-serif;\
                                text-align: center;\
                                margin-top: 30%;\
                                font-size:30px;\
                            }\
                            </style>";
    successContent += "<body>\
                        <p>链接成功，请退出网页。</p>\
                        <p>Connected to WiFi. ESP32-C3 IP address: " +
                      apIP.toString() + "</p>\
                        </body>";

    server.send(200, "text/html", successContent);
  }
}

void setup()
{
  Serial.begin(921600);

  Serial.println("正在扫描wifi中.");
  // 这里可以插入一个进度条的画面   大概时间是8秒钟吧
  int progress = 0;
  while (WiFi.scanComplete() == -1)
  {
    delay(500);
    Serial.print(".");
    progress++;
    if (progress % 20 == 0)
    { // 每输出20个"."换行一次，模拟进度条移动
      Serial.println();
    }
  }
  Serial.println(); // 扫描完成后换行

  // 扫描WiFi网络
  WiFi.mode(WIFI_STA);
  WiFi.scanNetworks();
  int numNetworks = WiFi.scanComplete();
  for (int i = 0; i < numNetworks; ++i)
  {
    Serial.println("wifi名称：" + WiFi.SSID(i));
  }

  // 将ESP32-C3设置为AP模式，并创建WiFi热点
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // 设置根路径的处理函数
  server.on("/", HTTP_GET, handleRoot);

  // 设置连接处理函数
  server.on("/connect", HTTP_POST, handleConnect);

  // 开始Web服务器
  server.begin();

  Serial.println("HTTP server started");

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(apIP);
}

void loop()
{
  // 处理客户端请求
  server.handleClient();
}
