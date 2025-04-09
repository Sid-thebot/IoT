// pattern_meteor.h

#ifndef PATTERN_METEOR_H
#define PATTERN_METEOR_H

#include <Adafruit_NeoPixel.h>

void meteorEffect(Adafruit_NeoPixel &strip, uint32_t color, uint8_t meteorSize = 10, bool meteorTrailDecay = true, int speedDelay = 30) {
  static int pos = 0;
  static bool forward = true;
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate < speedDelay) return;
  lastUpdate = millis();

  // fade all LEDs one step
  for (int i = 0; i < strip.numPixels(); i++) {
    if (!meteorTrailDecay || random(10) > 5) {
      uint32_t c = strip.getPixelColor(i);
      uint8_t r = (c >> 16) & 0xFF;
      uint8_t g = (c >> 8) & 0xFF;
      uint8_t b = c & 0xFF;

      r = r <= 10 ? 0 : r - 10;
      g = g <= 10 ? 0 : g - 10;
      b = b <= 10 ? 0 : b - 10;

      strip.setPixelColor(i, r, g, b);
    }
  }

  // draw meteor
  for (int j = 0; j < meteorSize; j++) {
    int pixelIndex = forward ? pos - j : pos + j;
    if (pixelIndex >= 0 && pixelIndex < strip.numPixels()) {
      strip.setPixelColor(pixelIndex, color);
    }
  }

  strip.show();

  if (forward) {
    pos++;
    if (pos - meteorSize > strip.numPixels()) {
      forward = false;
      pos = strip.numPixels() - 1;
    }
  } else {
    pos--;
    if (pos + meteorSize < 0) {
      forward = true;
      pos = 0;
    }
  }
}

#endif
