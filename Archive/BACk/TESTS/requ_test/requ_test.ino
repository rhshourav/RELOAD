/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "WiFi Ki Tor Bap Er";
const char* password = "f0kirni007";

const char* PARAM_INPUT_1 = "SSID";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "input3";


/*
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input2: <input type="text" name="input2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input3: <input type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
</body></html>*/
const char style_css[] PROGMEM = {"*/\nfont-face{font-family:Poppins-Medium;src:url(../fonts/poppins/Poppins-Medium.ttf)}*/\nfont-face{font-family:Poppins-Bold;src:url(../fonts/poppins/Poppins-Bold.ttf)}*/\nfont-face{font-family:Poppins-SemiBold;src:url(../fonts/poppins/Poppins-SemiBold.ttf)}*{margin:0;padding:0;box-sizing:border-box}body,html{height:100%;font-family:Poppins-Regular,sans-serif}a{font-family:Poppins-Regular;font-size:14px;line-height:1.7;color:#666;margin:0;transition:all .4s;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s}a:focus{outline:none!important}a:hover{text-decoration:none;color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}h1,h2,h3,h4,h5,h6{margin:0}p{font-family:Poppins-Regular;font-size:14px;line-height:1.7;color:#666;margin:0}ul,li{margin:0;list-style-type:none}input{outline:none;border:none}textarea{outline:none;border:none}textarea:focus,input:focus{border-color:transparent!important}input:focus::-webkit-input-placeholder{color:transparent}input:focus:-moz-placeholder{color:transparent}input:focus::-moz-placeholder{color:transparent}input:focus:-ms-input-placeholder{color:transparent}textarea:focus::-webkit-input-placeholder{color:transparent}textarea:focus:-moz-placeholder{color:transparent}textarea:focus::-moz-placeholder{color:transparent}textarea:focus:-ms-input-placeholder{color:transparent}input::-webkit-input-placeholder{color:#adadad}input:-moz-placeholder{color:#adadad}input::-moz-placeholder{color:#adadad}input:-ms-input-placeholder{color:#adadad}textarea::-webkit-input-placeholder{color:#adadad}textarea:-moz-placeholder{color:#adadad}textarea::-moz-placeholder{color:#adadad}textarea:-ms-input-placeholder{color:#adadad}button{outline:none!important;border:none;background:transparent}button:hover{cursor:pointer}iframe{border:none!important}.txt1{font-family:Poppins-Regular;font-size:13px;color:#666;line-height:1.5}.txt2{font-family:Poppins-Regular;font-size:13px;color:#333;line-height:1.5}.limiter{width:100%;margin:0 auto}.container-login100{width:100%;min-height:100vh;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;flex-wrap:wrap;justify-content:center;align-items:center;padding:15px;background:#f2f2f2}.wrap-login100{width:390px;background:#fff;border-radius:10px;overflow:hidden;padding:77px 55px 33px;box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-moz-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-webkit-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-o-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1);-ms-box-shadow:0 5px 10px 0 rgba(0,0,0,0.1)}.login100-form{width:100%}.login100-form-title{display:block;font-family:Poppins-Bold;font-size:30px;color:#333;line-height:1.2;text-align:center}.login100-form-title i{font-size:60px}.wrap-input100{width:100%;position:relative;border-bottom:2px solid #adadad;margin-bottom:37px}.input100{font-family:Poppins-Regular;font-size:15px;color:#555;line-height:1.2;display:block;width:100%;height:45px;background:transparent;padding:0 5px}.focus-input100{position:absolute;display:block;width:100%;height:100%;top:0;left:0;pointer-events:none}.focus-input100::before{content:\"\";display:block;position:absolute;bottom:-2px;left:0;width:0;height:2px;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s;background:#6a7dfe;background:-webkit-linear-gradient(left,#21d4fd,#b721ff);background:-o-linear-gradient(left,#21d4fd,#b721ff);background:-moz-linear-gradient(left,#21d4fd,#b721ff);background:linear-gradient(left,#21d4fd,#b721ff)}.focus-input100::after{font-family:Poppins-Regular;font-size:15px;color:#999;line-height:1.2;content:attr(data-placeholder);display:block;width:100%;position:absolute;top:16px;left:0;padding-left:5px;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.input100:focus + .focus-input100::after{top:-15px}.input100:focus + .focus-input100::before{width:100%}.has-val.input100 + .focus-input100::after{top:-15px}.has-val.input100 + .focus-input100::before{width:100%}.btn-show-pass{font-size:15px;color:#999;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;align-items:center;position:absolute;height:100%;top:0;right:0;padding-right:5px;cursor:pointer;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.btn-show-pass:hover{color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}.btn-show-pass.active{color:#6a7dfe;color:-webkit-linear-gradient(left,#21d4fd,#b721ff);color:-o-linear-gradient(left,#21d4fd,#b721ff);color:-moz-linear-gradient(left,#21d4fd,#b721ff);color:linear-gradient(left,#21d4fd,#b721ff)}.container-login100-form-btn{display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;flex-wrap:wrap;justify-content:center;padding-top:13px}.wrap-login100-form-btn{width:100%;display:block;position:relative;z-index:1;border-radius:25px;overflow:hidden;margin:0 auto}.login100-form-bgbtn{position:absolute;z-index:-1;width:300%;height:100%;background:#a64bf4;background:-webkit-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:-o-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:-moz-linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);background:linear-gradient(right,#21d4fd,#b721ff,#21d4fd,#b721ff);top:0;left:-100%;-webkit-transition:all .4s;-o-transition:all .4s;-moz-transition:all .4s;transition:all .4s}.login100-form-btn{font-family:Poppins-Medium;font-size:15px;color:#fff;line-height:1.2;text-transform:uppercase;display:-webkit-box;display:-webkit-flex;display:-moz-box;display:-ms-flexbox;display:flex;justify-content:center;align-items:center;padding:0 20px;width:100%;height:50px}.wrap-login100-form-btn:hover .login100-form-bgbtn{left:0}*/\nmedia (max-width: 576px){.wrap-login100{padding:77px 15px 33px}}.validate-input{position:relative}.alert-validate::before{content:attr(data-validate);position:absolute;max-width:70%;background-color:#fff;border:1px solid #c80000;border-radius:2px;padding:4px 25px 4px 10px;top:50%;-webkit-transform:translateY(-50%);-moz-transform:translateY(-50%);-ms-transform:translateY(-50%);-o-transform:translateY(-50%);transform:translateY(-50%);right:0;pointer-events:none;font-family:Poppins-Regular;color:#c80000;font-size:13px;line-height:1.4;text-align:left;visibility:hidden;opacity:0;-webkit-transition:opacity .4s;-o-transition:opacity .4s;-moz-transition:opacity .4s;transition:opacity .4s}.alert-validate::after{content:\"\\f06a\";font-family:FontAwesome;font-size:16px;color:#c80000;display:block;position:absolute;background-color:#fff;top:50%;-webkit-transform:translateY(-50%);-moz-transform:translateY(-50%);-ms-transform:translateY(-50%);-o-transform:translateY(-50%);transform:translateY(-50%);right:5px}.alert-validate:hover:before{visibility:visible;opacity:1}*/\nmedia (max-width: 992px){.alert-validate::before{visibility:visible;opacity:1}}"};


// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>Login V2</title>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1"
  <link rel="stylesheet" type="text/css" href="util.css">
  <link rel="stylesheet" type="text/css" href="style.css">
<!--===============================================================================================-->
</head>
<body>
  
  <div class="limiter">
    <div class="container-login100">
      <div class="wrap-login100">
        
          <span class="login100-form-title p-b-26">
            Welcome</br>
             Shourav</br>
          </span>
          <span class="login100-form-title p-b-48">
            <i class="zmdi zmdi-font"></i>
          </span>
          <form ation="/get" class="login100-form validate-form">
            <div class="wrap-input100 validate-input" >
              <input class="input100" type="text" name="SSID">
              <span class="focus-input100" data-placeholder="SSID"></span>
            </div>
            <div class="container-login100-form-btn">
              <div class="wrap-login100-form-btn">
                <div class="login100-form-bgbtn"></div>
                <button class="login100-form-btn">
                  ADD
                </button>
              </div>
            </div>
          </form>
          <form action="/get"  class="login100-form validate-form"></form>
            <div class="wrap-input100 validate-input" data-validate="Enter password">
              <span class="btn-show-pass">
                <i class="zmdi zmdi-eye"></i>
              </span>
              
              <input class="input100" type="password" name="pass">
              <span class="focus-input100" data-placeholder="Password"></span>
            </div>
          
            <div class="container-login100-form-btn">
              <div class="wrap-login100-form-btn">
                <div class="login100-form-bgbtn"></div>
                <button class="login100-form-btn">
                  ADD
                </button>
              </div>
            
          </div>
          </div>
        </form>
      </div>
    </div>
  </div>
  

  <div id="dropDownSelect1"></div>
  
<!--===============================================================================================-->
  <script src="js/jquery-3.2.1.min.js"></script>
<!--===============================================================================================-->->
  <script src="js/main.js"></script>

</body>
</html>
)rawliteral";





void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", style_css);
  });
   //server.on("/style.css",handleCss);

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}

/*
void handleCss(){
  server.send_P(200,"text/css",style_css);
}
*/
