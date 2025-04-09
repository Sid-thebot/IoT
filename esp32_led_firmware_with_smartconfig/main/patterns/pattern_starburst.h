// pattern_starburst.h

#ifndef PATTERN_STARBURST_H
#define PATTERN_STARBURST_H

#include <Adafruit_NeoPixel.h>

void starburst(Adafruit_NeoPixel &strip) {
  static unsigned long lastUpdate = 0;
  static int center = strip.numPixels() / 2;
  static int offset = 0;
  static int direction = 1;

  unsigned long now = millis();

  if (now - lastUpdate > 50) {
    lastUpdate = now;
    strip.clear();

    int left = center - offset;
    int right = center + offset;

    if (left >= 0) {
      strip.setPixelColor(left, strip.Color(255, 255, 0)); // Yellow burst
    }
    if (right < strip.numPixels()) {
      strip.setPixelColor(right, strip.Color(255, 255, 0));
    }

    strip.show();

    offset += direction;
    if (left <= 0 && direction == -1) {
      offset = 0;
      direction = 1;
    } else if (right >= strip.numPixels() - 1 && direction == 1) {
      direction = -1;
    }
  }
}

#endif
