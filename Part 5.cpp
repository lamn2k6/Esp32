#include <WiFi.h>
String ssid_st;
String pass_st;
bool mu3= false;
void auto_reconnect(){
  int n=0;
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Mất kết nối WiFi! Đang thử kết nối lại...");
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED && n<10) {
      n++;
      delay(1000);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Kết nối lại thành công!");
    } else {
      Serial.println("Kết nối lại thất bại!");
    }
  }
}

void thong_tin_WiFi(){
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("  • RSSI: %d dBm\n", WiFi.RSSI());
    Serial.printf("  • IP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("  • MAC: %s\n", WiFi.macAddress().c_str());
  }
}

void scan(){
  if(!mu3){
  WiFi.disconnect();
  Serial.println("Scanning...");
  mu3=true;
  }
  int n =WiFi.scanNetworks();
  if (n>0){
    Serial.printf("Đã tìm thấy: %d SSID \n", n);
    for(int i=0; i<n; i++){
      Serial.printf("%2d. SSID: %s | Tín hiệu: %d dBm \n",
      i+1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
      delay(50);

    }
;
}else if (n == 0) {
    Serial.println("Không tìm thấy mạng nào.");
    }
    delay(3456)  ;
  }
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //ST
  Serial.println("\nNhập tên wifi");
  while(ssid_st.length()==0){
  ssid_st=Serial.readString();
  ssid_st.trim();
  }

  delay(1000);

  Serial.println("Nhập pass wifi");
  while(pass_st.length()==0){
  pass_st=Serial.readString();
  pass_st.trim();
  }

WiFi.begin(ssid_st.c_str(), pass_st.c_str());

int n=0;
while(WiFi.status()!= WL_CONNECTED && n<20 ){
  delay(1000);
  Serial.print(".");
  n++;
}

  if (WiFi.status()== WL_CONNECTED) {
    Serial.println("\nST IP: ");
    Serial.print(WiFi.localIP());
    Serial.print("\n");
  }else Serial.println("SSID hoặc pass không đúng");
}
void loop() {
}
