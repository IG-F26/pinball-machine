#pragma once
#include <Arduino.h>
#include <stdint.h>

/**
 *  Struct stores which pin is used for the button and when it was last pressed.
 */
struct PlayButton {
    uint8_t buttonInput;
    bool buttonPrevPressed;
    unsigned long buttonTimeOfPressed;
    unsigned long cooldownTime;
};

// SETUP
/**
 * Creates struct for the Play Button with easy to read names.
 *
 * @param bI Pin where we read button signal
 * @return PlayButton struct with buttonPrevPressed and buttonTimeOfPressed
 * tracking how long a button's been pressed for, and cooldownTime explained above
 */
PlayButton playButtonInitiate(uint8_t bI);

// INTERMISSION/LOSS
/**
 * Determines if the game is ready to start
 *
 * @param pButton PlayButton struct to get info from
 * @return true if button has been pressed, also updating the struct's variables if needed
 */
bool playButtonIsPressed(PlayButton &pButton);

// GAMEPLAY
/**
 * Determines if game should be shut off
 *
 * @param pButton PlayButton struct to get info from
 * @return true if button has been held for long enough, also updating the struct's variables if needed
 */
bool resetButtonIsPressed(PlayButton &pButton);
