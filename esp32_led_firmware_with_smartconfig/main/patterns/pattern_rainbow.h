// pattern_rainbow.h

#ifndef PATTERN_RAINBOW_H
#define PATTERN_RAINBOW_H

#include <Adafruit_NeoPixel.h>

void rainbowCycle(Adafruit_NeoPixel &strip, uint8_t wait) {
  static uint16_t j = 0;

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.ColorHSV(((i * 65536L / strip.numPixels()) + j) % 65536));
  }
  strip.show();
  j += 256;
  delay(wait);
}

#endif
