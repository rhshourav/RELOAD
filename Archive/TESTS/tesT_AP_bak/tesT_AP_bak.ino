<<<<<<< HEAD
#include <ESP8266WiFi.h> 
 
const char* ap_ssid = "RELOAD"; //Access Point SSID
const char* ap_password= "shourav10"; //Access Point Password
uint8_t max_connections=8;//Maximum Connection Limit for AP
int current_stations=0, new_stations=0;

const char* ssid = "WiFi Ki Tor Bap Er"; //“your_wifi_ssid”
const char* password = "f0kirni007"; //"your_wifi_password"
 
uint8_t retries=0;
 
void setup()
{
  //Start the serial communication channel
  Serial.begin(115200);
  Serial.println();
   
  //Setting the AP Mode with SSID, Password, and Max Connection Limit
  if(WiFi.softAP(ap_ssid,ap_password,1,false,max_connections)==true)
  {
    Serial.print("Access Point is Creadted with SSID: ");
    Serial.println(ap_ssid);
    Serial.print("Max Connections Allowed: ");
    Serial.println(max_connections);
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("Unable to Create Access Point");
  }

  delay(100);
  Serial.println();
 
  //Try and Connect to the Network
  WiFi.begin(ssid,password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
 
  //Wait for WiFi to connect for a maximum timeout of 20 seconds
  while(WiFi.status()!=WL_CONNECTED && retries<20)
  {
    Serial.print(".");
    retries++;
    delay(1000);
  }
 
  Serial.println();
  //Inform the user whether the timeout has occured, or the ESP8266 is connected to the internet
  if(retries==20)//Timeout has occured
  {
    Serial.print("Unable to Connect to ");
    Serial.println(ssid);
  }
   
  if(WiFi.status()==WL_CONNECTED)//WiFi has succesfully Connected
  {
    Serial.print("Successfully connected to ");
    Serial.println(ssid);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}
 
 
void loop()
{
  //Continuously check how many stations are connected to Soft AP and notify whenever a new station is connected or disconnected
 
  new_stations=WiFi.softAPgetStationNum();
   
  if(current_stations<new_stations)//Device is Connected
  {
    current_stations=new_stations;
    Serial.print("New Device Connected to SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
   
  if(current_stations>new_stations)//Device is Disconnected
  {
    current_stations=new_stations;
    Serial.print("Device disconnected from SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
   
}
=======
#include <ESP8266WiFi.h> 
 
const char* ap_ssid = "RELOAD"; //Access Point SSID
const char* ap_password= "shourav10"; //Access Point Password
uint8_t max_connections=8;//Maximum Connection Limit for AP
int current_stations=0, new_stations=0;

const char* ssid = "WiFi Ki Tor Bap Er"; //“your_wifi_ssid”
const char* password = "f0kirni007"; //"your_wifi_password"
 
uint8_t retries=0;
 
void setup()
{
  //Start the serial communication channel
  Serial.begin(115200);
  Serial.println();
   
  //Setting the AP Mode with SSID, Password, and Max Connection Limit
  if(WiFi.softAP(ap_ssid,ap_password,1,false,max_connections)==true)
  {
    Serial.print("Access Point is Creadted with SSID: ");
    Serial.println(ap_ssid);
    Serial.print("Max Connections Allowed: ");
    Serial.println(max_connections);
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("Unable to Create Access Point");
  }

  delay(100);
  Serial.println();
 
  //Try and Connect to the Network
  WiFi.begin(ssid,password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
 
  //Wait for WiFi to connect for a maximum timeout of 20 seconds
  while(WiFi.status()!=WL_CONNECTED && retries<20)
  {
    Serial.print(".");
    retries++;
    delay(1000);
  }
 
  Serial.println();
  //Inform the user whether the timeout has occured, or the ESP8266 is connected to the internet
  if(retries==20)//Timeout has occured
  {
    Serial.print("Unable to Connect to ");
    Serial.println(ssid);
  }
   
  if(WiFi.status()==WL_CONNECTED)//WiFi has succesfully Connected
  {
    Serial.print("Successfully connected to ");
    Serial.println(ssid);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}
 
 
void loop()
{
  //Continuously check how many stations are connected to Soft AP and notify whenever a new station is connected or disconnected
 
  new_stations=WiFi.softAPgetStationNum();
   
  if(current_stations<new_stations)//Device is Connected
  {
    current_stations=new_stations;
    Serial.print("New Device Connected to SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
   
  if(current_stations>new_stations)//Device is Disconnected
  {
    current_stations=new_stations;
    Serial.print("Device disconnected from SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
   
}
>>>>>>> 8a7ce65297df2dec5a6fbe25181b472864c964a7
