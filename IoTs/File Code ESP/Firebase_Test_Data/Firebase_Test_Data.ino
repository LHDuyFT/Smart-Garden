#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Khai báo địa chỉ host của firebase

#define FIREBASE_HOST "smarthome-a6ce0.firebaseio.com"
#define FIREBASE_AUTH ""
#define WIFI_SSID "Sakura"
#define WIFI_PASSWORD "244466666"

String device1;

void setup() {

  Serial.begin(115200);
  pinMode(16, OUTPUT);

  //Kết nối tới wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  
  //Khởi tạo với Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  

/*
  //Đưa một số lên RFD
  Firebase.setFloat("Temperature", 32.0);
  //Kiểm tra lỗi
  if (Firebase.failed()) {
      Serial.print("setting temperature failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  //Lấy dữ liệu từ key trên RFD
  Serial.print("Humidity: ");
  Serial.println(Firebase.getFloat("Humidity"));
  delay(1000);
  
  //Đưa một chuỗi lên RFD
  Firebase.setString("Temperature", "90");

  if (Firebase.failed()) {
      Serial.print("setting message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

    //Đưa một chuỗi lên RFD
  Firebase.setString("Humidity", "10");

  if (Firebase.failed()) {
      Serial.print("setting message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

    //Đưa một chuỗi lên RFD
  Firebase.setString("Device1", "false");

  if (Firebase.failed()) {
      Serial.print("setting message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  //Đưa giá trị luận lý lên RFD
  Firebase.setBool("truth", false);

  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  //Đưa một số được cập nhật giá trị thường xuyên
  for (int i=0; i<5; i++) {
      String name = Firebase.pushInt("logs", n++);

      if (Firebase.failed()) {
          Serial.print("pushing /logs failed:");
          Serial.println(Firebase.error());  
          return;
      }
      //In ra key được tạo mới trong key logs (tạo mới ngẫu nhiên)
      Serial.print("pushed: /logs/");
      Serial.println(name);
      delay(1000);
  }

  //Xóa key Humidity đã đưa lên RFD trước đó
  Firebase.remove("Humidity");
  delay(1000);
  */
}
void loop() {
    Firebase.setString("Temperature", "90");

  if (Firebase.failed()) {
      Serial.print("setting message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

    Firebase.setString("Humidity", "-10");

  if (Firebase.failed()) {
      Serial.print("setting message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  Serial.print("Temperature: ");
  Serial.print(Firebase.getString("Temperature"));
  device1=Firebase.getString("Humidity");
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  Serial.println(device1);

  /*if (device1=="true") digitalWrite(16, LOW);
  if (device1=="false") digitalWrite(16, HIGH);
  delay(1000);*/
  
}
