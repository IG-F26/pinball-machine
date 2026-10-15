// Power Switch
// Elevator Motor - only uses GEN_PWR_OUT to always be on.
// Play Button
// Release Servo
// Flipper Buttons
// Flippers
// Losing IRBBS
// Losing Servo
// Scoring Hole IRBBS
// Spiral Ramp IRBBS
// Hall Effect Sensor for "The Doors"
// Microswitch for Spinner
// Pop Bumpers
// Sound System
// Scoring LEDs
// Score Display

#include "ButtonFlipperPair.hpp"
#include "ScoringIRBBS.hpp"
#include "LosingIRBBS.hpp"
#include "PlayButton.hpp"

ScoringIRBBS scoringHoleSensorIRBBS1;
// ScoringIRBBS scoringHoleSensor2;
LosingIRBBS losingIRBBS;
ButtonFlipperPair leftButtonFlipperPair;
ButtonFlipperPair rightButtonFlipperPair;
PlayButton playButton;

/*
 * All pins are temporary and are subject to change.
 */
const uint8_t GENERAL_PWR = 3;
const uint8_t SCORINGHOLESENSOR1_RECEIVER_PIN = 4;
const uint8_t LOSINGSENSOR_RECEIVER_PIN = 5;
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

void setup() {
    pinMode(GENERAL_PWR, OUTPUT);
    pinMode(SCORINGHOLESENSOR1_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(LOSINGSENSOR_RECEIVER_PIN, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_FLIPPER, OUTPUT);
    pinMode(RIGHT_FLIPPER, OUTPUT);
    pinMode(PLAY_BUTTON, INPUT_PULLUP);

    digitalWrite(GENERAL_PWR, HIGH);
    digitalWrite(LEFT_FLIPPER, LOW);
    digitalWrite(RIGHT_FLIPPER, LOW);

    scoringHoleSensorIRBBS1 = scoringIRBBSInitiate(SCORINGHOLESENSOR1_RECEIVER_PIN,100);
    leftButtonFlipperPair = buttonFlipperInitiate(LEFT_BUTTON, LEFT_FLIPPER);
    rightButtonFlipperPair = buttonFlipperInitiate(RIGHT_BUTTON, RIGHT_FLIPPER);
    losingIRBBS = losingIRBBSInitiate(LOSINGSENSOR_RECEIVER_PIN);
    playButton = playButtonInitiate(PLAY_BUTTON);

}

void loop() {
    if (ballsInPlayRemaining == -1) {
        if (playButtonIsPressed(playButton)) {
            ballsInPlayRemaining = MAX_BALLS;
        }
    } else if (ballsInPlayRemaining == 0) {
        if (playButtonIsPressed(playButton)) {
            ballsInPlayRemaining = MAX_BALLS;
        }
    } else {
        if (resetButtonIsPressed(playButton)) {
            ballsInPlayRemaining = 0;
        }
        buttonFlipperCheck(leftButtonFlipperPair);
        buttonFlipperCheck(rightButtonFlipperPair);
        ballsInPlayRemaining -= lossCheck(losingIRBBS);
    }
}