#include <Servo.h>

#define SERVO_PIN 10 

Servo steeringServo; 

void setup() {
  steeringServo.attach(SERVO_PIN);
}

void loop() {
  /*en riktning*/
  steeringServo.write(30);
  delay(1000);

  /*rakt fram förhoppnings vis*/
  steeringServo.write(90); 
  delay(1000);

  /*andra riktingen*/
  steeringServo.write(150);
  delay(1000);
}
