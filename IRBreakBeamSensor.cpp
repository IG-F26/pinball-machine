#pragma once
#include "IRBreakBeamSensor.hpp"

IRBreakBeamSensor initiate(uint8_t tGND, uint8_t tPWR, uint8_t rGND, uint8_t rPWR, uint8_t rSIG, uint8_t pointsToGive){
    pinMode(tPWR, OUTPUT);
    pinMode(rPWR, OUTPUT);
    pinMode(rSIG, INPUT_PULLUP);
    return {tGND, tPWR, rGND, rPWR, rSIG, pointsToGive, false, 0};
}

int scoreCheck(IRBreakBeamSensor sensor) {
    unsigned long timeAtCheck = millis();
    if (sensor.receiverSIG == HIGH) {
        sensor.isTriggered = false;
    } else if (sensor.isTriggered || timeAtCheck - sensor.timeOfPressed < DEBOUNCE_MS) {
        return 0;
    } else {
        sensor.timeOfPressed = timeAtCheck;
        sensor.isTriggered = true;
        return sensor.pointsToGive;
    }
}