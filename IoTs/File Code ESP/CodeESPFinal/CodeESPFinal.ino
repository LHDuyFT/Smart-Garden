#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define DHT_PIN 4    //D2 in Node MCU
#define DHT_TYPE DHT11

#define FIREBASE_HOST "dhtfinal.firebaseio.com"
#define FIREBASE_AUTH ""
#define WIFI_SSID "Hue"
#define WIFI_PASSWORD "123456789"

#define DEV1 5       //D1 in Node MCU
#define DEV2 14      //D5 in Node MCU
#define LED  2       //D4 in Node MCU

DHT dht(DHT_PIN, DHT_TYPE);

String Device1, Device2;

void setup() {
  Serial.begin(115200);
  
  //Chân cho Relay
  pinMode(DEV1, OUTPUT);
  pinMode(DEV2, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(DEV1, LOW);
  digitalWrite(DEV2, LOW);
  digitalWrite(LED, LOW);
  
  //Khởi động DHT
  dht.begin();

  //Kết nối Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println(WiFi.localIP());
  digitalWrite(LED, HIGH);
  
  //Khởi tạo với Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  //Đọc nhiệt độ và độ ẩm
  float tem = dht.readTemperature();
  float hum = dht.readHumidity();
  
  if (isnan(hum) || isnan(tem)) {
    return;
  }

  int tem1 = (int)tem;
  int hum1 = (int)hum;

  //Đưa độ ẩm và nhiệt độ lên Firebase
  Firebase.setString("Temperature",(String)tem1);
  
  if (Firebase.failed()) {  
      return;
  }
  delay(300);

  Firebase.setString("Humidity",(String)hum1);
  
  if (Firebase.failed()) {  
      return;
  }
  delay(300);

  //Đọc giá trị Device về ESP
  Device1 = Firebase.getString("Device1");

  if (Firebase.failed()) {
      return;
  }
  delay(300);

  Device2 = Firebase.getString("Device2");

  if (Firebase.failed()) {
      return;
  }
  delay(300);

  //Bật thiết bị
  if (Device1=="true") digitalWrite(DEV1, HIGH);
  else if (Device1=="false") digitalWrite(DEV1, LOW);

  if (Device2=="true") digitalWrite(DEV2, HIGH);
  else if (Device2=="false") digitalWrite(DEV2, LOW);
}
