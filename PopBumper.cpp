
const int BUMPER_SENSOR = 2;
const int SOLENOID_CONTROL = 8;

// Keep true until the hardware is verified.
const bool SIMULATION_MODE = true;

//change it to this if using the led
//const bool SIMULATION_MODE = false; 

// Example timing values for software testing.
// These are NOT validated for the HS-1564B.
const unsigned long PULSE_MS = 50;
const unsigned long COOLDOWN_MS = 1000;

// Independent software timeout
const unsigned long MAX_ON_MS = 100;

enum BumperState {
  READY,
  FIRING,
  COOLDOWN
};

BumperState bumperState = READY;

unsigned long stateStartTime = 0;
unsigned long activationStartTime = 0;

bool previousSensorPressed = false;

void setBumperOutput(bool enabled) {
  if (SIMULATION_MODE) {
    // Output is disabled in simulation mode.
    digitalWrite(SOLENOID_CONTROL, LOW);
    return;
  }

  digitalWrite(SOLENOID_CONTROL,
               enabled ? HIGH : LOW);
}

void setup() {
  pinMode(BUMPER_SENSOR, INPUT_PULLUP);
  pinMode(SOLENOID_CONTROL, OUTPUT);

  setBumperOutput(false);

  Serial.begin(9600);
  Serial.println("Pop bumper ready");
}

void loop() {
  unsigned long now = millis();

  bool sensorPressed =
    digitalRead(BUMPER_SENSOR) == LOW;

  bool newHit =
    sensorPressed && !previousSensorPressed;

  previousSensorPressed = sensorPressed;

  // Safety timeout
  if (bumperState == FIRING &&
      now - activationStartTime >= MAX_ON_MS) {

    setBumperOutput(false);

    bumperState = COOLDOWN;
    stateStartTime = now;

    Serial.println("Safety timeout / bumper off");
  }

  switch (bumperState) {

    case READY:
      if (newHit) {
        bumperState = FIRING;
        stateStartTime = now;
        activationStartTime = now;

        setBumperOutput(true);

        Serial.println("BUMPER HIT!");
      }
      break;

    case FIRING:
      if (now - stateStartTime >= PULSE_MS) {
        setBumperOutput(false);

        bumperState = COOLDOWN;
        stateStartTime = now;

        Serial.println("Bumper deactivated");
      }
      break;

    case COOLDOWN:
      if (now - stateStartTime >= COOLDOWN_MS) {
        bumperState = READY;
        Serial.println("Bumper ready again");
      }
      break;
  }
}
