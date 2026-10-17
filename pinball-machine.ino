#pragma once

#include "ButtonFlipperPair.hpp"
#include "GameLED.hpp"
#include "ScoringIRBBS.hpp"
#include "LosingIRBBS.hpp"
#include "PlayButton.hpp"
#include "ScoringHES.hpp"
#include "Config.hpp"
#include "ReleaseServo.hpp"
#include "toReAdd/Buzzer.hpp"


ScoringHES doorsHES;
ScoringIRBBS scoringHoleIRBBS;
ScoringIRBBS spiralRampIRBBS;
LosingIRBBS losingIRBBS;
ButtonFlipperPair leftButtonFlipperPair;
ButtonFlipperPair rightButtonFlipperPair;
PlayButton playButton;
GameLED gameLED;
Servo releaseServo;

/*
 * Variables keeping track of the game and such.
 */
int8_t ballsInPlayRemaining = -1;

/*
 * Variables keeping track of game score and such.
 */
unsigned int highScore = 0;
unsigned int currentScore = 0;

void setup() {
    pinMode(DOORSHES_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(SCORINGHOLEIRBBS_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(SPIRALRAMPIRBBS_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(LOSING_SENSOR_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_FLIPPER, OUTPUT);
    pinMode(RIGHT_FLIPPER, OUTPUT);
    pinMode(PLAY_BUTTON, INPUT_PULLUP);
    pinMode(LED_DATA_PIN, OUTPUT);
    pinMode(RELEASE_SERVO_OUT, OUTPUT);
    releaseServo.attach(RELEASE_SERVO_OUT);
    // pinMode(BUZZER_PIN, OUTPUT);

    digitalWrite(LEFT_FLIPPER, LOW);
    digitalWrite(RIGHT_FLIPPER, LOW);

    doorsHES = scoringHESInitiate(DOORSHES_RECEIVER_PIN,150);
    scoringHoleIRBBS = scoringIRBBSInitiate(SCORINGHOLEIRBBS_RECEIVER_PIN,100);
    spiralRampIRBBS = scoringIRBBSInitiate(SPIRALRAMPIRBBS_RECEIVER_PIN,100);
    leftButtonFlipperPair = buttonFlipperInitiate(LEFT_BUTTON, LEFT_FLIPPER);
    rightButtonFlipperPair = buttonFlipperInitiate(RIGHT_BUTTON, RIGHT_FLIPPER);
    losingIRBBS = losingIRBBSInitiate(LOSING_SENSOR_RECEIVER_PIN);
    playButton = playButtonInitiate(PLAY_BUTTON);
    gameLED = gameLEDInitiate();
    bootup(gameLED, millis());
    // gameStartSound();
}

void loop() {
    if (ballsInPlayRemaining == -1) {
        if (playButtonIsPressed(playButton)) {
            ballsInPlayRemaining = MAX_BALLS;
        }
        releaseServo.write(CLOSED);
    } else if (ballsInPlayRemaining == 0) {
        if (currentScore > 0 && currentScore > highScore) {
            highScore = currentScore;
            currentScore = 0;
        }
        if (playButtonIsPressed(playButton)) {
            ballsInPlayRemaining = MAX_BALLS;
        }
        releaseServo.write(CLOSED);
        // gameOverSound();
    } else {
        if (resetButtonIsPressed(playButton)) {
            // option to new high score using same code above
            currentScore = 0;
            ballsInPlayRemaining = 0;
        }
        int oldScore = currentScore;
        currentScore += scoreCheck(doorsHES) + scoreCheck(scoringHoleIRBBS) + scoreCheck(spiralRampIRBBS);
        // if (currentScore > oldScore) {
        //     gainPointsSound();
        // }
        buttonFlipperCheck(leftButtonFlipperPair);
        buttonFlipperCheck(rightButtonFlipperPair);
        if (lossCheck(losingIRBBS)) {
            ballsInPlayRemaining -= 1;
            // loseBallSound();
        }
        releaseSequence(releaseServo);
    }
    // updateSound();
}