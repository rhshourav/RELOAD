<<<<<<< HEAD
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char *ssid = "WiFi Ki Tor Bap Er";
const char *password = "f0kirni007";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Connected to WiFi. IP address: " + WiFi.localIP().toString());


  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", "<html><head><style>body {font-family: 'Courier New', monospace;margin: 20px;}#terminal {width: 80%;height: 400px;border: 1px solid #ccc;padding: 10px;overflow-y: scroll;}</style></head><body><div id='terminal'></div><input type='text' id='inputText' placeholder='Type a message...'><button onclick='sendMessage()'>Send</button><script>document.addEventListener('DOMContentLoaded', function () {var terminal = document.getElementById('terminal');var inputText = document.getElementById('inputText');function appendMessage(message) {terminal.innerHTML += message + '<br>';terminal.scrollTop = terminal.scrollHeight;}function sendMessage() {var message = inputText.value;if (message.trim() !== '') {appendMessage('Sent: ' + message);fetch('/send-message', {method: 'POST',headers: {'Content-Type': 'application/json',},body: JSON.stringify({ message: message }),}).then(response => response.json()).then(data => appendMessage('Received: ' + data.response)).catch(error => console.error('Error:', error));inputText.value = '';}}function receiveMessage() {fetch('/receive-message').then(response => response.json()).then(data => {if (data.message) {appendMessage('Received: ' + data.message);}}).catch(error => console.error('Error:', error));}setInterval(receiveMessage, 5000);});</script></body></html>");
  });

  server.on("/send-message", HTTP_POST, [](){
    String data = server.arg("plain");
    Serial.println("Received Message: " + data);
    
    // Process the received message here
    
    String response = "{\"response\":\"Message received\"}";
    server.send(200, "application/json", response);
  });

  server.on("/receive-message", HTTP_GET, [](){
    // Simulate receiving a message from ESP8266 (replace this with actual logic)
    String message = "Hello from ESP8266!";
    String response = "{\"message\":\"" + message + "\"}";
    server.send(200, "application/json", response);
  });

  server.onNotFound([](){
    server.send(404, "text/plain", "Not Found");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
=======
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char *ssid = "WiFi Ki Tor Bap Er";
const char *password = "f0kirni007";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Connected to WiFi. IP address: " + WiFi.localIP().toString());


  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", "<html><head><style>body {font-family: 'Courier New', monospace;margin: 20px;}#terminal {width: 80%;height: 400px;border: 1px solid #ccc;padding: 10px;overflow-y: scroll;}</style></head><body><div id='terminal'></div><input type='text' id='inputText' placeholder='Type a message...'><button onclick='sendMessage()'>Send</button><script>document.addEventListener('DOMContentLoaded', function () {var terminal = document.getElementById('terminal');var inputText = document.getElementById('inputText');function appendMessage(message) {terminal.innerHTML += message + '<br>';terminal.scrollTop = terminal.scrollHeight;}function sendMessage() {var message = inputText.value;if (message.trim() !== '') {appendMessage('Sent: ' + message);fetch('/send-message', {method: 'POST',headers: {'Content-Type': 'application/json',},body: JSON.stringify({ message: message }),}).then(response => response.json()).then(data => appendMessage('Received: ' + data.response)).catch(error => console.error('Error:', error));inputText.value = '';}}function receiveMessage() {fetch('/receive-message').then(response => response.json()).then(data => {if (data.message) {appendMessage('Received: ' + data.message);}}).catch(error => console.error('Error:', error));}setInterval(receiveMessage, 5000);});</script></body></html>");
  });

  server.on("/send-message", HTTP_POST, [](){
    String data = server.arg("plain");
    Serial.println("Received Message: " + data);
    
    // Process the received message here
    
    String response = "{\"response\":\"Message received\"}";
    server.send(200, "application/json", response);
  });

  server.on("/receive-message", HTTP_GET, [](){
    // Simulate receiving a message from ESP8266 (replace this with actual logic)
    String message = "Hello from ESP8266!";
    String response = "{\"message\":\"" + message + "\"}";
    server.send(200, "application/json", response);
  });

  server.onNotFound([](){
    server.send(404, "text/plain", "Not Found");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
>>>>>>> 8a7ce65297df2dec5a6fbe25181b472864c964a7
