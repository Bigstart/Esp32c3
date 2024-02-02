#include <Arduino.h>
#include <TFT_eSPI.h>
#include "qrcode.h"
#include <WebServer.h>
#include "errorpassword.h"

// WiFi信息
const char *ssid = "ESP32-C3-AP";
const char *password = "password";

WebServer server(80);
TFT_eSPI tft = TFT_eSPI();

// 函数声明
void displayLoadingBar();
void scanWiFiNetworks();
void setupWebServer();
void generateAndDisplayQRCode();
void displayQRCodeOnTFT();
void handleRoot();
void handleConnect();


void setup()
{
  Serial.begin(921600);

  // TFT初始化
  tft.init();
  tft.setRotation(4);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);

  // 显示加载动画
  displayLoadingBar();

  // 扫描WiFi网络
  scanWiFiNetworks();

  // 将ESP32-C3设置为AP模式，并创建WiFi热点
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // Web服务器设置
  setupWebServer();

  // 生成并显示二维码
  generateAndDisplayQRCode();
}

void loop()
{
  // 主循环留空
}

// 扫描wifi时加载动画
void displayLoadingBar()
{
  int screenWidth = 240;
  int screenHeight = 240;
  int barWidth = 200;
  int barHeight = 20;
  int barX = (screenWidth - barWidth) / 2;
  int barY = (screenHeight - barHeight) / 2;
  
  // 计算每个小步增加的长度
  int stepWidth = barWidth / (8 * 1000 / 100); // 8秒内刷新完，每100ms增加一步

  // 绘制加载框的外框
  tft.drawRect(barX, barY, barWidth, barHeight, TFT_WHITE);

  // 绘制加载条
  int currentWidth = 0; // 当前加载条的宽度
  for (int i = 0; i <= barWidth; i += stepWidth)
  {
    // 填充加载条到当前宽度
    tft.fillRect(barX, barY, currentWidth, barHeight, TFT_WHITE);
    currentWidth += stepWidth;
    // 控制加载条的速度
    delay(100); // 每100ms增加一步
  }
  // 确保加载条完全填满
  tft.fillRect(barX, barY, barWidth, barHeight, TFT_WHITE);
}


// 扫描WiFi
void scanWiFiNetworks()
{
  WiFi.mode(WIFI_STA);
  WiFi.scanNetworks();
  while (WiFi.scanComplete() == -1)
  {
    delay(500);
  }
  //扫描完成后 清屏  过度一下 
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0,0,4);
  tft.println("扫描完成 加载中");
}

// Web服务器设置
void setupWebServer()
{
  server.on("/", HTTP_GET, handleRoot);            // 设置根路径的处理函数
  server.on("/connect", HTTP_POST, handleConnect); // 设置连接处理函数
  server.begin();
  Serial.println("HTTP server started");

  IPAddress apIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(apIP);
}

// 生成并显示二维码
void generateAndDisplayQRCode()
{
  tft.fillScreen(TFT_WHITE);
  // 构建 WiFi 信息字符串
  char qrData[100];
  snprintf(qrData, sizeof(qrData), "WIFI:T:WPA;S:%s;P:%s;;", ssid, password);

  // 配置二维码生成选项
  esp_qrcode_config_t cfg = ESP_QRCODE_CONFIG_DEFAULT();
  cfg.max_qrcode_version = 21; // 适当的版本号

  // 生成二维码
  esp_qrcode_generate(&cfg, qrData);

  // 显示在TFT上
  displayQRCodeOnTFT();
}

void displayQRCodeOnTFT()
{
  // 获取二维码的句柄
  esp_qrcode_handle_t qrcode;

  // 获取二维码的边长
  int size = esp_qrcode_get_size(qrcode);

  // 逐像素绘制二维码
  for (int y = 0; y < size; y++)
  {
    for (int x = 0; x < size; x++)
    {
      // 检查每个像素的颜色，黑色像素为真，白色像素为假
      bool isBlack = esp_qrcode_get_module(qrcode, x, y);

      // 在 TFT 显示屏上绘制二维码像素
      if (isBlack)
      {
        tft.drawPixel(x, y, TFT_BLACK);
      }
      else
      {
        tft.drawPixel(x, y, TFT_WHITE);
      }
    }
  }
}

void handleRoot() // 处理根路径请求
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

// 处理连接请求
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
    // 密码错误 外链一个h的网页
    //  发送页面内容
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