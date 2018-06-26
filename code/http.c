#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "High皮起点1";
const char* password = "b102b102";

const char* host = "15r34407v7.imwork.net"; //需要访问的域名
const int httpsPort = 37170;  // 需要访问的端口
const String url = "/test";   // 需要访问的地址

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // 连接WIFI
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // 显示WIFI地址
}

void loop() {
  Serial.print("connecting to ");  
  Serial.println(host);  

  WiFiClient client;  

  /**
   * 测试是否正常连接
   */
  if (!client.connect(host, httpsPort)) {  
    Serial.println("connection failed");  
    return;  
  }  
  delay(10);  
  
  String postRequest =(String)("GET ") + url + "/ HTTP/1.1\r\n" +  
    "Content-Type: text/html;charset=utf-8\r\n" +  
    "Host: " + host + "\r\n" + 
    "User-Agent: BuildFailureDetectorESP8266\r\n" +
    "Connection: Keep Alive\r\n\r\n";  
  Serial.println(postRequest);  
  client.print(postRequest);  // 发送HTTP请求

  /**
   * 展示返回的所有信息
   */
  String line = client.readStringUntil('\n');
  while(line.length() != 0){
    Serial.println(line);
    line = client.readStringUntil('\n');
  }
  Serial.println(line);
  client.stop();
  delay(3000); 
}
