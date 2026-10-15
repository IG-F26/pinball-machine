#pragma once

// Maximum activation time to help protect the solenoids
const unsigned long MAX_FLIPPER_TIME = 300;

// "Debounce" or cooldown for sensor trips
constexpr unsigned long DEBOUNCE_MS = 1000;

// Minimum time to hold the play button down during gameplay to reset game
const unsigned long MIN_RESET_TIME = 3000;

// When game stops through initial start-up, forced reset, or loss
const unsigned long COOLDOWN_TIME = 5000;