
const int bumperSensor = 2;
const int bumperLED = 8;

// Demonstration timing only
const unsigned long activeTime = 100;
const unsigned long cooldownTime = 500;

unsigned long startTime = 0;

bool bumperActive = false;
bool cooldown = false;

void setup() {
  pinMode(bumperSensor, INPUT_PULLUP);
  pinMode(bumperLED, OUTPUT);

  digitalWrite(bumperLED, LOW);

  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  // Detect ball collision
  if (digitalRead(bumperSensor) == LOW &&
      !bumperActive && !cooldown) {

    bumperActive = true;
    startTime = currentTime;

    digitalWrite(bumperLED, HIGH);
    Serial.println("Bumper triggered!");
  }

  // End simulated activation
  if (bumperActive &&
      currentTime - startTime >= activeTime) {

    bumperActive = false;
    cooldown = true;
    startTime = currentTime;

    digitalWrite(bumperLED, LOW);
    Serial.println("Bumper off");
  }

  // Finish cooldown
  if (cooldown &&
      currentTime - startTime >= cooldownTime) {

    cooldown = false;
    Serial.println("Bumper ready");
  }
}
