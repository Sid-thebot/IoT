// pattern_larsonScanner.h

#ifndef PATTERN_LARSONSCANNER_H
#define PATTERN_LARSONSCANNER_H

#include <Adafruit_NeoPixel.h>

void larsonScanner(Adafruit_NeoPixel &strip, uint32_t color, int delayTime) {
  static int pos = 0;
  static int direction = 1;
  static uint32_t lastUpdate = 0;

  if (millis() - lastUpdate < delayTime) return;
  lastUpdate = millis();

  strip.clear();

  // Set the main dot
  strip.setPixelColor(pos, color);

  // Fade trail (just one pixel behind in each direction for simplicity)
  if (pos - 1 >= 0) {
    strip.setPixelColor(pos - 1, strip.Color(64, 0, 0));
  }
  if (pos + 1 < strip.numPixels()) {
    strip.setPixelColor(pos + 1, strip.Color(64, 0, 0));
  }

  strip.show();

  pos += direction;
  if (pos <= 0 || pos >= strip.numPixels() - 1) {
    direction *= -1;
  }
}

#endif
