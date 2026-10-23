#pragma once

#include "ReleaseServo.hpp"

void releaseSequence(Servo releaseServo) {
    unsigned long elapsed = millis();
    if (elapsed < SERVO_RELEASE_TIME) {
        releaseServo.write(OPEN);
    } else if (elapsed < INITIAL_RELEASE_TIME) {
        releaseServo.write(CLOSED);
    } else if (elapsed < INITIAL_RELEASE_TIME + SERVO_RELEASE_TIME) {
        releaseServo.write(OPEN);
    } else if (elapsed < INITIAL_RELEASE_TIME*2) {
        releaseServo.write(CLOSED);
    } else if (elapsed < INITIAL_RELEASE_TIME*2 + SERVO_RELEASE_TIME) {
        releaseServo.write(OPEN);
    } else if (elapsed < INITIAL_RELEASE_TIME*3) {
        releaseServo.write(CLOSED);
    } else if (elapsed < INITIAL_RELEASE_TIME*3 + SERVO_RELEASE_TIME) {
        releaseServo.write(OPEN);
    } else if (elapsed % 5000 < 500) {
        releaseServo.write(OPEN);
    } else {
        releaseServo.write(CLOSED);
    }
}