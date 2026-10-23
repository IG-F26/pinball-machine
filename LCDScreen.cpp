#pragma once

#include "LCDScreen.hpp"

LCDScreen lcdScreenInitiate(uint8_t RS, uint8_t E, uint8_t one, uint8_t two, uint8_t three, uint8_t four) {
    LiquidCrystal ret(RS, E, one, two, three, four);
    ret.begin(16, 2);
    return {ret};
}

void loadingScreen(LCDScreen &screen) {
    screen.lcd.setCursor(0, 0);        // column 0, second row
    screen.lcd.print("                ");
    screen.lcd.print("IOTA GAMMA");
    if (millis() % 6000 < 1000) {
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("PB MACHINE");
    } else if (millis() % 6000 < 2000) {
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("PB MACHINE!");
    } else if (millis() % 6000 < 3000) {
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("PB MACHINE!!");
    } else if (millis() % 6000 < 4000) {
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("PB MACHINE!!!");
    } else if (millis() % 6000 < 5000) {
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("PB MACHINE!!");
    } else {
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("PB MACHINE!");
    }


}

// INTERMISSION/LOSS

void displayHighscore(LCDScreen &screen, unsigned int playerScore, unsigned int highScore) {
    if (millis() % 6000 < 3000) {
        screen.lcd.setCursor(0, 0);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("Your Score:");
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print(playerScore);
    } else {
        screen.lcd.setCursor(0, 0);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print("High Score:");
        screen.lcd.setCursor(0, 1);        // column 0, second row
        screen.lcd.print("                ");
        screen.lcd.print(highScore);
    }
}

// GAMEPLAY

void displayScore(LCDScreen &screen, unsigned int playerScore) {
    screen.lcd.setCursor(0, 0);        // column 0, second row
    screen.lcd.print("                ");
    screen.lcd.print("Your Score:");
    screen.lcd.setCursor(0, 1);        // column 0, second row
    screen.lcd.print("                ");
    screen.lcd.print(playerScore);
}