#include <Stepper.h>

const int STEPS_PER_REV = 3000;
Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11);  // note the pin order

void setup() {
    stepper.setSpeed(10);  // RPM; stay under about 15
}

void loop() {
    // stepper.step(STEPS_PER_REV);   // one turn clockwise
    // delay(100);

}