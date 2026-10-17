#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <Servo.h>

const int SERVO_RELEASE_TIME = 500;
const int INITIAL_RELEASE_TIME = 15000;
const int CLOSED = 90;
const int OPEN = 180;

void releaseSequence(Servo releaseServo);