#include <Servo.h>

Servo servo;

void setup() {

servo.attach(12); //D6

servo.write(0);

delay(2000);

}

void loop() {

servo.write(145);

delay(1000);

servo.write(0);

delay(1000);

}
