 * This code will configure ESP8266 in station mode which will then connect with the strongest WiFi network available within the area. 
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
 
//Defining the instance of ESP8266MultiWifi
ESP8266WiFiMulti wifi_multi;
 
//Specifying the SSIDs and Passwords of the Local WiFi Networks in your area
 
//WiFi 1
const char* ssid1 = "PTCL_BB";
const char* password1 = "F4D22ABF";
 
//WiFi 2
const char* ssid2 = "Netnonik";
const char* password2 = "hey_there";
 
//WiFi 3
const char* ssid3 = "basal";
const char* password3 = "go_there";
 
uint16_t connectTimeOutPerAP=5000;//Defines the TimeOut(ms) which will be used to try and connect with any specific Access Point
 
void setup()
{
  //Start the serial communication with the computer
  Serial.begin(115200);
  delay(100);
  Serial.println();
 
  //Adding the WiFi networks to the MultiWiFi instance
  wifi_multi.addAP(ssid1,password1);
  wifi_multi.addAP(ssid2,password2);
  wifi_multi.addAP(ssid3,password3);  
 
  //Wait for ESP8266 to scan the local area and connect with the strongest of the networks defined above
  Serial.print("Connecting to Wi-Fi...");
  while(wifi_multi.run(connectTimeOutPerAP)!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
 
void loop()
{
  //Monitor the WiFi connection before performing any operation
  if(wifi_multi.run()==WL_CONNECTED)
  {
    //ESP8266 is connected to an Access Point
    Serial.print("Connected to ");
    Serial.print(WiFi.SSID());
    Serial.println("...");
    delay(1000);
  }
  else
  {
    //Wait till ESP8266 connects with an AP
    Serial.print("WiFi Disconnected!!!");
    Serial.print("Establishing a connection with a nearby Wi-Fi...");
    while(wifi_multi.run(connectTimeOutPerAP)!=WL_CONNECTED)
    {
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}
