// pattern_scannerDouble.h

#ifndef PATTERN_SCANNERDOUBLE_H
#define PATTERN_SCANNERDOUBLE_H

#include <Adafruit_NeoPixel.h>

void doubleScanner(Adafruit_NeoPixel &strip, uint32_t color, int speedDelay) {
  static int position = 0;
  static int direction = 1;
  int numPixels = strip.numPixels();

  strip.clear();
  strip.setPixelColor(position, color);
  strip.setPixelColor(numPixels - 1 - position, color);
  strip.show();
  delay(speedDelay);

  position += direction;
  if (position <= 0 || position >= numPixels - 1) {
    direction *= -1;
  }
}

#endif
