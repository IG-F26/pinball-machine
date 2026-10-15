#pragma once
#include "ScoringIRBBS.hpp"

ScoringIRBBS scoringIRBBSInitiate(uint8_t rSIG, int pointsToGive){
    return {.receiverSIG = rSIG, .pointsToGive = pointsToGive, .isTriggered = false, .timeOfPressed = 0};
}

int scoreCheck(ScoringIRBBS &sensor) {
    unsigned long timeAtCheck = millis();
    sensor.isTriggered = digitalRead(sensor.receiverSIG) == LOW;
    if (!sensor.isTriggered || timeAtCheck - sensor.timeOfPressed < DEBOUNCE_MS) {
        return 0;
    }
    sensor.timeOfPressed = timeAtCheck;
    return sensor.pointsToGive;
}