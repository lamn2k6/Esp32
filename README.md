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
```python
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
```
`Serial.begin(115200)`  
&emsp;Khởi tạo giao tiếp UART (Serial) giữa ESP32 và máy tính.  
&emsp;Tốc độ truyền dữ liệu là 115200 bit/giây, phù hợp cho debug.  
&emsp;Mọi lệnh `Serial.print()` sau này sẽ hiển thị trên Serial Monitor của Arduino IDE.  
`WiFi.mode(WIFI_STA)`   
&emsp;Đặt ESP32 ở chế độ trạm (Station mode).  
&emsp;Ở chế độ này, ESP32 hoạt động như một thiết bị WiFi thông thường, kết nối vào router thay vì phát WiFi.  

```python
  Serial.println("\nNhập tên wifi");
  while(ssid_st.length()==0){
    ssid_st=Serial.readString();
    ssid_st.trim();
  }
```
In yêu cầu nhập tên WiFi (SSID).  
Dùng `Serial.readString()` để đọc dữ liệu nhập từ người dùng qua Serial Monitor.  
`trim()` loại bỏ khoảng trắng hoặc ký tự xuống dòng dư thừa.  
Vòng `while` giữ cho chương trình dừng lại cho đến khi người dùng nhập xong SSID.  

```python
  delay(1000);

  Serial.println("Nhập pass wifi");
  while(pass_st.length()==0){
    pass_st=Serial.readString();
    pass_st.trim();
  }
```
`delay(1000)` tạm dừng 1 giây để đảm bảo Serial có thời gian xử lý.  
Sau đó chương trình yêu cầu người dùng nhập mật khẩu WiFi (`pass_st`).  
Cách đọc và xử lý tương tự phần nhập SSID ở trên.  

```python
WiFi.begin(ssid_st.c_str(), pass_st.c_str());
```
`WiFi.begin()`: Hàm bắt đầu quá trình kết nối tới WiFi.  
Tham số:  
&emsp;`ssid_st.c_str()` → chuyển chuỗi kiểu `String` sang `const char*` để tương thích với hàm.  
&emsp;`pass_st.c_str()` → mật khẩu WiFi.  
Sau khi gọi, ESP32 sẽ tự động tìm mạng trùng SSID và thử kết nối.  

```python
int n=0;
while(WiFi.status()!= WL_CONNECTED && n<20 ){
  delay(1000);
  Serial.print(".");
  n++;
}
```
Kiểm tra trạng thái kết nối với WiFi.  
`WiFi.status()` trả về mã trạng thái (ví dụ: `WL_CONNECTED` nếu đã kết nối).  
Nếu chưa kết nối, in ra dấu “.” mỗi giây, thử lại tối đa 20 lần (20 giây).  

```python
if (WiFi.status()== WL_CONNECTED) {
  Serial.println("\nST IP: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
} else Serial.println("SSID hoặc pass không đúng");
```
Nếu ESP32 đã kết nối thành công:  
&emsp;In ra địa chỉ IP mà router cấp (`WiFi.localIP()`).  
Nếu thất bại sau 20 giây → báo lỗi "SSID hoặc pass không đúng".  

