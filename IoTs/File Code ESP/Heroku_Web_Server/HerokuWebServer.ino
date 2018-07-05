
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <SerialCommand.h>  
#include <ArduinoJson.h>
#include "DHT.h"

 
SerialCommand sCmd;
SocketIOClient client;
const char* ssid = "Connectify-me";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "lasajut0";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.
 
char host[] = "gentle-savannah-83491.herokuapp.com";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 80;                  //Cổng dịch vụ socket server do chúng ta tạo!
char namespace_esp8266[] = "esp8266";   //Thêm Arduino!
 
//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// mà chúng ta cần quan tâm đó là
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;
#define DHTPIN 2
// Su dung cam bien DHT11
#define DHTTYPE DHT11
// Cau hinh chan DHT 
DHT dht(DHTPIN, DHTTYPE, 15);

byte red = 4, blue = 5; // led đỏ đối vô digital 4, led xanh đối vô digital 5 
// Pin

StaticJsonBuffer<200> jsonBuffer;
String JSON;
JsonObject& root = jsonBuffer.createObject();
 void setup()
        {
          
         
         //pinMode 4 đèn LED là OUTPUT
           pinMode(red,OUTPUT);
          pinMode(blue,OUTPUT);
  
        Serial.begin(115200);
        // Mo Serial
        
 
        //Việc đầu tiên cần làm là kết nối vào mạng Wifi
        Serial.print("Ket noi vao mang ");
        Serial.println(ssid);
 
        //Kết nối vào mạng Wifi
        WiFi.begin(ssid, password);
 
        //Chờ đến khi đã được kết nối
        while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
                delay(500);
                Serial.print('.');
        }
 
        Serial.println();
        Serial.println(F("Da ket noi WiFi"));
        Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
        Serial.println(WiFi.localIP());
 
        if (!client.connect(host, port, namespace_esp8266)) {
                Serial.println(F("Ket noi den socket server that bai!"));
                return;
        }
        
        Serial.println("Da san sang nhan lenh");
         dht.begin();

}
 
void loop()
        {
               
        //Khi bắt được bất kỳ sự kiện nào thì chúng ta có hai tham số:
        //  +RID: Tên sự kiện
        //  +RFull: Danh sách tham số được nén thành chuỗi JSON!
        if (client.monitor()) {
 
            
                //in ra serial monitor
                Serial.print(RID);
                Serial.print(' ');
                Serial.println(Rfull);
        }
        
        
        if (RID == "device1on")
        {
          digitalWrite(red , HIGH);
         }
         if (RID == "device1off")
        {
          digitalWrite(red , LOW);
          }
         if (RID == "device2on")
        {
          digitalWrite(blue , HIGH);
          }
         if (RID == "device2off")
        {
          digitalWrite(blue , LOW);
          }
         if(RID == "UPDATE"){
          float t = dht.readTemperature();
          float h = dht.readHumidity();
         Serial.print("Nhiet do: ");
         Serial.println(t);
         Serial.print("Do am: ");
         Serial.print(h);
         delay(1000);
        float temp1 = t;
        float temp2 = h;
          root["nhietdo"] = temp1;
          root["doam"] = temp2;
          root.printTo(JSON);
          client.sendJSON("SEND UPDATE", JSON);
          }
        //Kết nối lại!
        if (!client.connected()) {
            client.reconnect(host, port, namespace_esp8266);
        }
 
        sCmd.readSerial();
}

