#ifndef PATTERN_USERCOLOR_H
#define PATTERN_USERCOLOR_H

#include <Adafruit_NeoPixel.h>

void userColorPattern(Adafruit_NeoPixel &strip, uint32_t color, int delayTime = 50) {
  static uint32_t lastColor = 0;
  static bool firstRun = true;

  if (firstRun || lastColor != color) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    lastColor = color;
    firstRun = false;
  }
}
#endif
