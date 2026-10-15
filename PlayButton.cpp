#pragma once
#include "PlayButton.hpp"

PlayButton playButtonInitiate(uint8_t bI) {
    return {.buttonInput = bI, .buttonPrevPressed = false, .buttonTimeOfPressed = 0, .cooldownTime = 0};
}

bool playButtonIsPressed(PlayButton &pButton) {
    unsigned long timeAtCheck = millis();
    if (digitalRead(pButton.buttonInput) == LOW && timeAtCheck - pButton.cooldownTime >= COOLDOWN_TIME) {
        pButton.cooldownTime = timeAtCheck;
        return true;
    }
    return false;
}

bool resetButtonIsPressed(PlayButton &pButton) {
    unsigned long timeAtCheck = millis();
    bool isPressed = digitalRead(pButton.buttonInput) == LOW;
    if (!isPressed) {
        pButton.buttonPrevPressed = isPressed;
        return false;
    }
    if (!pButton.buttonPrevPressed) {
        pButton.buttonPrevPressed = isPressed;
        pButton.buttonTimeOfPressed = timeAtCheck;
        return false;
    }
    if (timeAtCheck - pButton.cooldownTime >= COOLDOWN_TIME
        && timeAtCheck - pButton.buttonTimeOfPressed >= MIN_RESET_TIME) {
        pButton.cooldownTime = timeAtCheck;
        return true;
    }
    return false;
}