Kết quả thực thi  
Sau khi nạp code, Serial Monitor sẽ hiển thị:  
&emsp;1. Yêu cầu người dùng nhập SSID và mật khẩu.  
&emsp;2. Hiển thị tiến trình kết nối (bằng dấu “.”).  
&emsp;3. Nếu thành công → in IP.  
&emsp;4. Nếu thất bại → báo lỗi.  
Ví dụ:  
```python
Nhập tên wifi
MyHome
Nhập pass wifi
12345678
....................
ST IP:
192.168.1.37
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
&emsp; Access Point (AP): tạo mạng WiFi riêng, cho phép các thiết bị khác kết nối vào ESP32.  
&emsp; Station (STA): giúp ESP32 kết nối vào mạng WiFi hiện có (ví dụ: WiFi nhà bạn).  
Chương trình này kích hoạt đồng thời cả hai chế độ (WIFI_AP_STA).  
&emsp; ESP32 sẽ tự phát WiFi riêng có tên “Mu vô địch”.  
&emsp; Sau đó, người dùng nhập SSID và mật khẩu WiFi khác qua Serial để ESP32 kết nối vào mạng đó. 
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

# Part 4: Giao tiếp dữ liệu
Mô tả tổng quan  
ESP32 được cấu hình để:  
1. Phát ra một WiFi riêng (Access Point) có SSID “Mu vô địch”.  
2. Cho phép người dùng nhập SSID và mật khẩu WiFi khác để ESP32 kết nối vào mạng đó (Station).  
3. Khởi tạo hai giao thức mạng:  
&emsp; TCP (Transmission Control Protocol): giao thức tin cậy, có kiểm soát lỗi, dùng cho gửi dữ liệu quan trọng (ví dụ: bật/tắt LED).  
&emsp; UDP (User Datagram Protocol): nhanh hơn nhưng không kiểm tra lỗi, thường dùng cho truyền dữ liệu thời gian thực.  
4. Cho phép người dùng nhập lệnh qua Serial để gửi đi qua TCP hoặc UDP.  
5. Nhận dữ liệu từ TCP hoặc UDP và điều khiển LED (GPIO2) tương ứng.  

# Phần khai báo
```python
`#include <WiFi.h>

const char* ssid_ap = "Mu vô địch";
const char* pass_ap = "taolaricon";

String ssid_st;
String pass_st;

WiFiClient client;
WiFiServer server(80);

String IP;
String HOST;

WiFiUDP udp;
IPAddress ip(192,168,0,100);

bool mu1 = false;
bool mu2 = false;
```
`ssid_ap`, `pass_ap`: tên và mật khẩu WiFi mà ESP32 phát ra.  
`ssid_st`, `pass_st`: WiFi mà người dùng nhập để ESP32 kết nối.  
`WiFiClient` và `WiFiServer`: đối tượng phục vụ giao thức TCP.  
`WiFiUDP`: đối tượng phục vụ giao thức UDP.  
`IPAddress ip(192,168,0,100)`: địa chỉ IP đích cho UDP gửi.  
`mu1`, `mu2`: biến trạng thái để in thông báo “Kết nối thành công” một lần duy nhất.  

# Các hàm chính
1. `giao_thuc_UDP_gui()`  
```python
void giao_thuc_UDP_gui() {
  if (udp.beginPacket(ip, 1945)) {
    String phan_hoi = Serial.readStringUntil('\n');
    if (!mu1) {
      Serial.println("Kết nối thành công");
      udp.println("HELLO");
      mu1 = true;
    }
    udp.endPacket();
    phan_hoi.trim();
    if (phan_hoi.length() > 1) {
      udp.println(phan_hoi);
      udp.endPacket();
      phan_hoi = "";
    }
  }
}

```
`udp.beginPacket(ip, 1945)`	Mở một gói dữ liệu UDP để gửi đến địa chỉ IP `192.168.0.100` (được khai báo ở trên) và cổng đích 1945. Hàm trả về `true` nếu bắt đầu gói thành công.  
`Serial.readStringUntil('\n')`	Đọc chuỗi từ Serial (người dùng nhập trên máy tính) cho đến khi gặp ký tự xuống dòng `\n`.  
`if (!mu1)`	Kiểm tra biến `mu1` (ban đầu = false). Nếu chưa từng gửi thông điệp khởi tạo thì in ra thông báo `"Kết nối thành công"` và gửi chuỗi `"HELLO"` qua UDP.  
`udp.println("HELLO")`	Gửi chuỗi `"HELLO"` trong gói UDP hiện tại.  
`udp.endPacket()`	Kết thúc và thực sự phát đi gói UDP (tương đương “gửi đi”). Nếu không gọi dòng này, dữ liệu chưa được gửi.  
`phan_hoi.trim()`	Xoá khoảng trắng đầu/cuối của chuỗi người dùng nhập.  
`if (phan_hoi.length() > 1)`	Nếu người dùng nhập nội dung (dài hơn 1 ký tự), gửi chuỗi đó đi bằng `udp.println()`. Sau khi gửi, xóa nội dung biến để chuẩn bị lần kế tiếp.   

