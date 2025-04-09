// pattern_sideWipe.h

#ifndef PATTERN_SIDEWIPE_H
#define PATTERN_SIDEWIPE_H

#include <Adafruit_NeoPixel.h>

void sideWipe(Adafruit_NeoPixel &strip) {
  static int pos = 0;
  static bool forward = true;
  int numPixels = strip.numPixels();

  strip.clear();
  if (forward) {
    for (int i = 0; i <= pos; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 255));
    }
    pos++;
    if (pos >= numPixels) {
      forward = false;
      pos = numPixels - 1;
    }
  } else {
    for (int i = numPixels - 1; i >= pos; i--) {
      strip.setPixelColor(i, strip.Color(0, 255, 255));
    }
    pos--;
    if (pos < 0) {
      forward = true;
      pos = 0;
    }
  }

  strip.show();
  delay(50);
}

#endif
