// pattern_marchingAnts.h

#ifndef PATTERN_MARCHINGANTS_H
#define PATTERN_MARCHINGANTS_H

#include <Adafruit_NeoPixel.h>

void marchingAnts(Adafruit_NeoPixel &strip, uint8_t speed = 100) {
  static uint16_t offset = 0;
  static uint32_t lastUpdate = 0;

  if (millis() - lastUpdate < speed) return;
  lastUpdate = millis();

  offset = (offset + 1) % strip.numPixels();

  for (int i = 0; i < strip.numPixels(); i++) {
    if ((i + offset) % 4 < 2) {
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // white
    } else {
      strip.setPixelColor(i, 0); // off
    }
  }

  strip.show();
}

#endif
