#include <SoftwareSerial.h>

String wifiName ="High皮起点1";
String wifiPwd = "b102b102";


SoftwareSerial mySerial(10,11);//RX TX
//SoftwareSerial mySerial(0,1);//RX TX
String str;
void setup() {

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);//wifi模块串口
  Serial.begin(9600);//连pc串口
  delay(1000);
  //设置为station模式
  mySerial.println("AT+CWMODE=1");
  //连接wifi
  mySerial.println("AT+CWJAP=\""+wifiName+"\",\""+"\""+wifiPwd+"\"");
  //检测是否连接
  mySerial.println("AT+CIFSR");
 

  while(Serial.available()){Serial.write(Serial.read());}
  while(mySerial.available()){Serial.write(mySerial.read());}
  Serial.println("wificar init");
}
  
void loop() {
    if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    String data;
    unsigned long start;
    start = millis();
    while (millis()-start<100) 
      {
        if (Serial.available()>0)
        {
          char c = Serial.read();
          data += c;
        }
        if (data.indexOf("\nOK")!=-1)
        {
          break;
        }
      }
      mySerial.println(data);
  }
}
 
 
/**
* 读取串口缓冲区里面的数据
*/
int ReceiveWifiMessage(char *buf){
  //+IPD,<len>:<data>
  //+IPD,<id>,<len>:<data>
  String data = "";
  if (mySerial.available()>0){
    unsigned long start;
    start = millis();
    char c0 = mySerial.read();
    if (c0 == '+')
    {
      while (millis()-start<100) 
      {
        if (mySerial.available()>0)
        {
          char c = mySerial.read();
          data += c;
        }
        if (data.indexOf("\nOK")!=-1)
        {
          break;
        }
      }
 
      int sLen = strlen(data.c_str());
      int i,j;
      for (i = 0; i <= sLen; i++){
        if (data[i] == ':'){
          break;
        }
      }
      //判断是否存在id
      boolean found = false;
      for (j = 4; j <= i; j++){
        if (data[j] == ','){
          found = true;
          break;
        }
      }
      int iSize;
      if(found ==true){
        //+IPD,<id>,<len>:<data>
          String _size = data.substring(j+1, i);
          iSize = _size.toInt();
          String str = data.substring(i+1, i+1+iSize);
          strcpy(buf, str.c_str());     
      }else{
        //+IPD,<len>:<data>     
          String _size = data.substring(4, i);
          iSize = _size.toInt();
          String str = data.substring(i+1, i+1+iSize);
          strcpy(buf, str.c_str());
      }
      return iSize;
    }else{
      while(mySerial.read() >= 0){}  
    }
  }
  return 0;
}
