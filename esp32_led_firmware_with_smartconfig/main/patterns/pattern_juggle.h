// pattern_juggle.h

#ifndef PATTERN_JUGGLE_H
#define PATTERN_JUGGLE_H

#include <Adafruit_NeoPixel.h>

void juggleEffect(Adafruit_NeoPixel &strip, int balls = 4, uint8_t fadeAmount = 20) {
  static float pos[4] = {0};
  static float speed[4] = {0.9, 0.7, 0.5, 0.3};
  static uint32_t lastUpdate = 0;

  if (millis() - lastUpdate < 20) return;
  lastUpdate = millis();

  // Fade all LEDs
  for (int i = 0; i < strip.numPixels(); i++) {
    uint32_t color = strip.getPixelColor(i);
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    r = (r <= fadeAmount) ? 0 : r - fadeAmount;
    g = (g <= fadeAmount) ? 0 : g - fadeAmount;
    b = (b <= fadeAmount) ? 0 : b - fadeAmount;
    strip.setPixelColor(i, r, g, b);
  }

  // Draw the balls
  for (int i = 0; i < balls; i++) {
    int posIndex = (int)(sin(millis() * 0.001 * speed[i]) * (strip.numPixels() / 2 - 1) + strip.numPixels() / 2);
    uint32_t color = strip.Color(255 - (i * 60), 0, i * 60);
    strip.setPixelColor(posIndex, color);
  }

  strip.show();
}

#endif
