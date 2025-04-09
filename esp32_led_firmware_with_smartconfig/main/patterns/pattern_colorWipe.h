// pattern_colorWipe.h

#ifndef PATTERN_COLOR_WIPE_H
#define PATTERN_COLOR_WIPE_H

#include <Adafruit_NeoPixel.h>

void colorWipe(Adafruit_NeoPixel &strip, uint32_t color, int wait) {
  static int pixelIndex = 0;

  if (pixelIndex < strip.numPixels()) {
    strip.setPixelColor(pixelIndex, color);
    strip.show();
    pixelIndex++;
  } else {
    pixelIndex = 0;
    strip.clear();
  }

  delay(wait);
}

#endif
