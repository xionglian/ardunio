#include <ESP8266WiFi.h>  
const char* ssid     = "High皮起点1";  
const char* password = "b102b102";  
  
const char * host = "www.baidu.com";  
const int httpPort = 80;  
  
void setup() {  
  Serial.begin(9600);  
  delay(10);  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
    
  WiFi.begin(ssid, password);  
    
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.print(".");  
  }  
  
  Serial.println("");  
  Serial.println("WiFi connected");    
  Serial.println("IP address: ");  
  Serial.println(WiFi.localIP());  
}  
  
void loop() {  
  
  Serial.print("connecting to ");  
  Serial.println(host);  
    
  WiFiClient client;  
    
  if (!client.connect(host, httpPort)) {  
    Serial.println("connection failed");  
    return;  
  }  
   delay(10);  
  String recv = readLine();//将从串口接收的数据发送到服务器，readLine()方法可以自行设计  
  while (recv != "0")  
  {  
    if (recv.length() && recv != "0" && recv != "-1200"){//与我的项目相匹配的判断条件  
      String data = (String)"{\"heartbeat\":\"" + recv+"\"}";  
      int length = data.length();  
        
      String postRequest =(String)("POST ") + "/ HTTP/1.1\r\n" +  
          "Content-Type: application/json;charset=utf-8\r\n" +  
          "Host: " + host + ":" + httpPort + "\r\n" +            
          "Content-Length: " + length + "\r\n" +  
          "Connection: Keep Alive\r\n\r\n" +  
          data+"\r\n";  
       Serial.println(postRequest);  
       client.print(postRequest);  
       delay(100);  
       break;  
  }          
    recv = readLine();  
  }  
  client.stop();  
}  
  
String readLine()  
{  
    String str;  
    while (Serial.available())  
    {  
        char temp = Serial.read();  
        if (temp != '\n') {  
          str += char(temp);  
          delay(2);  
        }//delete temp;  
        else break;//delete temp;  
    }  
    return str;  
}  

