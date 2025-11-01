#include <WiFi.h>

const char* ssid_ap="Mu vô địch";
const char* pass_ap="taolaricon";

String ssid_st;
String pass_st;

WiFiClient client;
WiFiServer server(80);

String IP;
String HOST;

WiFiUDP udp;

IPAddress ip(192,168,0,100);
bool mu1= false;
bool mu2= false;
void giao_thuc_UDP_gui(){
  if(udp.beginPacket(ip, 1945)){
    String phan_hoi= Serial.readStringUntil('\n');
    if(!mu1){
    Serial.println("Kết nối thành công");
    udp.println("HELLO");
    mu1=true;
    }
    udp.endPacket();
    phan_hoi.trim();
    if(phan_hoi.length()>1){
    udp.println(phan_hoi);
    udp.endPacket();
    phan_hoi="";
    }
  }
}
void giao_thuc_UDP_nhan(){
  udp.parsePacket();
  
  String n = udp.readString();
  n.trim();
  if(n=="ON"){
    digitalWrite(2, HIGH);
    Serial.println(n);
  }else if(n=="OFF"){
    digitalWrite(2, LOW);
    Serial.println(n);
  }
  
  

}

void giao_thuc_TCP_nhan() {
 
if (client.connected()){
  while (client.available()) {
    String n = client.readStringUntil('\n');
    n.trim();

    if (n.length() > 0) {
 Serial.println(n);

 if (n == "ON") {
   digitalWrite(2, HIGH);
   client.println("LED ON");
 }
 else if (n == "OFF") {
   digitalWrite(2, LOW);
   client.println("LED OFF");
 }
    }
  }
}else client = server.available();
}

void giao_thuc_TCP_gui() {
if(client.connect(IP.c_str(), HOST.toInt())){
  String phan_hoi=Serial.readStringUntil('\n');
  if(!mu2){
    Serial.println("Kết nối thành công");
    client.println("HELLO");
    mu2=true;
  }
    phan_hoi.trim();
    if(phan_hoi.length()>0){
    client.println(phan_hoi);
    phan_hoi="";
    }
  }else {
    client.connect(IP.c_str(), HOST.toInt());
    delay(1000);}
}
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

void loop() {
  
}
