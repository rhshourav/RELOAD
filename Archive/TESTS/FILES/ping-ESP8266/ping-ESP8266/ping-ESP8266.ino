//Follow us on other social media

//https://www.youtube.com/c/ZinTechIdeas
//https://www.facebook.com/zin.techideas.3
//https://www.instagram.com/zintechideas/
//https://twitter.com/Zintechideas
//https://zintechideas.ir/
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h> 
#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);


const char* ssid     = "WiFi Ki Tor Bap Er";
const char* password = "f0kirni007";

const char* remote_host = "www.google.com";

int i;


void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.display();
  delay(10);
  
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("WiFi connected with ip ");  
  Serial.println(WiFi.localIP());
  Serial.print("Pinging host ");  
  Serial.println(remote_host);
}

void loop() {

    Ping.ping(remote_host, 10);  
    i= Ping.averageTime();
    
    Serial.println(i);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Ping:");
  display.display(); 

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35,10);
  display.println(i);
  display.display(); 

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(75,10);
  display.println("ms");
  display.display();

  delay(50); 
  display.clearDisplay();

}
