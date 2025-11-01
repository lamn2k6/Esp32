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

# Part 2: Esp32 AP  
Mô tả hoạt động      
1. ESP32 được khởi động ở chế độ WIFI_AP_STA (vừa làm Access Point, vừa có thể kết nối mạng khác). 
2. ESP32 tạo ra một mạng WiFi riêng với SSID và mật khẩu do người lập trình đặt sẵn.  
3. Sau khi khởi tạo thành công, chương trình in địa chỉ IP của Access Point ra Serial Monitor.  
4. Người dùng có thể kết nối điện thoại hoặc laptop vào mạng đó để giao tiếp trực tiếp với ESP32.
# Code đầy đủ
```cpp
#include <WiFi.h>
const char* ssid_ap="Mu vô địch";
const char* pass_ap="taolaricon";
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  //AP
  WiFi.softAP(ssid_ap, pass_ap);
  delay(2000);
  Serial.print("AP IP: ");
  Serial.print(WiFi.softAPIP());
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
const char* ssid_ap = "Mu vô địch";
const char* pass_ap = "taolaricon";
```
`ssid_ap`: tên mạng WiFi mà ESP32 sẽ phát ra.  
`pass_ap`: mật khẩu để thiết bị khác kết nối.  
`Kiểu dữ` liệu `const char*` dùng vì các hàm trong `WiFi.h` cần chuỗi ký tự cố định (C-string).  

3. Hàm `setup()`  
`Serial.begin(115200);`: Khởi động cổng giao tiếp Serial với tốc độ 115200 baud để giao tiếp với máy tính.    
`WiFi.mode(WIFI_AP);`: Cấu hình ESP32 ở chế độ AP (Access Point) phát ra WiFi riêng.  

4. Tạo Access Point
```python
WiFi.softAP(ssid_ap, pass_ap);

```
Hàm này khởi tạo WiFi AP với SSID và password đã khai báo.  
Thiết bị khác có thể tìm thấy WiFi “Mu vô địch” trong danh sách WiFi.  
Tham số:  
  `ssid_ap`: tên WiFi.  
  `pass_ap`: mật khẩu (phải ≥ 8 ký tự).  
Nếu không muốn có mật khẩu, có thể dùng `WiFi.softAP(ssid_ap);`

5. Lấy địa chỉ IP của Access Point  
```python
WiFi.softAPIP();
``` 
Trả về địa chỉ IP của ESP32 trong chế độ Access Point.  
Mặc định thường là 192.168.4.1.    
Dùng `Serial.print()` để in ra màn hình Serial.  

6. Độ trễ (delay) 
```python
delay(2000);
```
Cho ESP32 thời gian khởi tạo và in kết quả lên Serial.  

# Kết quả khi chạy  
Khi nạp chương trình và mở Serial Monitor (baud 115200), bạn sẽ thấy:    
```python
AP IP: 192.168.4.1
```
Trên điện thoại hoặc máy tính, bạn sẽ thấy mạng WiFi:  
```python
Tên WiFi: Mu vô địch
Mật khẩu: taolaricon
```
Kết nối thành công, thiết bị sẽ nhận địa chỉ IP trong dải 192.168.4.x.  

# Past 3: Esp32 AP + STA
Mô tả tổng quan        
ESP32 có hai chế độ WiFi chính:  
  🟢 Access Point (AP): tạo mạng WiFi riêng, cho phép các thiết bị khác kết nối vào ESP32.  
  🔵 Station (STA): giúp ESP32 kết nối vào mạng WiFi hiện có (ví dụ: WiFi nhà bạn).  
Chương trình này kích hoạt đồng thời cả hai chế độ (WIFI_AP_STA).  
  ● ESP32 sẽ tự phát WiFi riêng có tên “Mu vô địch”.  
  ● Sau đó, người dùng nhập SSID và mật khẩu WiFi khác qua Serial để ESP32 kết nối vào mạng đó. 
# Code đầy đủ
```cpp
#include <WiFi.h>

const char* ssid_ap="Mu vô địch";
const char* pass_ap="taolaricon";

String ssid_st;
String pass_st;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  //AP
  WiFi.softAP(ssid_ap, pass_ap);
  delay(2000);
  Serial.print("AP IP: ");
  Serial.print(WiFi.softAPIP());
  delay(5000);

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
`WiFi.mode()`: chọn chế độ hoạt động (AP, STA hoặc cả hai).  
`WiFi.softAP()`: tạo mạng WiFi riêng.  
`WiFi.begin()`: kết nối vào mạng WiFi khác.  
`WiFi.localIP()`: lấy IP của ESP32 khi ở chế độ Station.  
`WiFi.softAPIP()`: lấy IP của ESP32 khi ở chế độ Access Point.  

2. Các biến toàn cục 
```python
const char* ssid_ap = "Mu vô địch";
const char* pass_ap = "taolaricon";
String ssid_st;
String pass_st;
```
`ssid_ap`: tên mạng WiFi mà ESP32 sẽ phát ra.  
`pass_ap`: mật khẩu để thiết bị khác kết nối.  
Lưu tên mạng và mật khẩu người dùng nhập vào để ESP32 dùng kết nối chế độ STA.    

3. Hàm `setup()`  
`Serial.begin(115200);`: Khởi động cổng giao tiếp Serial với tốc độ 115200 baud để giao tiếp với máy tính.    
`WiFi.mode(WIFI_AP_STA);`: Kích hoạt chế độ kép (Dual Mode) — cho phép ESP32 phát WiFi riêng (Access Point). Đồng thời kết nối WiFi khác (Station).  

4. Phát WiFi riêng (Access Point)
```python
WiFi.softAP(ssid_ap, pass_ap);
Serial.print(WiFi.softAPIP());

```
`WiFi.softAP()` khởi tạo mạng WiFi riêng.  
`WiFi.softAPIP()` trả về địa chỉ IP mặc định của AP: 192.168.4.1.  
Thiết bị khác có thể kết nối vào mạng này.  

5. Kết nối chế độ Station (STA)   
```python
Serial.readString();
```
Đọc chuỗi ký tự người dùng nhập từ Serial Monitor.  
trim() xóa ký tự \r hoặc \n khi nhấn Enter.  

```python
WiFi.begin(ssid_st.c_str(), pass_st.c_str());
```
begin() khởi động quá trình kết nối WiFi.  
c_str() chuyển đổi kiểu String sang chuỗi C (const char*).  

```python
while (WiFi.status() != WL_CONNECTED && n < 20) { ... }
```
Kiểm tra trạng thái kết nối trong 20 giây (mỗi giây in một dấu “.”).  
Nếu thành công → in địa chỉ IP nhận từ router.  
Nếu thất bại → thông báo lỗi “SSID hoặc pass không đúng”.  

# Kết quả khi chạy  
Khi mở Serial Monitor (baud 115200), bạn sẽ thấy:  
```python
AP IP: 192.168.4.1
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
















