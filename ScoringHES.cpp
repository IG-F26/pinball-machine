#pragma once
#include "ScoringHES.hpp"
#include "Config.hpp"

ScoringHES scoringHESInitiate(uint8_t rSIG, int pointsToGive) {
    return {rSIG, pointsToGive, false, 0};
}

int scoreCheck(ScoringHES &sensor) {
    unsigned long timeAtCheck = millis();
    sensor.isTriggered = digitalRead(sensor.receiverSIG) == LOW;
    if (!sensor.isTriggered || timeAtCheck - sensor.timeOfPressed < DEBOUNCE_MS) {
        return 0;
    }
    sensor.timeOfPressed = timeAtCheck;
    return sensor.pointsToGive;
}