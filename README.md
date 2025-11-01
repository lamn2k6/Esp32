# Part 1: Esp32 STA
** Mô tả hoạt động: **
1.ESP32 khởi động ở chế độ WIFI_AP_STA (vừa làm điểm truy cập, vừa có thể kết nối WiFi khác).
2.Người dùng nhập tên WiFi (SSID) và mật khẩu (password) qua Serial Monitor.
3.ESP32 sử dụng thông tin vừa nhập để kết nối mạng WiFi.
4.Nếu kết nối thành công, chương trình in ra địa chỉ IP; nếu thất bại, thông báo lỗi.
# Code đầy đủ
```c++
#include <WiFi.h>
String ssid_st;
String pass_st;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
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
```
Giải thích chi tiết từng phần
1.Thư viện:
```cpp
#include <WiFi.h>
```
Thư viện hỗ trợ các chức năng WiFi cho ESP32:
```cpp WiFi.begin(ssid, password)```– kết nối mạng WiFi.
WiFi.status() – kiểm tra trạng thái kết nối.

WiFi.localIP() – lấy địa chỉ IP.

WiFi.mode() – chọn chế độ WiFi (AP, STA, hoặc cả hai).






















