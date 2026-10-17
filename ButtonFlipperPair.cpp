#pragma once
#include "ButtonFlipperPair.hpp"
#include "Config.hpp"

ButtonFlipperPair buttonFlipperInitiate(uint8_t bI, uint8_t fO) {
    return {bI, 0, false, fO};
}

void buttonFlipperCheck(ButtonFlipperPair &buttonFlipperPair) {
    unsigned long timeAtCheck = millis();
    bool buttonIsTriggered = digitalRead(buttonFlipperPair.buttonInput) == LOW;

    if (!buttonIsTriggered) {
        digitalWrite(buttonFlipperPair.flipperOutput, LOW);
        buttonFlipperPair.flipperIsTriggered = false;
    } else if (buttonIsTriggered && !buttonFlipperPair.flipperIsTriggered) {
        digitalWrite(buttonFlipperPair.flipperOutput, HIGH);
        buttonFlipperPair.buttonTimeOfPressed = timeAtCheck;
        buttonFlipperPair.flipperIsTriggered = true;
    } else if (timeAtCheck - buttonFlipperPair.buttonTimeOfPressed >= MAX_FLIPPER_TIME) {
        digitalWrite(buttonFlipperPair.flipperOutput, LOW);
    }
}