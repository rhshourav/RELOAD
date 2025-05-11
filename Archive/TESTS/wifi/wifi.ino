<<<<<<< HEAD
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const int ass = 9999999;
const char index_html[] PROGMEM ={"<!DOCTYPE html> <html lang=en> <head> <title>RLOAD</title> <meta charset=UTF-8> <meta name=viewport content=\"width=device-width, initial-scale=1\" <link rel=stylesheet type=text/css href=util.css> <link rel=stylesheet type=text/css href=style.css> </head> <body> <div class=limiter> <div class=container-login100> <div class=wrap-login100> <form class=\"login100-form validate-form\"> <span class=\"login100-form-title p-b-26\"> Welcome</br> Shourav</br> </span> <span class=\"login100-form-title p-b-48\"> <i class=\"zmdi zmdi-font\"></i> </span> <div class=\"wrap-input100 validate-input\"> <input class=input100 type=text name=SSID> <span class=focus-input100 data-placeholder=SSID></span> </div> <div class=\"wrap-input100 validate-input\" data-validate=\"Enter password\"> <span class=btn-show-pass> <i class=\"zmdi zmdi-eye\"></i> </span> <input class=input100 type=password name=pass> <span class=focus-input100 data-placeholder=Password></span> </div> <div class=container-login100-form-btn> <div class=wrap-login100-form-btn> <div class=login100-form-bgbtn></div> <button class=login100-form-btn> Login </button> </div> </div> </div> </form> </div> </div> </div> <div id=dropDownSelect1></div> <script src=js/jquery-3.2.1.min.js></script> <script src=js/main.js></script> </body> </html>"};
const char style_css[] PROGMEM = {"*/\nfont-face{font-family:Poppins-Medium;src:url(../fonts/poppins/Poppins-Medium.ttf)}*/\nfont-face{font-family:Poppins-Bold;src:url(../fonts/poppins/Poppins-Bold.ttf)}*/\nfont-face{font-family:Poppins-SemiBold;src:url(../fonts/poppins/Poppins-SemiBold.ttf)}*{margin:0;padding:0;box-sizing:border-box}body,html{height:100%;font-family:Poppins-Regular,sans-serif}a{font-family:Poppins-Regular;font-size:14px;line-height:1.7;color:#666;margin:0;transition:all .4s;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s}a:focus{outline:none!important}a:hover{text-decoration:none;color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}h1,h2,h3,h4,h5,h6{margin:0}p{font-family:Poppins-Regular;font-size:14px;line-height:1.7;color:#666;margin:0}ul,li{margin:0;list-style-type:none}input{outline:none;border:none}textarea{outline:none;border:none}textarea:focus,input:focus{border-color:transparent!important}input:focus::-webkit-input-placeholder{color:transparent}input:focus:-moz-placeholder{color:transparent}input:focus::-moz-placeholder{color:transparent}input:focus:-ms-input-placeholder{color:transparent}textarea:focus::-webkit-input-placeholder{color:transparent}textarea:focus:-moz-placeholder{color:transparent}textarea:focus::-moz-placeholder{color:transparent}textarea:focus:-ms-input-placeholder{color:transparent}input::-webkit-input-placeholder{color:#adadad}input:-moz-placeholder{color:#adadad}input::-moz-placeholder{color:#adadad}input:-ms-input-placeholder{color:#adadad}textarea::-webkit-input-placeholder{color:#adadad}textarea:-moz-placeholder{color:#adadad}textarea::-moz-placeholder{color:#adadad}textarea:-ms-input-placeholder{color:#adadad}button{outline:none!important;border:none;background:transparent}button:hover{cursor:pointer}iframe{border:none!important}.txt1{font-family:Poppins-Regular;font-size:13px;color:#666;line-height:1.5}.txt2{font-family:Poppins-Regular;font-size:13px;color:#333;line-height:1.5}.limiter{width:100%;margin:0 auto}.container-login100{width:100%;min-height:100vh;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;flex-wrap:wrap;justify-content:center;align-items:center;padding:15px;background:#f2f2f2}.wrap-login100{width:390px;background:#fff;border-radius:10px;overflow:hidden;padding:77px 55px 33px;box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-moz-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-webkit-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-o-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-ms-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1)}.login100-form{width:100%}.login100-form-title{display:block;font-family:Poppins-Bold;font-size:30px;color:#333;line-height:1.2;text-align:center}.login100-form-title i{font-size:60px}.wrap-input100{width:100%;position:relative;border-bottom:2px solid #adadad;margin-bottom:37px}.input100{font-family:Poppins-Regular;font-size:15px;color:#555;line-height:1.2;display:block;width:100%;height:45px;background:transparent;padding:0 5px}.focus-input100{position:absolute;display:block;width:100%;height:100%;top:0;left:0;pointer-events:none}.focus-input100::before{content:\"\";display:block;position:absolute;bottom:-2px;left:0;width:0;height:2px;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s;background:#6a7dfe;background:-webkit-linear-gradient(left,#21d4fd,#b721ff);background:-o-linear-gradient(left,#21d4fd,#b721ff);background:-moz-linear-gradient(left,#21d4fd,#b721ff);background:linear-gradient(left,#21d4fd,#b721ff)}.focus-input100::after{font-family:Poppins-Regular;font-size:15px;color:#999;line-height:1.2;content:attr(data-placeholder);display:block;width:100%;position:absolute;top:16px;left:0;padding-left:5px;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.input100:focus + .focus-input100::after{top:-15px}.input100:focus + .focus-input100::before{width:100%}.has-val.input100 + .focus-input100::after{top:-15px}.has-val.input100 + .focus-input100::before{width:100%}.btn-show-pass{font-size:15px;color:#999;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;align-items:center;position:absolute;height:100%;top:0;right:0;padding-right:5px;cursor:pointer;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.btn-show-pass:hover{color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}.btn-show-pass.active{color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}.container-login100-form-btn{display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;flex-wrap:wrap;justify-content:center;padding-top:13px}.wrap-login100-form-btn{width:100%;display:block;position:relative;z-index:1;border-radius:25px;overflow:hidden;margin:0 auto}.login100-form-bgbtn{position:absolute;z-index:-1;width:300%;height:100%;background:#a64bf4;background:-webkit-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:-o-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:-moz-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);top:0;left:-100%;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.login100-form-btn{font-family:Poppins-Medium;font-size:15px;color:#fff;line-height:1.2;text-transform:uppercase;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;justify-content:center;align-items:center;padding:0 20px;width:100%;height:50px}.wrap-login100-form-btn:hover .login100-form-bgbtn{left:0}*/\nmedia (max-width: 576px){.wrap-login100{padding:77px 15px 33px}}.validate-input{position:relative}.alert-validate::before{content:attr(data-validate);position:absolute;max-width:70%;background-color:#fff;border:1px solid #c80000;border-radius:2px;padding:4px 25px 4px 10px;top:50%;-webkit-transform:translateY(-50%);-moz-transform:translateY(-50%);-ms-transform:translateY(-50%);-o-transform:translateY(-50%);transform:translateY(-50%);right:0;pointer-events:none;font-family:Poppins-Regular;color:#c80000;font-size:13px;line-height:1.4;text-align:left;visibility:hidden;opacity:0;-webkit-transition:opacity .4s;-o-transition:opacity .4s;-moz-transition:opacity .4s;transition:opacity .4s}.alert-validate::after{content:\"\\f06a\";font-family:FontAwesome;font-size:16px;color:#c80000;display:block;position:absolute;background-color:#fff;top:50%;-webkit-transform:translateY(-50%);-moz-transform:translateY(-50%);-ms-transform:translateY(-50%);-o-transform:translateY(-50%);transform:translateY(-50%);right:5px}.alert-validate:hover:before{visibility:visible;opacity:1}*/\nmedia (max-width: 992px){.alert-validate::before{visibility:visible;opacity:1}}"};

