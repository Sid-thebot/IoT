// pattern_twinkle.h

#ifndef PATTERN_TWINKLE_H
#define PATTERN_TWINKLE_H

#include <Adafruit_NeoPixel.h>

void twinkleEffect(Adafruit_NeoPixel &strip, int chance = 10) {
  for (int i = 0; i < strip.numPixels(); i++) {
    if (random(0, 100) < chance) {
      strip.setPixelColor(i, strip.Color(random(0, 255), random(0, 255), random(0, 255)));
    } else {
      strip.setPixelColor(i, 0);
    }
  }
  strip.show();
  delay(100);
}

#endif
