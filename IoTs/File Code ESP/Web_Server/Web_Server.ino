#include <ESP8266WiFi.h>

#define LED_PIN 16

const char* ssid = "MinhHue";
const char* password = "123456789";

//Khởi tạo giá trị ban đầu của LED
int value = 1;

WiFiServer server(80);

//Hàm thiết kế giao diện WebServer phản hồi cho Client
String WebServer(int Led_state) {
  String s;
  if (!Led_state) {
    s= "<html><center><h1>Led State is ON now<br>";
    s+= "Click <a href = \"off\"><button>OFF</button></a> to turn off Led</h1></center></html>\n";
  }
  else {
    s= "<html><center><h1>Led State is OFF now<br>";
    s+= "Click <a href = \"on\"><button>ON</button></a> to turn on Led</h1></center></html>\n";
  }
  return s;
}

void setup() {
  Serial.begin(115200);
  delay(10);

  //Cấu hình cho Led Pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, value);

  //Kết nối tới Wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  //Kiểm tra trạng thái kết nối
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi connected");

  //Khởi động Server
  server.begin();
  Serial.println("Server started");

  //In địa chỉ IP của ESP
  Serial.println(WiFi.localIP());
}

void loop() {
  //Kiểm tra Client kết nối
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  //Đợi client gửi phản hồi
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }
  //Đọc phản hồi từ client
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/on") != -1) value=0;
  else {
    if (req.indexOf("/off") != -1) value=1;
    else {
      //Khi truy cập vào IP của ESP thì không stop client
      //mà in ra client trạng thái LED như bình thường
      if (req.indexOf("/") != -1);            
      else {
        Serial.println("Invalid request");
        client.stop();
        return;
      }
    }
  }
  digitalWrite(LED_PIN, value);
  client.flush();
  //Gửi phản hồi cho client
  client.print(WebServer(value));
  delay(1);
  Serial.println("Client disconnected");
}

