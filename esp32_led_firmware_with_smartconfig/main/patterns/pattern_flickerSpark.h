// pattern_flickerSpark.h

#ifndef PATTERN_FLICKERSPARK_H
#define PATTERN_FLICKERSPARK_H

#include <Adafruit_NeoPixel.h>

void flickerSpark(Adafruit_NeoPixel &strip, int flickerRate = 50) {
  int pixelCount = strip.numPixels();

  // Flicker randomly
  for (int i = 0; i < pixelCount; i++) {
    if (random(0, 100) < flickerRate) {
      uint8_t r = random(150, 255);
      uint8_t g = random(100, 200);
      uint8_t b = random(50, 150);
      strip.setPixelColor(i, strip.Color(r, g, b));
    } else {
      strip.setPixelColor(i, 0); // Turn off pixel
    }
  }

  strip.show();
  delay(50);
}

#endif
