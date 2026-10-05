/* References:
 * [https://learn.adafruit.com/ir-breakbeam-sensors/arduino] - Basic IR Breakbeam Sensor Functionality
*/

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
    int transmitterGND;
    int transmitterPWR;
    int receiverGND;
    int receiverPWR;
    int receiverSIG;
    int pointsToGive;
    bool isPressed;
};

IRBreakBeamSensor initiate(int tGND, int tPWR, int rGND, int rPWR, int rSIG, int pointsToGive);

#endif //PINBALL_MACHINE_IRBREAKBEAMSENSOR_H