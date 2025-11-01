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
