//esp 8266 bord download
//https://arduino.esp8266.com/stable/package_esp8266com_index.json
//html to c/c++ 
//https://tomeko.net/online_tools/cpp_text_escape.php?lang=en



//included Lib files
#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 
#include <Wire.h> 
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
String st;
String content;
int statusCode;
// local network name and password
const char* ssid = "WiFi Ki Tor Bap Er";
const char* password = "f0kirni007";

const char* l_ssid = "RELOAD";
const char* l_password = "shourav10";


//globla variables
int bklightvar = 0 ;


//initing esp web server at port 80;
ESP8266WebServer server(80);


// Requested web server for debug
const char debugTxt[] PROGMEM={"<!DOCTYPE html>\n"
"    <html>\n"
"    <head>\n"
"        <meta http-equiv = 'refresh' content = '0; url =/' />\n"
"    </head>\n"
"    <body>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <p>Welcome Shourav How Are You Doing</p>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"   </body>\n"
"  </html>"};








//debug function


//back to function let's you move back to root after dowing some work
void backTo()
{
  char temp[400];

  snprintf(temp, 400,
    """<!DOCTYPE html>"
    "<html>"
    "<head>"
        "<meta http-equiv = 'refresh' content = '0; url =/' />"
   " </head>"
    "<body>"
   "</body>"
  "</html>""");
  server.send(200, "text/html", temp);
}

 




//main setup
void setup() {


  
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.print("Connecting to network");
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);  
  
    IPAddress local_IP(10, 10, 10, 2);
  IPAddress gateway(10, 10, 10, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(l_ssid, l_password);
  Serial.println("Access Point created");// Connect to WiFi network

  while (WiFi.status() != WL_CONNECTED) {    // Wait for connection
    delay(500);
    Serial.print(".");
    Serial.println("Connecting to WiFi..");
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  // handleing server request
  //server.on("/", handleRoot);
  //  server.on("/test", deBug);
  //  server.on("/reset", rest);
  server.begin();
  Serial.println("HTTP server started");
  test();
}

void loop(void)
{

  // doing Main loop
  server.handleClient();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(100);



}

void test() {
   int n = WiFi.scanNetworks();
  Serial.println("scan completed");
  if (n == 0)
    Serial.println("No WiFi Networks found");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
    WiFi.softAP("ESP-NAME", "");
  Serial.println("Initializing_Wifi_accesspoint");
  launchWeb();
  Serial.println("over");

  server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>ESP8266 WiFi Connectivity Setup ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
       
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  } 
