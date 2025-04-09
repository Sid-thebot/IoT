#ifndef PATTERN_CONFETTI_H
#define PATTERN_CONFETTI_H

#include <Adafruit_NeoPixel.h>

void confettiEffect(Adafruit_NeoPixel &strip) {
  // Manually fade all pixels (simulate fadeToBlackBy)
  for (int i = 0; i < strip.numPixels(); i++) {
    uint32_t color = strip.getPixelColor(i);
    uint8_t r = (uint8_t)((color >> 16) & 0xFF);
    uint8_t g = (uint8_t)((color >> 8) & 0xFF);
    uint8_t b = (uint8_t)(color & 0xFF);

    // Reduce brightness to simulate fade
    r = (uint8_t)(r * 0.9);
    g = (uint8_t)(g * 0.9);
    b = (uint8_t)(b * 0.9);

    strip.setPixelColor(i, strip.Color(r, g, b));
  }

  // Add a new random pixel
  int pos = random(strip.numPixels());
  int r = random(0, 256);
  int g = random(0, 256);
  int b = random(0, 256);

  strip.setPixelColor(pos, strip.Color(r, g, b));
  strip.show();
  delay(10);
}

#endif  // PATTERN_CONFETTI_H
