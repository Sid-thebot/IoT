// pattern_theaterChase.h

#ifndef PATTERN_THEATERCHASE_H
#define PATTERN_THEATERCHASE_H

#include <Adafruit_NeoPixel.h>

void theaterChase(Adafruit_NeoPixel &strip, uint32_t color, int wait) {
  static int start = 0;
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate > wait) {
    lastUpdate = now;
    strip.clear();

    for (int i = start; i < strip.numPixels(); i += 3) {
      strip.setPixelColor(i, color);
    }

    strip.show();
    start = (start + 1) % 3;
  }
}

#endif
