
#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(13);  
}

void loop() {
  myServo.write(180);   
  delay(200);         

  myServo.write(90);   
  delay(500);

}
