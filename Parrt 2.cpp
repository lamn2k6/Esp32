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
