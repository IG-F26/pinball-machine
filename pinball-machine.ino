#include "ButtonFlipperPair.hpp"
#include "ScoringIRBBS.hpp"
#include "LosingIRBBS.hpp"
#include "PlayButton.hpp"
#include "ScoringHES.hpp"

ScoringHES scoringHES;
ScoringIRBBS scoringIRBBS1;
// ScoringIRBBS scoringIRBBS2;
LosingIRBBS losingIRBBS;
ButtonFlipperPair leftButtonFlipperPair;
ButtonFlipperPair rightButtonFlipperPair;
PlayButton playButton;

/*
 * All pins are temporary and are subject to change.
 */
const uint8_t SCORINGHES_RECEIVER_PIN = 2;
const uint8_t SCORINGIRBBS1_RECEIVER_PIN = 3;
const uint8_t LOSING_SENSOR_RECEIVER_PIN = 5;
const uint8_t LEFT_BUTTON = 6;
const uint8_t RIGHT_BUTTON = 7;
const uint8_t LEFT_FLIPPER = 8;
const uint8_t RIGHT_FLIPPER = 9;
const uint8_t PLAY_BUTTON = 10;

/*
 * Variables keeping track of the game and such.
 */
const uint8_t MAX_BALLS = 5;
int8_t ballsInPlayRemaining = -1;

/*
 * Variables keeping track of game score and such.
 */
unsigned int highScore = 0;
unsigned int currentScore = 0;


void setup() {
    pinMode(SCORINGHES_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(SCORINGIRBBS1_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(LOSING_SENSOR_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_FLIPPER, OUTPUT);
    pinMode(RIGHT_FLIPPER, OUTPUT);
    pinMode(PLAY_BUTTON, INPUT_PULLUP);

    digitalWrite(LEFT_FLIPPER, LOW);
    digitalWrite(RIGHT_FLIPPER, LOW);

    scoringHES = scoringHESInitiate(SCORINGHES_RECEIVER_PIN,150);
    scoringIRBBS1 = scoringIRBBSInitiate(SCORINGIRBBS1_RECEIVER_PIN,100);
    leftButtonFlipperPair = buttonFlipperInitiate(LEFT_BUTTON, LEFT_FLIPPER);
    rightButtonFlipperPair = buttonFlipperInitiate(RIGHT_BUTTON, RIGHT_FLIPPER);
    losingIRBBS = losingIRBBSInitiate(LOSING_SENSOR_RECEIVER_PIN);
    playButton = playButtonInitiate(PLAY_BUTTON);

}

void loop() {
    if (ballsInPlayRemaining == -1) {
        if (playButtonIsPressed(playButton)) {
            ballsInPlayRemaining = MAX_BALLS;
        }
    } else if (ballsInPlayRemaining == 0) {
        if (currentScore > 0 && currentScore > highScore) {
            highScore = currentScore;
            currentScore = 0;
        }
        if (playButtonIsPressed(playButton)) {
            ballsInPlayRemaining = MAX_BALLS;
        }
    } else {
        if (resetButtonIsPressed(playButton)) {
            // option to new high score using same code above
            currentScore = 0;
            ballsInPlayRemaining = 0;
        }
        currentScore += scoreCheck(scoringHES) + scoreCheck(scoringIRBBS1);
        buttonFlipperCheck(leftButtonFlipperPair);
        buttonFlipperCheck(rightButtonFlipperPair);
        ballsInPlayRemaining -= lossCheck(losingIRBBS);
    }
}