// pattern_softTwinkle.h

#ifndef PATTERN_SOFTTWINKLE_H
#define PATTERN_SOFTTWINKLE_H

#include <Adafruit_NeoPixel.h>

void softTwinkle(Adafruit_NeoPixel &strip) {
  static int twinklePixel = 0;
  static int brightness = 0;
  static bool increasing = true;
  static unsigned long lastUpdate = 0;
  const int twinkleDelay = 20;

  if (millis() - lastUpdate > twinkleDelay) {
    lastUpdate = millis();

    // Fade all pixels slightly
    for (int i = 0; i < strip.numPixels(); i++) {
      uint32_t color = strip.getPixelColor(i);
      uint8_t r = (uint8_t)(color >> 16) & 0xFF;
      uint8_t g = (uint8_t)(color >> 8) & 0xFF;
      uint8_t b = (uint8_t)(color) & 0xFF;

      r = (r > 10) ? r - 10 : 0;
      g = (g > 10) ? g - 10 : 0;
      b = (b > 10) ? b - 10 : 0;

      strip.setPixelColor(i, r, g, b);
    }

    // Update the twinkle pixel
    if (increasing) {
      brightness += 15;
      if (brightness >= 255) {
        brightness = 255;
        increasing = false;
      }
    } else {
      brightness -= 15;
      if (brightness <= 0) {
        brightness = 0;
        increasing = true;
        twinklePixel = random(0, strip.numPixels());
      }
    }

    // Set the current twinkle pixel
    strip.setPixelColor(twinklePixel, strip.Color(brightness, brightness, brightness));
    strip.show();
  }
}

#endif
