/*
使用的是高德的天气api
初始的数据已经处理好了 可以直接用  要装入ArduinoJson库 最新版的就可以吧   
*/



#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char ssid[] = "xiaomi14";  // WIFI名称 修改这2个就可以了
const char pass[] = "21212121m";  // WIFI密码

String url = "https://restapi.amap.com/v3/weather/weatherInfo";
String city = "021";
String key = "4f1235eb9ad07a534aa8056d57e5cdc8";

void setup() {
  Serial.begin(921600);
  Serial.print("正在连接WIFI ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("连接成功");

  HTTPClient http;
  // 构造完整的请求URL
  String requestUrl = "https://restapi.amap.com/v3/weather/weatherInfo?city=310112&key=" + key;

  // 指定访问URL
  http.begin(requestUrl);

  // 接受响应状态码
  int http_code = http.GET();

  //Serial.print("状态码:");
  //Serial.println(http_code);

  String response = http.getString();
  Serial.print("响应数据:\n");
  //Serial.println(response);

  // 关闭 HTTP 连接
  http.end();

 // 创建一个 JsonDocument 对象
  DynamicJsonDocument doc(256);

  // 解析 JSON 数据
  deserializeJson(doc, response);

  // 获取 "lives" 数组中的第一个元素
  JsonObject firstEntry = doc["lives"][0];


  // 获取各个字段的值
  String province = firstEntry["province"].as<String>();      //省份
  String city = firstEntry["city"].as<String>();              //区
  String weather = firstEntry["weather"].as<String>();      //天气
  unsigned int temp = firstEntry["temperature"].as<unsigned int>();   //温度
  int hum = firstEntry["humidity"].as<int>();                         //湿度
  String winddirection = firstEntry["winddirection"].as<String>();    //风向
  String windpower = firstEntry["windpower"].as<String>();            //风力
  String info = firstEntry["reporttime"].as<String>();                //更新时间

  // 输出各个字段的值
  Serial.println(province+" "+city);
  Serial.println("天气：" + weather);
  Serial.println("温度：" + String(temp)+"℃");
  Serial.println("湿度：" + String(hum)+"%");
  Serial.println(winddirection + "风" + String(windpower) + "级");
  Serial.println("更新时间：" + info);

}

void loop() {
  // Empty, since we're not doing anything in the loop
}
