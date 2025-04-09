// pattern_colorChase.h

#ifndef PATTERN_COLOR_CHASE_H
#define PATTERN_COLOR_CHASE_H

#include <Adafruit_NeoPixel.h>

void colorChase(Adafruit_NeoPixel &strip, uint32_t color, int wait) {
  static int index = 0;

  strip.clear();
  strip.setPixelColor(index, color);
  strip.show();

  index++;
  if (index >= strip.numPixels()) {
    index = 0;
  }

  delay(wait);
}

#endif
