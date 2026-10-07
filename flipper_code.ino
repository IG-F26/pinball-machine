
// Flipper buttons
const int LEFT_BUTTON = 2;
const int RIGHT_BUTTON = 3;

// MOSFET/driver control pins
const int LEFT_FLIPPER = 5;
const int RIGHT_FLIPPER = 6;

// Maximum activation time to help protect the solenoids
const unsigned long MAX_FLIPPER_TIME = 300; // milliseconds

unsigned long leftStartTime = 0;
unsigned long rightStartTime = 0;

bool leftFlipperActive = false;
bool rightFlipperActive = false;


void setup() {

    // Buttons use Arduino's internal pull-up resistors
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);

    // Outputs control the MOSFET/driver
    pinMode(LEFT_FLIPPER, OUTPUT);
    pinMode(RIGHT_FLIPPER, OUTPUT);

    // Make sure flippers start OFF
    digitalWrite(LEFT_FLIPPER, LOW);
    digitalWrite(RIGHT_FLIPPER, LOW);
}


void loop() {

    updateLeftFlipper();
    updateRightFlipper();
}



void updateLeftFlipper() {

    bool buttonPressed = digitalRead(LEFT_BUTTON) == LOW;

    // Button was just pressed
    if (buttonPressed && !leftFlipperActive) {

        digitalWrite(LEFT_FLIPPER, HIGH);

        leftStartTime = millis();

        leftFlipperActive = true;
    }

    // Button released
    if (!buttonPressed) {

        digitalWrite(LEFT_FLIPPER, LOW);

        leftFlipperActive = false;
    }

    // Safety timeout
    if (leftFlipperActive &&
        millis() - leftStartTime >= MAX_FLIPPER_TIME) {

        digitalWrite(LEFT_FLIPPER, LOW);
    }
}



void updateRightFlipper() {

    bool buttonPressed = digitalRead(RIGHT_BUTTON) == LOW;

    // Button was just pressed
    if (buttonPressed && !rightFlipperActive) {

        digitalWrite(RIGHT_FLIPPER, HIGH);

        rightStartTime = millis();

        rightFlipperActive = true;
    }

    // Button released
    if (!buttonPressed) {

        digitalWrite(RIGHT_FLIPPER, LOW);

        rightFlipperActive = false;
    }

    // Safety timeout
    if (rightFlipperActive &&
        millis() - rightStartTime >= MAX_FLIPPER_TIME) {

        digitalWrite(RIGHT_FLIPPER, LOW);
    }
}