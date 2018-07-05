#include <DHT.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  // Khởi động cảm biến DHT11
  dht.begin();
}
 void loop() {
  // DHT đọc nhiệt độ hoặc độ ẩm mất khoảng 250 ms
  // Quá trình đọc có thể lên đến 2s
  delay(2000);
  
  float hum = dht.readHumidity();
  
  // Đọc nhiệt độ ở giai Celsius
  float tem = dht.readTemperature();
  
  // Kiểm tra giá trị nhiệt độ và độ ẩm có đúng không !
  if (isnan(hum) || isnan(tem)) {
    Serial.println("Failed to read from DHT11 sensor !");
    return;
  }
  //Xuất giá trị nhiệt độ và độ ẩm ra Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(tem);
  Serial.println(" *C");
  Serial.println();
}

