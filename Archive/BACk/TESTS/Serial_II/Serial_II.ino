<<<<<<< HEAD
void setup() {
  Serial.begin(115200); // Set the baud rate to 115200 bps
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readString();
    Serial.println("Received: " + receivedData);
  }
}
=======
void setup() {
  Serial.begin(115200); // Set the baud rate to 115200 bps
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readString();
    Serial.println("Received: " + receivedData);
  }
}
>>>>>>> 8a7ce65297df2dec5a6fbe25181b472864c964a7
