/* References:
 * [https://learn.adafruit.com/ir-breakbeam-sensors/arduino] - Basic IR Breakbeam Sensor Functionality
*/

#pragma once
#include <Arduino.h>
#include <stdint.h>

#define DEBOUNCE_MS 100

#ifndef PINBALL_MACHINE_IRBREAKBEAMSENSOR_H
#define PINBALL_MACHINE_IRBREAKBEAMSENSOR_H

/* There are 5 pins:
* Transmitter and Receiver GND
* Transmitter and Receiver PWR
* Receiver SIGNAL -- our digital input; when beam is broken, outputs LOW to our arduino
*
* There really isn't a need to store these pins except for the receiver signal
* and maybe the transmitter pwr when turning on machine
*/
struct IRBreakBeamSensor {
    uint8_t transmitterGND;
    uint8_t transmitterPWR;
    uint8_t receiverGND;
    uint8_t receiverPWR;
    uint8_t receiverSIG;
    uint8_t pointsToGive;
    bool isTriggered;
    unsigned long timeOfPressed;
};

/**
 * Creates a struct of the IR Break Beam Sensor for easy-to-reference names and controlling scoring logic
 *
 * @param tGND Transmitter's ground pin
 * @param tPWR Transmitter's power pin
 * @param rGND Receiver's ground pin
 * @param rPWR Receiver's power pin
 * @param rSIG Receiver's signal pin (the white wire)
 * @param pointsToGive How many points this scoring method will give
 * @return IRBreakBeamSensor object to reference each loop, plus storing if the sensor has been tripped and time since
 * tripped
 */
IRBreakBeamSensor initiate(uint8_t tGND, uint8_t tPWR, uint8_t rGND, uint8_t rPWR, uint8_t rSIG, uint8_t pointsToGive);

/**
 * Per loop, checks if the IR Breakbeam sensor has been tripped, giving the player points if so.
 * A delay is added to prevent the sensor from tripping multiple times due to the same ball.
 *
 * @param sensor The sensor struct containing the signal pin to check
 * @return Returns pointsToGive from the sensor struct if the sensor has just been tripped, and 0 otherwise
 */
int scoreCheck(IRBreakBeamSensor sensor);
#endif //PINBALL_MACHINE_IRBREAKBEAMSENSOR_H