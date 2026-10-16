
#include "pitches.h"

const int buzzerPin = 8;

// =====================================
// MUSIC SETTINGS
// =====================================

// 1.5 = 50% longer notes (slower music)
const float musicSpeed = 1.2;

// Wait 1 second after an event
const unsigned long musicResumeDelay = 1000;

// =====================================
// BACKGROUND MUSIC
// =====================================

const int melody[] = {
  NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,

  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C6, NOTE_C6,
  NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,
  NOTE_C6
};

const int durations[] = {
  8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,

  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 16,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 8, 8, 8, 8,

  8, 16, 2, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 4, 8, 4, 8, 4, 8,
  1
};

// =====================================
// FIVE PINBALL SOUND EFFECTS
// =====================================

// 1. Game Start
const int startNotes[] = {523, 659, 784, 1047};
const int startDurations[] = {180, 180, 180, 450};

// 2. Gain Points
const int pointsNotes[] = {1200, 1600, 2000};
const int pointsDurations[] = {100, 100, 170};

// 3. Gain Ball
const int gainBallNotes[] = {659, 784, 988, 1319};
const int gainBallDurations[] = {150, 150, 150, 400};

// 4. Lose Ball
const int loseBallNotes[] = {800, 600, 400};
const int loseBallDurations[] = {230, 230, 400};

// 5. Game Over
const int gameOverNotes[] = {784, 659, 523, 392, 262};
const int gameOverDurations[] = {300, 300, 300, 350, 650};

// =====================================
// SOUND CONTROLLER VARIABLES
// =====================================

enum SoundType {
  NONE,
  START,
  POINTS,
  GAIN_BALL,
  LOSE_BALL,
  GAME_OVER,
  BACKGROUND
};

SoundType currentSound = NONE;

const int* currentNotes = nullptr;
const int* currentDurations = nullptr;

int totalNotes = 0;
int currentNote = 0;

unsigned long previousMillis = 0;
unsigned long noteDuration = 0;

bool soundPlaying = false;
bool gameRunning = false;

// Background music position
int backgroundPosition = 0;

// Pause tracking
unsigned long eventFinishedMillis = 0;
bool waitingToResume = false;

const int melodySize = sizeof(melody) / sizeof(melody[0]);

// =====================================
// SETUP
// =====================================

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  // Automatically start for testing
  gameStartSound();
}

// =====================================
// MAIN LOOP
// =====================================

void loop() {

  updateSound();

  // Test sounds using Serial Monitor
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') gameStartSound();
    if (input == '2') gainPointsSound();
    if (input == '3') gainBallSound();
    if (input == '4') loseBallSound();
    if (input == '5') gameOverSound();
  }

  // Add your sensor and flipper code here
}

// =====================================
// NOTE DURATION
// =====================================

unsigned long getNoteDuration() {

  if (currentSound == BACKGROUND) {

    unsigned long originalDuration =
      1000UL / currentDurations[currentNote];

    return (unsigned long)(originalDuration * 1.3 * musicSpeed);
  }

  return currentDurations[currentNote];
}

// =====================================
// PLAY CURRENT NOTE
// =====================================

void playCurrentNote() {

  previousMillis = millis();
  noteDuration = getNoteDuration();

  int frequency = currentNotes[currentNote];

  if (frequency == REST || frequency == 0) {
    noTone(buzzerPin);
    return;
  }

  if (currentSound == BACKGROUND) {

    unsigned long soundLength =
      (unsigned long)(
        (1000.0 / currentDurations[currentNote]) * musicSpeed
      );

    tone(buzzerPin, frequency, soundLength);

  } else {

    tone(buzzerPin, frequency, noteDuration * 9 / 10);
  }
}

// =====================================
// START A SOUND EFFECT
// =====================================

void playSound(
  SoundType type,
  const int notes[],
  const int noteTimes[],
  int count
) {

  // Cancel any previous resume countdown
  waitingToResume = false;

  // Save background position if interrupted
  if (currentSound == BACKGROUND && soundPlaying) {
    backgroundPosition = currentNote;
  }

  noTone(buzzerPin);

  currentSound = type;
  currentNotes = notes;
  currentDurations = noteTimes;

  totalNotes = count;
  currentNote = 0;

  soundPlaying = true;

  playCurrentNote();
}

// =====================================
// BACKGROUND MUSIC
// =====================================

void backgroundMusic() {

  currentSound = BACKGROUND;
  currentNotes = melody;
  currentDurations = durations;

  totalNotes = melodySize;
  currentNote = backgroundPosition;

  soundPlaying = true;

  playCurrentNote();
}

// =====================================
// UPDATE SOUND USING MILLIS
// =====================================

void updateSound() {

  unsigned long currentMillis = millis();

  // Wait before resuming background music
  if (waitingToResume) {

    if (currentMillis - eventFinishedMillis >= musicResumeDelay) {
      waitingToResume = false;

      if (gameRunning) {
        backgroundMusic();
      }
    }

    return;
  }

  // If nothing is playing, start background music
  if (!soundPlaying) {

    if (gameRunning) {
      backgroundMusic();
    }

    return;
  }

  // Check whether current note has finished
  if (currentMillis - previousMillis >= noteDuration) {

    currentNote++;

    // Entire sound finished
    if (currentNote >= totalNotes) {

      noTone(buzzerPin);
      soundPlaying = false;

      // Start the game after opening sound
      if (currentSound == START) {
        gameRunning = true;
        backgroundPosition = 0;
      }

      // Restart background when song finishes
      if (currentSound == BACKGROUND) {
        backgroundPosition = 0;
        backgroundMusic();
        return;
      }

      // Pause after sound effects
      if (gameRunning) {
        eventFinishedMillis = currentMillis;
        waitingToResume = true;
      }

      return;
    }

    playCurrentNote();
  }
}

// =====================================
// 1. GAME START SOUND
// =====================================

void gameStartSound() {

  gameRunning = false;
  backgroundPosition = 0;

  playSound(
    START,
    startNotes,
    startDurations,
    4
  );
}

// =====================================
// 2. GAIN POINTS SOUND
// =====================================

void gainPointsSound() {

  if (!gameRunning) return;

  playSound(
    POINTS,
    pointsNotes,
    pointsDurations,
    3
  );
}

// =====================================
// 3. GAIN BALL SOUND
// =====================================

void gainBallSound() {

  if (!gameRunning) return;

  playSound(
    GAIN_BALL,
    gainBallNotes,
    gainBallDurations,
    4
  );
}

// =====================================
// 4. LOSE BALL SOUND
// =====================================

void loseBallSound() {

  if (!gameRunning) return;

  playSound(
    LOSE_BALL,
    loseBallNotes,
    loseBallDurations,
    3
  );
}

// =====================================
// 5. GAME OVER SOUND
// =====================================

void gameOverSound() {

  gameRunning = false;
  backgroundPosition = 0;

  playSound(
    GAME_OVER,
    gameOverNotes,
    gameOverDurations,
    5
  );
}
