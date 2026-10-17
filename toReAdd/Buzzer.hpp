#pragma once

#include "../pitches.h"
#include <Arduino.h>
#include <stdint.h>

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

unsigned long getNoteDuration();

void playCurrentNote();

void playSound(
  SoundType type,
  const int notes[],
  const int noteTimes[],
  int count
);

void backgroundMusic();

void updateSound();

void gameStartSound();

void gainPointsSound();

void gainBallSound();

void loseBallSound();

void gameOverSound();