#ifndef STASSID
#define STASSID "WiFi Ki Tor Bap Er"
#define STAPSK  "f0kirni007"
#endif

const char* ssid = STASSID;
const char* password = STAPSK; 

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send_P(200, "text/html", index_html);
  digitalWrite(led, 0);
}

void handleCss(){
  server.send_P(200,"text/css",style_css);
}
void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/style.css",handleCss);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
=======
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const int ass = 9999999;
const char index_html[] PROGMEM ={"<!DOCTYPE html> <html lang=en> <head> <title>RLOAD</title> <meta charset=UTF-8> <meta name=viewport content=\"width=device-width, initial-scale=1\" <link rel=stylesheet type=text/css href=util.css> <link rel=stylesheet type=text/css href=style.css> </head> <body> <div class=limiter> <div class=container-login100> <div class=wrap-login100> <form class=\"login100-form validate-form\"> <span class=\"login100-form-title p-b-26\"> Welcome</br> Shourav</br> </span> <span class=\"login100-form-title p-b-48\"> <i class=\"zmdi zmdi-font\"></i> </span> <div class=\"wrap-input100 validate-input\"> <input class=input100 type=text name=SSID> <span class=focus-input100 data-placeholder=SSID></span> </div> <div class=\"wrap-input100 validate-input\" data-validate=\"Enter password\"> <span class=btn-show-pass> <i class=\"zmdi zmdi-eye\"></i> </span> <input class=input100 type=password name=pass> <span class=focus-input100 data-placeholder=Password></span> </div> <div class=container-login100-form-btn> <div class=wrap-login100-form-btn> <div class=login100-form-bgbtn></div> <button class=login100-form-btn> Login </button> </div> </div> </div> </form> </div> </div> </div> <div id=dropDownSelect1></div> <script src=js/jquery-3.2.1.min.js></script> <script src=js/main.js></script> </body> </html>"};
const char style_css[] PROGMEM = {"*/\nfont-face{font-family:Poppins-Medium;src:url(../fonts/poppins/Poppins-Medium.ttf)}*/\nfont-face{font-family:Poppins-Bold;src:url(../fonts/poppins/Poppins-Bold.ttf)}*/\nfont-face{font-family:Poppins-SemiBold;src:url(../fonts/poppins/Poppins-SemiBold.ttf)}*{margin:0;padding:0;box-sizing:border-box}body,html{height:100%;font-family:Poppins-Regular,sans-serif}a{font-family:Poppins-Regular;font-size:14px;line-height:1.7;color:#666;margin:0;transition:all .4s;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s}a:focus{outline:none!important}a:hover{text-decoration:none;color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}h1,h2,h3,h4,h5,h6{margin:0}p{font-family:Poppins-Regular;font-size:14px;line-height:1.7;color:#666;margin:0}ul,li{margin:0;list-style-type:none}input{outline:none;border:none}textarea{outline:none;border:none}textarea:focus,input:focus{border-color:transparent!important}input:focus::-webkit-input-placeholder{color:transparent}input:focus:-moz-placeholder{color:transparent}input:focus::-moz-placeholder{color:transparent}input:focus:-ms-input-placeholder{color:transparent}textarea:focus::-webkit-input-placeholder{color:transparent}textarea:focus:-moz-placeholder{color:transparent}textarea:focus::-moz-placeholder{color:transparent}textarea:focus:-ms-input-placeholder{color:transparent}input::-webkit-input-placeholder{color:#adadad}input:-moz-placeholder{color:#adadad}input::-moz-placeholder{color:#adadad}input:-ms-input-placeholder{color:#adadad}textarea::-webkit-input-placeholder{color:#adadad}textarea:-moz-placeholder{color:#adadad}textarea::-moz-placeholder{color:#adadad}textarea:-ms-input-placeholder{color:#adadad}button{outline:none!important;border:none;background:transparent}button:hover{cursor:pointer}iframe{border:none!important}.txt1{font-family:Poppins-Regular;font-size:13px;color:#666;line-height:1.5}.txt2{font-family:Poppins-Regular;font-size:13px;color:#333;line-height:1.5}.limiter{width:100%;margin:0 auto}.container-login100{width:100%;min-height:100vh;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;flex-wrap:wrap;justify-content:center;align-items:center;padding:15px;background:#f2f2f2}.wrap-login100{width:390px;background:#fff;border-radius:10px;overflow:hidden;padding:77px 55px 33px;box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-moz-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-webkit-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-o-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-ms-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1)}.login100-form{width:100%}.login100-form-title{display:block;font-family:Poppins-Bold;font-size:30px;color:#333;line-height:1.2;text-align:center}.login100-form-title i{font-size:60px}.wrap-input100{width:100%;position:relative;border-bottom:2px solid #adadad;margin-bottom:37px}.input100{font-family:Poppins-Regular;font-size:15px;color:#555;line-height:1.2;display:block;width:100%;height:45px;background:transparent;padding:0 5px}.focus-input100{position:absolute;display:block;width:100%;height:100%;top:0;left:0;pointer-events:none}.focus-input100::before{content:\"\";display:block;position:absolute;bottom:-2px;left:0;width:0;height:2px;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s;background:#6a7dfe;background:-webkit-linear-gradient(left,#21d4fd,#b721ff);background:-o-linear-gradient(left,#21d4fd,#b721ff);background:-moz-linear-gradient(left,#21d4fd,#b721ff);background:linear-gradient(left,#21d4fd,#b721ff)}.focus-input100::after{font-family:Poppins-Regular;font-size:15px;color:#999;line-height:1.2;content:attr(data-placeholder);display:block;width:100%;position:absolute;top:16px;left:0;padding-left:5px;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.input100:focus + .focus-input100::after{top:-15px}.input100:focus + .focus-input100::before{width:100%}.has-val.input100 + .focus-input100::after{top:-15px}.has-val.input100 + .focus-input100::before{width:100%}.btn-show-pass{font-size:15px;color:#999;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;align-items:center;position:absolute;height:100%;top:0;right:0;padding-right:5px;cursor:pointer;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.btn-show-pass:hover{color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}.btn-show-pass.active{color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}.container-login100-form-btn{display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;flex-wrap:wrap;justify-content:center;padding-top:13px}.wrap-login100-form-btn{width:100%;display:block;position:relative;z-index:1;border-radius:25px;overflow:hidden;margin:0 auto}.login100-form-bgbtn{position:absolute;z-index:-1;width:300%;height:100%;background:#a64bf4;background:-webkit-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:-o-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:-moz-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);top:0;left:-100%;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.login100-form-btn{font-family:Poppins-Medium;font-size:15px;color:#fff;line-height:1.2;text-transform:uppercase;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;justify-content:center;align-items:center;padding:0 20px;width:100%;height:50px}.wrap-login100-form-btn:hover .login100-form-bgbtn{left:0}*/\nmedia (max-width: 576px){.wrap-login100{padding:77px 15px 33px}}.validate-input{position:relative}.alert-validate::before{content:attr(data-validate);position:absolute;max-width:70%;background-color:#fff;border:1px solid #c80000;border-radius:2px;padding:4px 25px 4px 10px;top:50%;-webkit-transform:translateY(-50%);-moz-transform:translateY(-50%);-ms-transform:translateY(-50%);-o-transform:translateY(-50%);transform:translateY(-50%);right:0;pointer-events:none;font-family:Poppins-Regular;color:#c80000;font-size:13px;line-height:1.4;text-align:left;visibility:hidden;opacity:0;-webkit-transition:opacity .4s;-o-transition:opacity .4s;-moz-transition:opacity .4s;transition:opacity .4s}.alert-validate::after{content:\"\\f06a\";font-family:FontAwesome;font-size:16px;color:#c80000;display:block;position:absolute;background-color:#fff;top:50%;-webkit-transform:translateY(-50%);-moz-transform:translateY(-50%);-ms-transform:translateY(-50%);-o-transform:translateY(-50%);transform:translateY(-50%);right:5px}.alert-validate:hover:before{visibility:visible;opacity:1}*/\nmedia (max-width: 992px){.alert-validate::before{visibility:visible;opacity:1}}"};

#ifndef STASSID
#define STASSID "WiFi Ki Tor Bap Er"
#define STAPSK  "f0kirni007"
#endif

const char* ssid = STASSID;
const char* password = STAPSK; 

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send_P(200, "text/html", index_html);
  digitalWrite(led, 0);
}

void handleCss(){
  server.send_P(200,"text/css",style_css);
}
void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/style.css",handleCss);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
>>>>>>> 8a7ce65297df2dec5a6fbe25181b472864c964a7
