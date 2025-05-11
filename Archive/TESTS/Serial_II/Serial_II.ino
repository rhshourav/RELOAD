void setup() {
  Serial.begin(115200); // Set the baud rate to 115200 bps
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readString();
    Serial.println("Received: " + receivedData);
  }
}
