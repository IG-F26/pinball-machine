/* References:
 * [https://learn.adafruit.com/ir-breakbeam-sensors/arduino] - Basic IR Breakbeam Sensor Functionality
*/

#pragma once
#include <Arduino.h>
#include <stdint.h>

constexpr unsigned long DEBOUNCE_MS = 1000;

/**
 *  Struct stores which pin it tracks, if it has been tripped, and time since it was last tripped
 */
struct LosingIRBBS {
    uint8_t receiverSIG;
    bool isTriggered;
    unsigned long timeOfPressed;
};

// SETUP
/**
 * Creates a struct of the losing IR Break Beam Sensor
 *
 * @param rSIG Receiver's signal pin (the white wire)
 * @return IRBreakBeamSensor struct to reference each loop, plus storing if the sensor has been tripped and time since
 * tripped
 */
LosingIRBBS losingIRBBSInitiate(uint8_t rSIG);

// INTERMISSION/LOSS
/*
 * Still powered, just nothing checked during this time
 */

// GAMEPLAY
/**
 * Per loop, checks if the IR Breakbeam sensor has been tripped, decrementing the # of balls in play if so.
 * A delay is added to prevent the sensor from tripping multiple times due to the same ball.
 *
 * @param sensor The sensor struct containing the signal pin to check
 * @return Returns 1 if a ball was lost, 0 otherwise
 */
uint8_t lossCheck(LosingIRBBS &sensor);