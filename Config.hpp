#pragma once
/*
 * All pins are temporary and are subject to change.
 */
const uint8_t DOORSHES_RECEIVER_PIN = 2;
const uint8_t SCORINGHOLEIRBBS_RECEIVER_PIN = 3;
const uint8_t SPIRALRAMPIRBBS_RECEIVER_PIN = 4;
const uint8_t LOSING_SENSOR_RECEIVER_PIN = 5;
const uint8_t LEFT_BUTTON = 6;
const uint8_t RIGHT_BUTTON = 7;
const uint8_t LEFT_FLIPPER = 8;
const uint8_t RIGHT_FLIPPER = 9;
const uint8_t PLAY_BUTTON = 10;
const uint8_t LED_DATA_PIN = 11;
const uint8_t RELEASE_SERVO_OUT = 12;
const uint8_t LED1 = 13;
const uint8_t LED2 = 14;
const uint8_t LED3 = 15;
const uint8_t LED4 = 16;
const uint8_t BUZZER_PIN = 17;



// Maximum activation time to help protect the solenoids
const unsigned long MAX_FLIPPER_TIME = 50;

// "Debounce" or cooldown for sensor trips
constexpr unsigned long DEBOUNCE_MS = 1000;

// Minimum time to hold the play button down during gameplay to reset game
const unsigned long MIN_RESET_TIME = 3000;

// When game stops through initial start-up, forced reset, or loss
const unsigned long COOLDOWN_TIME = 5000;

// # of leds of our strip; could be 60 or 120 leds total (since we have 2 strips that can connect)
const int NUM_LEDS = 60;

// # of balls our game can hold - going down to 3 instead of 5
const uint8_t MAX_BALLS = 3;