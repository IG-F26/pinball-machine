#pragma once
#include <Arduino.h>
#include <stdint.h>

/**
 *  Struct stores which pin it tracks, the points it gives (varying between gameplay elements), if it has been tripped,
 *  and time since it was last tripped
 */
struct ScoringHES {
    uint8_t receiverSIG;
    int pointsToGive;
    bool isTriggered;
    unsigned long timeOfPressed;
};

// SETUP
/**
 * Creates a struct of the Hall-Effect Sensor for easy-to-reference names and controlling scoring logic
 *
 * @param rSIG Receiver's signal pin
 * @param pointsToGive How many points this scoring method will give
 * @return ScoringHES struct to reference each loop, plus storing if the sensor has been tripped and time since
 * tripped
 */
ScoringHES scoringHESInitiate(uint8_t rSIG, int pointsToGive);

// INTERMISSION/LOSS
/*
 * Still powered, just nothing checked during this time
 */

// GAMEPLAY
/**
 * Per loop, checks if the Hall-effect sensor has been tripped, giving the player points if so.
 * A delay is added to prevent the sensor from tripping multiple times due to the same ball.
 *
 * @param sensor The sensor struct containing the signal pin to check
 * @return Returns pointsToGive from the sensor struct if the sensor has just been tripped, and 0 otherwise
 */
int scoreCheck(ScoringHES &sensor);