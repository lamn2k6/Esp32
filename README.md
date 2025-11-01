# Esp32
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
bool mu3= false;
