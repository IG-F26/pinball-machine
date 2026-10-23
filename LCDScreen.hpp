#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal.h>

struct LCDScreen {
    LiquidCrystal lcd;
};

LCDScreen lcdScreenInitiate(uint8_t RS, uint8_t E, uint8_t one, uint8_t two, uint8_t three, uint8_t four);

void loadingScreen(LCDScreen &screen);

// INTERMISSION/LOSS

void displayHighscore(LCDScreen &screen);

// GAMEPLAY

void displayScore(LCDScreen &screen);