Kết quả thực thi:    
&emsp; Khi người dùng nhập dữ liệu qua Serial, ESP32 gửi chuỗi đó qua UDP tới IP và port đã chỉ định.  
&emsp; Dòng "HELLO" chỉ gửi 1 lần duy nhất khi khởi tạo kết nối.  

2. `giao_thuc_UDP_nhan()`
```python
void giao_thuc_UDP_nhan() {
  udp.parsePacket();
  String n = udp.readString();
  n.trim();
  if (n == "ON") {
    digitalWrite(2, HIGH);
    Serial.println(n);
  } else if (n == "OFF") {
    digitalWrite(2, LOW);
    Serial.println(n);
  }
}
```
`udp.parsePacket()`	Kiểm tra xem có gói dữ liệu UDP đến hay không. Nếu có, chuẩn bị để đọc.  
`udp.readString()`	Đọc toàn bộ dữ liệu có trong gói UDP dưới dạng chuỗi.  
`n.trim()`	Loại bỏ ký tự trắng thừa đầu/cuối (tránh lỗi khi so sánh).  
`if (n == "ON")` / `"OFF"`	Kiểm tra nội dung gói tin nhận được: nếu `"ON"` → bật LED, `"OFF"` → tắt LED.  
`digitalWrite(2, HIGH/LOW)`	Điều khiển chân GPIO2 bật hoặc tắt.  
`Serial.println(n)`	In ra dữ liệu nhận được để người dùng quan sát.  

Kết quả thực thi:  
&emsp; Khi một thiết bị khác gửi gói UDP chứa `"ON"` hoặc `"OFF"`, ESP32 bật/tắt LED và in trạng thái ra Serial.  

3. `giao_thuc_TCP_nhan()`
```python
void giao_thuc_TCP_nhan() {
  if (client.connected()) {
    while (client.available()) {
      String n = client.readStringUntil('\n');
      n.trim();
      if (n.length() > 0) {
        Serial.println(n);
        if (n == "ON") {
          digitalWrite(2, HIGH);
          client.println("LED ON");
        } else if (n == "OFF") {
          digitalWrite(2, LOW);
          client.println("LED OFF");
        }
      }
    }
  } else client = server.available();
}
```
`server.available()` — trả về một `WiFiClient` mới (client kết nối đến server của ESP32) nếu có client TCP đến; nếu không có thì trả về một đối tượng rỗng.  
&emsp; Ở cuối hàm, `client = server.available();` dùng để gán client mới khi có một kết nối đến server. (Nghĩa là ESP32 đóng vai server lắng nghe port 80; khi device khác kết nối thì `server.available()` trả client.)  
`client.connected()` — kiểm tra xem đối tượng client hiện tại đang có kết nối TCP hợp lệ hay không.  
`client.available()` — kiểm tra có byte dữ liệu nào để đọc từ client không.  
&emsp; Vòng while `(client.available())` đọc hết dữ liệu hiện có (nếu có nhiều gói, vòng sẽ lặp).   
`client.readStringUntil('\n')` — đọc tới ký tự xuống dòng (`\n`) hoặc tới timeout của hàm `readStringUntil`.  
Sau khi đọc, `n.trim()` loại bỏ các ký tự trắng đầu/cuối. Nếu `n` là `"ON"` hoặc `"OFF"`, chương trình:  
&emsp; thay đổi trạng thái chân GPIO2 `(digitalWrite(2, ...))` để bật/tắt LED;  
&emsp; phản hồi lại client bằng `client.println("LED ON")` hoặc `"LED OFF"` (gửi qua TCP). 

Kết quả thực thi: hàm này nhận lệnh từ client kết nối đến ESP32 (ESP32 làm server), thực hiện lệnh (bật/tắt LED) và trả lời về client. Nếu chưa có client, nó cố gắng lấy client mới bằng `server.available()`.  

