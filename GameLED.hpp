#pragma once

#include <FastLED.h>
#include "Config.hpp"

struct GameLED {
    uint8_t ledDataPin;
    CRGB led[NUM_LEDS];
    uint8_t priority;
    unsigned long startAnimationTime;
};

// SETUP

GameLED gameLEDInitiate();

void bootup(GameLED &led, unsigned long startTime);

// INTERMISSION/LOSS

void loseGame(GameLED &led, unsigned long startTime);

// GAMEPLAY

void scorePoint(GameLED &led, unsigned long startTime);

void loseBall(GameLED &led, unsigned long startTime);

void displayPriorityAnimation(GameLED &led, unsigned long startTime);