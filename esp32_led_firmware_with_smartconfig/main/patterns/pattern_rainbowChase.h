// pattern_rainbowChase.h

#ifndef PATTERN_RAINBOWCHASE_H
#define PATTERN_RAINBOWCHASE_H

#include <Adafruit_NeoPixel.h>

void rainbowChase(Adafruit_NeoPixel &strip, int wait) {
  static int startIndex = 0;
  int numPixels = strip.numPixels();

  for (int i = 0; i < numPixels; i++) {
    int hue = (startIndex + i * 256 / numPixels) % 65536;
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue)));
  }

  strip.show();
  startIndex = (startIndex + 256) % 65536;
  delay(wait);
}

#endif
