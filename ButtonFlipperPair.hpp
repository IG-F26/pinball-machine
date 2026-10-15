#pragma once
#include <Arduino.h>
#include <stdint.h>

/**
 *  Struct stores which pin goes to the button and flipper,
 *  if button has been activated, and time since button's last activation
 */
struct ButtonFlipperPair {
    uint8_t buttonInput;
    unsigned long buttonTimeOfPressed;
    bool flipperIsTriggered;
    uint8_t flipperOutput;
};

// SETUP
/**
 * Creates struct for a Button-Flipper pairing with easy to read names.
 *
 * @param bI Pin where we read button signal
 * @param fO Pin where we power flipper
 * @return ButtonFlipperPair struct to reference each loop, plus storing if
 * button has been activated and time since activation
 */
ButtonFlipperPair buttonFlipperInitiate(uint8_t bI, uint8_t fO);

// INTERMISSION/LOSS
/*
 * Still powered, just nothing checked during this time
 */

// GAMEPLAY
/**
 * During gameplay, check if button has been pressed; if so, activate its respective flipper.
 *
 * @param buttonFlipperPair The paired object to detect state
 */
void buttonFlipperCheck(ButtonFlipperPair &buttonFlipperPair);
