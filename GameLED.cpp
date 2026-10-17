#pragma once

#include "GameLED.hpp"
#include <math.h>


GameLED gameLEDInitiate() {
  GameLED ret = { LED_DATA_PIN, new CRGB[NUM_LEDS], -1, -1 };
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(ret.led, NUM_LEDS);
  FastLED.setBrightness(90);
  FastLED.clear();
  FastLED.show();
  return ret;
}

void bootup(GameLED &led, unsigned long startTime) {
  if (led.priority >= 3) {
    led.priority = 3;
    led.startAnimationTime = startTime;
    return;
  }
  unsigned long elapsed = millis() - startTime;
  if (elapsed > 7000) {
    led.priority = -1;
    FastLED.clear();
    FastLED.show();
    return;
  }
  int ledsLit = min(elapsed / 7000 * NUM_LEDS, NUM_LEDS);
  for (int i = 0; i < ledsLit; i++) {
    led.led[i] = CRGB::White;
  }
  FastLED.show();
}

void loseGame(GameLED &led, unsigned long startTime) {
  if (led.priority >= 0) {
    led.priority = 0;
    led.startAnimationTime = startTime;
    return;
  }
  unsigned long elapsed = millis() - startTime;
  if (elapsed > 5000) {
    led.priority = -1;
    FastLED.clear();
    FastLED.show();
    return;
  }
  if (elapsed % 400 < 200) {
    fill_solid(
        led.led, NUM_LEDS, CRGB::Red
    );
  } else {
    fill_solid(
        led.led, NUM_LEDS, CRGB::Red
    );
  }
  FastLED.show();
}

void scorePoint(GameLED &led, unsigned long startTime) {
  if (led.priority >= 2) {
    led.priority = 2;
    led.startAnimationTime = startTime;
    return;
  }
  unsigned long elapsed = millis() - startTime;
  if (elapsed > 1000) {
    led.priority = -1;
    FastLED.clear();
    FastLED.show();
    return;
  }
  if (elapsed < 750) {
    fill_solid(
        led.led, NUM_LEDS, CRGB(0,min((elapsed/750)*255,255),0)
    );
  } else {
    fill_solid(
        led.led, NUM_LEDS, CRGB(0,max(255-((elapsed-750)/250),0),0)
    );
  }
  FastLED.show();
}

void loseBall(GameLED &led, unsigned long startTime) {
  if (led.priority >= 1) {
    led.priority = 1;
    led.startAnimationTime = startTime;
    return;
  }
  unsigned long elapsed = millis() - startTime;
  if (elapsed > 3500) {
    led.priority = -1;
    FastLED.clear();
    FastLED.show();
    return;
  }
  if (elapsed < 1500) {
    fill_solid(
        led.led, NUM_LEDS, CRGB(min((elapsed/1500)*255,255),0,0)
    );
  } else {
    fill_solid(
        led.led, NUM_LEDS, CRGB(max(255-((elapsed-1500)/2000),0),0,0)
    );
  }
  FastLED.show();
}

void displayPriorityAnimation(GameLED &led) {
  unsigned long startTime = millis();
  switch (led.priority) {
    case 0:
      return loseGame(led, startTime);
    case 1:
      return loseBall(led, startTime);
    case 2:
      return scorePoint(led, startTime);
    case 3:
      return bootup(led, startTime);
    default:
      fill_solid(led.led, NUM_LEDS, CRGB::Black);
      FastLED.show();
  }
}