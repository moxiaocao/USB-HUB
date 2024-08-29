#include <Arduino.h>  
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
const char *ssid="quest2";                //输入自己的wifi账号
const char *password="meiyijia";         //输入自己的wifi密码
//定义   此处url等是根据心知官网给的参考文档设置，可以自己创建账号获得key私钥参数
String url="https://api.seniverse.com/v3/weather/now.json";    //请求网址响应
String city="beijing";                                      //输入想要获得的城市
String key="SqCSfIh3uFYt2xlAs";   
unsigned int temp=0;
String name="";
String wea="";
String Time = "no_init";
String WEA="";
 
void weather_init() {
  //连接WiFi
  WiFi.begin(ssid,password);
  Serial.print("正在连接Wi-Fi");
  //检测是否连接成功
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("连接成功");
  Serial.print("IP地址:");
  Serial.println(WiFi.localIP());
}
  
void http_get()
{//创建HTTPCLient 对象
  HTTPClient http;
 
  //发送GET请求
  http.begin(url+"?key="+key+"&location="+city);
  int httpCode=0;
  httpCode=http.GET();
  //获取响应状态码
  Serial.printf("HTTP 状态码:%d",httpCode);
  //获取响应正文
  String response=http.getString();
  Serial.println("响应数据");
  Serial.println(response);
  
  http.end();
  //创建DynamicJsonDocument对象
  DynamicJsonDocument doc(1024);
  //解析JSON数据
  deserializeJson(doc,response);
  //从解析后的JSON文档中获取值
  temp=doc["results"][0]["now"]["temperature"].as<unsigned int>();
  name=doc["results"][0]["location"]["name"].as<String>();
  wea=doc["results"][0]["now"]["text"].as<String>();
  Time = doc["results"][0]["last_update"].as<String>();
}
  
  
void weather_scanf() 
{
  // put your main code here, to run repeatedly:
  http_get();
  Serial.printf("位置：%s\n",name);
  Serial.printf("温度：%d\n",temp);
  Serial.printf("天气：%s\n",wea);
  WEA.concat(Time);
  Serial.println(WEA);
  WEA="";
  // delay(6000);//刷新调用时间，用定时器代替,心知天气刷新时间为10分钟
}