4. `giao_thuc_TCP_gui()`
```python
void giao_thuc_TCP_gui() {
  if (client.connect(IP.c_str(), HOST.toInt())) {
    String phan_hoi = Serial.readStringUntil('\n');
    if (!mu2) {
      Serial.println("Kết nối thành công");
      client.println("HELLO");
      mu2 = true;
    }
    phan_hoi.trim();
    if (phan_hoi.length() > 0) {
      client.println(phan_hoi);
      phan_hoi = "";
    }
  } else {
    client.connect(IP.c_str(), HOST.toInt());
    delay(1000);
  }
}

```
`client.connect(IP.c_str(), HOST.toInt())` — cố gắng tạo kết nối TCP đến server đích có IP và cổng do người dùng nhập.  
&emsp; Trả về `true` nếu liên kết TCP thành công ngay lập tức, `false` nếu không (hàm có thể khởi tạo quá trình kết nối nhưng trả về false nếu chưa kịp hoàn thành).  
Khi `connect()` trả `true` (kết nối có sẵn):  
&emsp;  `Serial.readStringUntil('\n')` đọc dữ liệu người dùng nhập trên Serial để gửi đi.  
&emsp; Nếu `mu2` chưa true — in `"Kết nối thành công"` một lần và gửi "HELLO" đến server đích (dùng `client.println("HELLO"))` — đây là thông điệp khởi tạo/handshake tự tạo.  
&emsp; Nếu người dùng nhập thêm `phan_hoi` (không rỗng sau `trim()`), ESP32 gửi chuỗi đó lên server bằng `client.println(phan_hoi)`.  
Nếu `connect()` trả false, đoạn `else` cố gắng gọi `client.connect(...)` lần nữa và `delay(1000)` để chờ — đây là cách lặp lại nỗ lực kết nối.  

Hành vi tổng quát: hàm này biến ESP32 thành TCP client — nó chủ động kết nối tới một server (IP,cổng do người dùng nhập), sau đó gửi chuỗi nhập từ Serial tới server và gửi một chuỗi khởi tạo `"HELLO"` khi kết nối lần đầu. 

# Phần setup
``` python
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

server.begin();

Serial.println("TCP.Nhập IP: ");
while(IP.length()==0) {
  IP=Serial.readString();
  IP.trim();}

  delay(1000);

Serial.println("TCP.Nhập cổng: ");
while(HOST.length()==0) {
  HOST=Serial.readString();
  HOST.trim();}

client.connect(IP.c_str(), HOST.toInt());

int m=0;
while (!client.connected() && m<20){
Serial.print(".");
delay(1000);
m++;}

udp.begin(1945);

}
```
`Serial.begin(115200);`	Mở giao tiếp Serial giữa ESP32 và máy tính, tốc độ 115200 bps.  
`WiFi.mode(WIFI_AP_STA);`	Cho phép ESP32 vừa làm Access Point (tạo mạng riêng), vừa làm Station (kết nối router ngoài).  
`pinMode(2, OUTPUT); digitalWrite(2, LOW);`	Cấu hình GPIO2 làm output điều khiển LED, ban đầu tắt.  
`WiFi.softAP(ssid_ap, pass_ap);` Tạo WiFi AP có SSID `"Mu vô địch"` và mật khẩu `"taolaricon"`.  
`WiFi.softAPIP()`	Lấy IP của ESP32 trong mạng AP (thường là 192.168.4.1).  
`Serial.readString()` (phần nhập SSID và pass)	Cho phép người dùng nhập tên và mật khẩu WiFi để ESP32 kết nối tới router (STA mode).  
`WiFi.begin(ssid_st.c_str(), pass_st.c_str());`	Bắt đầu kết nối đến WiFi router đã nhập.  
`WiFi.status()`	Kiểm tra trạng thái WiFi (WL_CONNECTED nếu thành công).  
`WiFi.localIP()`	Lấy IP ESP32 trong mạng router.  
`server.begin();`	Khởi động server TCP trên port 80.  
`udp.begin(1945);`	Mở cổng UDP 1945 để nhận/gửi dữ liệu UDP.  
`client.connect(IP.c_str(), HOST.toInt());`	Tạo kết nối TCP client đến địa chỉ và cổng người dùng nhập.

Kết quả thực thi  
&emsp;Sau khi `setup()` chạy xong, ESP32 sẽ:  
&emsp;Phát WiFi riêng `"Mu vô địch"`.  
&emsp;Kết nối vào mạng WiFi khác (nếu nhập đúng SSID và pass).  
&emsp;Sẵn sàng lắng nghe TCP trên cổng 80.  
&emsp;Sẵn sàng gửi/nhận dữ liệu TCP & UDP. 
 
# Part 5: Thao tác nâng cao
Mô tả tổng quan:  
1. Người dùng nhập thông tin mạng WiFi (SSID và password) qua Serial Monitor.  
2. Kết nối ESP32 vào mạng WiFi ở chế độ Station (WIFI_STA).  
3. Tự động quét (scan) và liệt kê các mạng WiFi xung quanh.  
4. Tự động thử kết nối lại (reconnect) nếu mất WiFi.  
5. In ra thông tin kết nối WiFi (RSSI, IP, MAC).  
Chương trình gồm 3 hàm chức năng chính:  
&emsp;`auto_reconnect()` — Tự động kết nối lại WiFi khi mất.  
&emsp;`thong_tin_WiFi()` — Hiển thị thông tin mạng hiện tại.  
&emsp;`scan()` — Quét và liệt kê các mạng WiFi khả dụng.  

# Các hàm chính
1. `Hàm auto_reconnect()`
Mục đích: Tự động kiểm tra và kết nối lại WiFi nếu ESP32 bị mất kết nối.

```python
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

```
`void auto_reconnect()`	Khai báo hàm không có tham số và không trả về giá trị.  
`int n=0;`	Biến đếm số lần thử kết nối lại, giới hạn tối đa 10 lần.  
`if (WiFi.status() != WL_CONNECTED)` Kiểm tra nếu trạng thái WiFi không phải đang kết nối.  
`Serial.println("Mất kết nối...")`	In thông báo lên màn hình Serial.  
`WiFi.reconnect();`	Gọi hàm có sẵn trong thư viện `<WiFi.h>` để thử kết nối lại mạng cũ.  
`while (WiFi.status() != WL_CONNECTED && n<10)`	Lặp tối đa 10 lần, mỗi lần cách nhau 1 giây, cho đến khi WiFi được kết nối.  
`delay(1000); Serial.print(".");`	Tạm dừng 1 giây và in dấu “.” thể hiện tiến trình.  
`if (WiFi.status() == WL_CONNECTED)`	Nếu kết nối thành công sau vòng lặp → in thông báo.  
`else Serial.println("Kết nối lại thất bại!");`	Nếu không kết nối được sau 10 giây → báo lỗi.  

Kết quả thực thi: ESP32 tự động phát hiện khi mất mạng và thử kết nối lại, tránh phải reset thủ công.  

2. `Hàm thong_tin_WiFi()`
Mục đích: Hiển thị thông tin chi tiết của mạng WiFi đang kết nối.
```python
void thong_tin_WiFi(){
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("  • RSSI: %d dBm\n", WiFi.RSSI());
    Serial.printf("  • IP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("  • MAC: %s\n", WiFi.macAddress().c_str());
  }
}
```
`void thong_tin_WiFi()`	Hàm không tham số, không trả về.  
`if (WiFi.status() == WL_CONNECTED)`	Chỉ in thông tin nếu ESP32 đang kết nối mạng.  
`Serial.printf(" • RSSI: %d dBm\n", WiFi.RSSI());`	In độ mạnh tín hiệu WiFi (RSSI) – đơn vị dBm. Giá trị khoảng -30 đến -90.  
`Serial.printf(" • IP: %s\n", WiFi.localIP().toString().c_str());`	Lấy và in địa chỉ IP cục bộ mà router cấp cho ESP32.  
`Serial.printf(" • MAC: %s\n", WiFi.macAddress().c_str());`	Lấy địa chỉ MAC vật lý của ESP32 (định danh duy nhất của thiết bị).  

&emsp;Kết quả thực thi:  
In ra màn hình Serial ba dòng thông tin:  
```python
• RSSI: -55 dBm
• IP: 192.168.1.105
• MAC: 24:6F:28:3B:AA:1F
```
3. `Hàm scan()`
Mục đích: Quét toàn bộ các mạng WiFi xung quanh và hiển thị tên, tín hiệu của từng mạng.  
```python
void scan(){
  if(!mu3){
    WiFi.disconnect();
    Serial.println("Scanning...");
    mu3=true;
  }
  int n = WiFi.scanNetworks();
  if (n>0){
    Serial.printf("Đã tìm thấy: %d SSID \n", n);
    for(int i=0; i<n; i++){
      Serial.printf("%2d. SSID: %s | Tín hiệu: %d dBm \n",
      i+1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
      delay(50);
    }
  } else if (n == 0) {
    Serial.println("Không tìm thấy mạng nào.");
  }
  delay(3456);
}
```
`if(!mu3)`	Kiểm tra cờ `mu3` để chỉ hiển thị thông báo “Scanning...” một lần.  
`WiFi.disconnect();`	Ngắt kết nối hiện tại để có thể quét toàn bộ mạng xung quanh.  
`Serial.println("Scanning...");`	In ra thông báo đang quét.  
`mu3=true;`	Đánh dấu đã quét một lần, không lặp thông báo.  
`int n = WiFi.scanNetworks();` Gọi hàm quét WiFi có sẵn trong thư viện, trả về số mạng tìm thấy.  
`if (n>0)`	Nếu có mạng, tiếp tục liệt kê từng mạng.  
`Serial.printf("Đã tìm thấy: %d SSID \n", n);`	In tổng số mạng WiFi tìm thấy.  
`for(int i=0; i<n; i++)`	Duyệt qua từng mạng WiFi.  
`WiFi.SSID(i)`	Lấy tên (SSID) của mạng thứ i.  
`WiFi.RSSI(i)`	Lấy cường độ tín hiệu (độ mạnh sóng) của mạng thứ i.  
`Serial.printf("%2d. SSID: %s | Tín hiệu %d dBm \n", i+1, ...)` Hàm in ra dữ liệu theo định dạng.  
&emsp;`%2d`	In số nguyên (ở đây là i+1) và đảm bảo có ít nhất 2 ký tự chiều rộng.  
→ Ví dụ: nếu `i=0` thì in “ 1.”, nếu `i=9` thì in “10.”  
&emsp;`%s`	In chuỗi ký tự (ở đây là tên mạng WiFi).  
&emsp;`%d`	In số nguyên (ở đây là cường độ tín hiệu, đơn vị dBm).  
&emsp;`\n`	Xuống dòng sau khi in xong.  
&emsp;`i+1`	Vì mảng bắt đầu từ 0, nên cộng 1 để thành số thứ tự hiển thị bắt đầu từ 1.  
&emsp;`WiFi.SSID(i).c_str()`	Lấy tên mạng WiFi thứ i dưới dạng chuỗi ký tự chuẩn C (kiểu `const char*`).  
&emsp;`WiFi.RSSI(i)`	Lấy độ mạnh tín hiệu của mạng thứ i (đơn vị dBm, càng gần 0 thì càng mạnh).  
`delay(50);`	Nghỉ ngắn giữa mỗi lần in để tránh tràn dữ liệu Serial.  
`else if (n == 0)`	Nếu không có mạng nào được tìm thấy → in thông báo.  
`delay(3456);`	Dừng lại khoảng 3,4 giây để tránh quét liên tục làm treo thiết bị.  

&emsp;Kết quả thực thi:  
Ví dụ khi chạy:
```python
Scanning...
Đã tìm thấy: 3 SSID 
 1. SSID: TP-Link_5G | Tín hiệu: -49 dBm 
 2. SSID: MyHome | Tín hiệu: -67 dBm 
 3. SSID: Cafe_Free | Tín hiệu: -85 dBm
```
# Phần setup
Mục đích: Thiết lập chế độ hoạt động, nhập thông tin mạng và kết nối WiFi.  
```python
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
```
`Serial.begin(115200)`  
&emsp;Khởi tạo giao tiếp UART (Serial) giữa ESP32 và máy tính.  
&emsp;Tốc độ truyền dữ liệu là 115200 bit/giây, phù hợp cho debug.  
&emsp;Mọi lệnh `Serial.print()` sau này sẽ hiển thị trên Serial Monitor của Arduino IDE.  
`WiFi.mode(WIFI_STA)`   
&emsp;Đặt ESP32 ở chế độ trạm (Station mode).  
&emsp;Ở chế độ này, ESP32 hoạt động như một thiết bị WiFi thông thường, kết nối vào router thay vì phát WiFi.  

```python
  Serial.println("\nNhập tên wifi");
  while(ssid_st.length()==0){
    ssid_st=Serial.readString();
    ssid_st.trim();
  }
```
In yêu cầu nhập tên WiFi (SSID).  
Dùng `Serial.readString()` để đọc dữ liệu nhập từ người dùng qua Serial Monitor.  
`trim()` loại bỏ khoảng trắng hoặc ký tự xuống dòng dư thừa.  
Vòng `while` giữ cho chương trình dừng lại cho đến khi người dùng nhập xong SSID.  

```python
  delay(1000);

  Serial.println("Nhập pass wifi");
  while(pass_st.length()==0){
    pass_st=Serial.readString();
    pass_st.trim();
  }
```
`delay(1000)` tạm dừng 1 giây để đảm bảo Serial có thời gian xử lý.  
Sau đó chương trình yêu cầu người dùng nhập mật khẩu WiFi (`pass_st`).  
Cách đọc và xử lý tương tự phần nhập SSID ở trên.  

```python
WiFi.begin(ssid_st.c_str(), pass_st.c_str());
```
`WiFi.begin()`: Hàm bắt đầu quá trình kết nối tới WiFi.  
Tham số:  
&emsp;`ssid_st.c_str()` → chuyển chuỗi kiểu `String` sang `const char*` để tương thích với hàm.  
&emsp;`pass_st.c_str()` → mật khẩu WiFi.  
Sau khi gọi, ESP32 sẽ tự động tìm mạng trùng SSID và thử kết nối.  

```python
int n=0;
while(WiFi.status()!= WL_CONNECTED && n<20 ){
  delay(1000);
  Serial.print(".");
  n++;
}
```
Kiểm tra trạng thái kết nối với WiFi.  
`WiFi.status()` trả về mã trạng thái (ví dụ: `WL_CONNECTED` nếu đã kết nối).  
Nếu chưa kết nối, in ra dấu “.” mỗi giây, thử lại tối đa 20 lần (20 giây).  

```python
if (WiFi.status()== WL_CONNECTED) {
  Serial.println("\nST IP: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
} else Serial.println("SSID hoặc pass không đúng");
```
Nếu ESP32 đã kết nối thành công:  
&emsp;In ra địa chỉ IP mà router cấp (`WiFi.localIP()`).  
Nếu thất bại sau 20 giây → báo lỗi "SSID hoặc pass không đúng".  

Kết quả thực thi  
Sau khi nạp code, Serial Monitor sẽ hiển thị:  
&emsp;1. Yêu cầu người dùng nhập SSID và mật khẩu.  
&emsp;2. Hiển thị tiến trình kết nối (bằng dấu “.”).  
&emsp;3. Nếu thành công → in IP.  
&emsp;4. Nếu thất bại → báo lỗi.  
Ví dụ:  
```python
Nhập tên wifi
MyHome
Nhập pass wifi
12345678
....................
ST IP:
192.168.1.37
```



















