// pattern_breathe.h

#ifndef PATTERN_BREATHE_H
#define PATTERN_BREATHE_H

#include <Adafruit_NeoPixel.h>

void breathingGlow(Adafruit_NeoPixel &strip, uint32_t color, int breatheSpeed) {
  static int brightness = 0;
  static int delta = 5;

  brightness += delta;
  if (brightness <= 0 || brightness >= 255) {
    delta = -delta;
    brightness += delta;
  }

  uint8_t r = (uint8_t)((color >> 16) & 0xFF);
  uint8_t g = (uint8_t)((color >> 8) & 0xFF);
  uint8_t b = (uint8_t)(color & 0xFF);

  uint8_t br = (brightness * r) / 255;
  uint8_t bg = (brightness * g) / 255;
  uint8_t bb = (brightness * b) / 255;

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(br, bg, bb));
  }

  strip.show();
  delay(breatheSpeed);
}

#endif
