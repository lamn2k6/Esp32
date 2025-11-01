# Esp32
```c++
#include <WiFi.h>
String ssid_st;
String pass_st;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

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
}
```
dddsvfnfjwfejhn

