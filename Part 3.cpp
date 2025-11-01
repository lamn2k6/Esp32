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
