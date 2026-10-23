#pragma once
#include <Stepper.h>
#include <Arduino.h>
#include <stdint.h>

const int STEPS_PER_REV = 3000;

Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11);  // note the pin order

void setup() {
    stepper.setSpeed(10);  // RPM; stay under about 15
}

void loop() {
    stepper.step(STEPS_PER_REV);   // one turn clockwise
    delay(100);

}

/**
 *  Struct stores which pin it tracks, the points it gives (varying between gameplay elements), if it has been tripped,
 *  and time since it was last tripped
 */
struct ScoringIRBBS {
    uint8_t receiverSIG;
    int pointsToGive;
    bool isTriggered;
    unsigned long timeOfPressed;
};

// SETUP
/**
 * Creates a struct of the IR Break Beam Sensor for easy-to-reference names and controlling scoring logic
 *
 * @param rSIG Receiver's signal pin (the white wire)
 * @param pointsToGive How many points this scoring method will give
 * @return IRBreakBeamSensor struct to reference each loop, plus storing if the sensor has been tripped and time since
 * tripped
 */
ScoringIRBBS scoringIRBBSInitiate(uint8_t rSIG, int pointsToGive);

// INTERMISSION/LOSS
/*
 * Still powered, just nothing checked during this time
 */

// GAMEPLAY
/**
 * Per loop, checks if the IR Breakbeam sensor has been tripped, giving the player points if so.
 * A delay is added to prevent the sensor from tripping multiple times due to the same ball.
 *
 * @param sensor The sensor struct containing the signal pin to check
 * @return Returns pointsToGive from the sensor struct if the sensor has just been tripped, and 0 otherwise
 */
int scoreCheck(ScoringIRBBS &sensor);