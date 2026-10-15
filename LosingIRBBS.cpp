#pragma once
#include "LosingIRBBS.hpp"
#include "Config.hpp"

LosingIRBBS losingIRBBSInitiate(uint8_t rSIG) {
    return {rSIG, false, 0};
}

uint8_t lossCheck(LosingIRBBS &sensor) {
    unsigned long timeAtCheck = millis();
    sensor.isTriggered = digitalRead(sensor.receiverSIG) == LOW;
    if (!sensor.isTriggered || timeAtCheck - sensor.timeOfPressed < DEBOUNCE_MS) {
        return 0;
    }
    sensor.timeOfPressed = timeAtCheck;
    return 1;
}