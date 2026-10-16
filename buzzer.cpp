
const int buzzerPin = 8;

const int startNotes[] = {523, 659, 784, 1047};
const int startDurations[] = {180, 180, 180, 450};

const int pointsNotes[] = {1200, 1600, 2000};
const int pointsDurations[] = {100, 100, 170};

const int gainBallNotes[] = {659, 784, 988, 1319};
const int gainBallDurations[] = {150, 150, 150, 400};

const int loseBallNotes[] = {800, 600, 400};
const int loseBallDurations[] = {230, 230, 400};

const int gameOverNotes[] = {784, 659, 523, 392, 262};
const int gameOverDurations[] = {300, 300, 300, 350, 650};

// Current sound information
const int* currentNotes = nullptr;
const int* currentDurations = nullptr;

int totalNotes = 0;
int currentNote = 0;

unsigned long previousMillis = 0;
bool soundPlaying = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Update the buzzer
  updateSound();

  // Test sounds using Serial Monitor, type the number
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') {
      gameStartSound();
    }

    if (input == '2') {
      gainPointsSound();
    }

    if (input == '3') {
      gainBallSound();
    }

    if (input == '4') {
      loseBallSound();
    }

    if (input == '5') {
      gameOverSound();
    }
  }

  // Add sensor and flipper code 
}

// Starts playing a sound
void playSound(const int notes[],
               const int durations[],
               int count) {

  noTone(buzzerPin);

  currentNotes = notes;
  currentDurations = durations;
  totalNotes = count;
  currentNote = 0;

  soundPlaying = true;
  previousMillis = millis();

  tone(buzzerPin, currentNotes[0],
       currentDurations[0] * 9 / 10);
}

// Updates sound without delay()
void updateSound() {

  if (!soundPlaying) {
    return;
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >=
      (unsigned long)currentDurations[currentNote]) {

    currentNote++;

    if (currentNote >= totalNotes) {
      noTone(buzzerPin);
      soundPlaying = false;
      return;
    }

    previousMillis = currentMillis;

    tone(buzzerPin, currentNotes[currentNote],
         currentDurations[currentNote] * 9 / 10);
  }
}

// 1. GAME START
void gameStartSound() {
  playSound(startNotes, startDurations, 4);
}

// 2. GAIN POINTS
void gainPointsSound() {
  playSound(pointsNotes, pointsDurations, 3);
}

// 3. GAIN BALL
void gainBallSound() {
  playSound(gainBallNotes, gainBallDurations, 4);
}

// 4. LOSE BALL
void loseBallSound() {
  playSound(loseBallNotes, loseBallDurations, 3);
}

// 5. GAME OVER
void gameOverSound() {
  playSound(gameOverNotes, gameOverDurations, 5);
}
