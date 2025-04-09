// pattern_noiseFlow.h

#ifndef PATTERN_NOISEFLOW_H
#define PATTERN_NOISEFLOW_H

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>  // FastLED used for noise generation

#define NOISE_SCALE 30

void noiseFlow(Adafruit_NeoPixel &strip) {
  static uint16_t x = random16();
  static uint16_t y = random16();
  static uint16_t z = random16();
  static uint16_t speed = 1;
  static uint8_t hue = 0;

  for (int i = 0; i < strip.numPixels(); i++) {
    uint8_t noise = inoise8(x + i * NOISE_SCALE, y, z);
    uint8_t colorIndex = (noise + hue) % 255;
    CRGB color = CHSV(colorIndex, 255, 255);

    strip.setPixelColor(i, strip.Color(color.r, color.g, color.b));
  }

  z += speed;
  hue++;
  strip.show();
  delay(20);
}

#endif
