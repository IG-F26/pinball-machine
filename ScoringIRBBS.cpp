#pragma once
#include "ScoringIRBBS.hpp"
#include "Config.hpp"

ScoringIRBBS scoringIRBBSInitiate(uint8_t rSIG, int pointsToGive){
    return { rSIG, pointsToGive, false, 0};
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