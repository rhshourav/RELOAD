#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "WiFi Ki Tor Bap Er"
#define STAPSK "f0kirni007"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  int sec = millis() / 1000;
   int min = sec / 60;
   int hr = min / 60;
        char temp[420];
   snprintf ( temp, 400,

"<html>\
  <head>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <form action='http://192.168.4.1' method='get'>\
    F_name: <input type='text' name='fname'><br>\
    <input type='submit' value='Submit'>\
</form>\
  </body>\
</html>",

      hr, min % 60, sec % 60
   );
  server.send(200, "text/html", temp);
}

void setup() {
  delay(1000);
  WiFi.softAP(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
   server.handleClient();
}
