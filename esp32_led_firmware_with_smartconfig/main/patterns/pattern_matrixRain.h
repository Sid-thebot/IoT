// pattern_matrixRain.h

#ifndef PATTERN_MATRIX_RAIN_H
#define PATTERN_MATRIX_RAIN_H

#include <Adafruit_NeoPixel.h>

void matrixRain(Adafruit_NeoPixel &strip, uint8_t speed = 50) {
  static uint32_t lastUpdate = 0;
  static uint8_t rain[256];  // max number of LEDs (adjust size if needed)

  if (millis() - lastUpdate < speed) return;
  lastUpdate = millis();

  for (int i = 0; i < strip.numPixels(); i++) {
    uint8_t value = rain[i];
    if (value > 0) {
      value = value > 25 ? value - 25 : 0;
    } else if (random(0, 50) == 0) {
      value = 255;
    }
    rain[i] = value;
    strip.setPixelColor(i, strip.Color(0, value, 0));
  }

  strip.show();
}

#endif
