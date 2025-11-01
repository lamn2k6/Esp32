# Part 1: Esp32 STA
Mô tả hoạt động:
1. ESP32 khởi động ở chế độ WIFI_AP_STA (vừa làm điểm truy cập, vừa có thể kết nối WiFi khác).
2. Người dùng nhập tên WiFi (SSID) và mật khẩu (password) qua Serial Monitor.
3. ESP32 sử dụng thông tin vừa nhập để kết nối mạng WiFi.
4. Nếu kết nối thành công, chương trình in ra địa chỉ IP; nếu thất bại, thông báo lỗi.
# Code đầy đủ
```cpp 
#include <WiFi.h>
String ssid_st;
String pass_st;
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
```
# Giải thích chi tiết từng phần
1. Thư viện  
```cpp
#include <WiFi.h>
```
Thư viện hỗ trợ các chức năng WiFi cho ESP32:  
`cpp WiFi.begin(ssid, password)`– kết nối mạng WiFi.  
`cpp cppWiFi.status()` – kiểm tra trạng thái kết nối.  
`cpp WiFi.localIP()` – lấy địa chỉ IP.  
`cpp WiFi.mode()` – chọn chế độ WiFi (AP, STA, hoặc cả hai).

2. Các biến toàn cục 
```python
String ssid_st;
String pass_st;
```
Lưu tên mạng và mật khẩu mà người dùng nhập qua Serial Monitor.  
Dạng `String` giúp dễ dàng thao tác chuỗi (trim, đọc từ Serial...).  

3. Hàm `setup()`  
`Serial.begin(115200);`: Khởi động cổng giao tiếp Serial với tốc độ 115200 baud để giao tiếp với máy tính.    
`WiFi.mode(WIFI_STA);`: Cấu hình ESP32 ở chế độ STA (Station) cho phép ESP32 kết nối vào mạng WiFi có sẵn.

4. Nhập SSID và Password
```python
Serial.println("\nNhập tên wifi");
while (ssid_st.length() == 0) {
  ssid_st = Serial.readString();
  ssid_st.trim();
}
```
`Serial.readString()` đọc dữ liệu nhập từ bàn phím qua Serial Monitor.  
`trim()` loại bỏ khoảng trắng hoặc ký tự xuống dòng (`\r`, `\n`).  
Vòng lặp `while` giữ cho đến khi người dùng nhập xong.  
Làm tương tự với mật khẩu.  

5. Kết nối WiFi  
```python
WiFi.begin(ssid_st.c_str(), pass_st.c_str());
``` 
Bắt đầu kết nối WiFi.  
`c_str()` chuyển kiểu `String` sang dạng chuỗi ký tự (`const char*`) để hàm `WiFi.begin()` hiểu. 

6. Kiểm tra kết nối
```python
while (WiFi.status() != WL_CONNECTED && n < 20) {
  delay(1000);
  Serial.print(".");
  n++;
}
```
Mỗi giây kiểm tra một lần xem đã kết nối chưa.  
Nếu sau 20 lần (20 giây) vẫn chưa kết nối, thoát vòng lặp.  

7. Kết quả
```python
if (WiFi.status() == WL_CONNECTED) {
  Serial.println("\nST IP: ");
  Serial.print(WiFi.localIP());
}
else Serial.println("SSID hoặc pass không đúng");
``` 
Nếu kết nối thành công → in địa chỉ IP của ESP32.  
Nếu thất bại → thông báo lỗi.  

# Kết quả khi chạy  
Ví dụ khi nhập đúng:  
```python
Nhập tên wifi
MyHomeWiFi
Nhập pass wifi
12345678
................
ST IP:
192.168.1.104
```
Nếu nhập sai:  
```python
SSID hoặc pass không đúng
``` 





















