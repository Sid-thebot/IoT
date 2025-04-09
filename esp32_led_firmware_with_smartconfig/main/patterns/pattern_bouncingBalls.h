// pattern_bouncingBalls.h

#ifndef PATTERN_BOUNCING_BALLS_H
#define PATTERN_BOUNCING_BALLS_H

#include <Adafruit_NeoPixel.h>

#define GRAVITY -9.81
#define START_HEIGHT 1
#define NUM_BALLS 3
#define SPEED_ADJUST 0.05

float Height[NUM_BALLS];
float ImpactVelocityStart;
float ImpactVelocity[NUM_BALLS];
float TimeSinceLastBounce[NUM_BALLS];
long ClockTimeSinceLastBounce[NUM_BALLS];
float Dampening[NUM_BALLS];
unsigned long lastTime = 0;
bool initialized = false;
uint8_t ballColors[NUM_BALLS][3] = {
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255}
};

void initializeBouncingBalls() {
  ImpactVelocityStart = sqrt(-2 * GRAVITY * START_HEIGHT);
  for (int i = 0; i < NUM_BALLS; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = START_HEIGHT;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(NUM_BALLS, 2);
  }
  initialized = true;
}

void bouncingBalls(Adafruit_NeoPixel &strip) {
  if (!initialized) {
    initializeBouncingBalls();
  }

  unsigned long currentTime = millis();
  strip.clear();

  for (int i = 0; i < NUM_BALLS; i++) {
    TimeSinceLastBounce[i] = (currentTime - ClockTimeSinceLastBounce[i]) / 1000.0;
    Height[i] = 0.5 * GRAVITY * pow(TimeSinceLastBounce[i], 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i];

    if (Height[i] < 0) {
      Height[i] = 0;
      ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
      ClockTimeSinceLastBounce[i] = currentTime;

      if (ImpactVelocity[i] < 0.01) {
        ImpactVelocity[i] = ImpactVelocityStart;
      }
    }

    int position = round(Height[i] * (strip.numPixels() - 1) / START_HEIGHT);
    strip.setPixelColor(position, strip.Color(ballColors[i][0], ballColors[i][1], ballColors[i][2]));
  }

  strip.show();
  delay(20);
}

#endif
