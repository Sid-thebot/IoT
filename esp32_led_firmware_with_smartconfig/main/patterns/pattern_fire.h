#ifndef PATTERN_FIRE_H
#define PATTERN_FIRE_H

#include <Adafruit_NeoPixel.h>

#define COOLING  55
#define SPARKING 120

// ✅ Declare FireHeatColor first
uint32_t FireHeatColor(byte temperature) {
  byte t192 = round((temperature / 255.0) * 191);
  byte heatramp = t192 & 63;  // 0..63
  heatramp <<= 2;             // scale up to 0..252

  if (t192 > 128) {
    return ((uint32_t)255 << 16) | ((uint32_t)255 << 8) | heatramp;
  } else if (t192 > 64) {
    return ((uint32_t)255 << 16) | ((uint32_t)heatramp << 8);
  } else {
    return ((uint32_t)heatramp << 16);
  }
}

void fireFlicker(Adafruit_NeoPixel &strip, uint8_t cooling = COOLING, uint8_t sparking = SPARKING, int speedDelay = 15) {
  static byte heat[128];  // Max 128 LEDs
  int pixelCount = strip.numPixels();
  if (pixelCount > 128) pixelCount = 128;

  for (int i = 0; i < pixelCount; i++) {
    heat[i] = qsub8(heat[i], random(0, ((cooling * 10) / pixelCount) + 2));
  }

  for (int k = pixelCount - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  if (random(255) < sparking) {
    int y = random(7);
    heat[y] = qadd8(heat[y], random(160, 255));
  }

  for (int j = 0; j < pixelCount; j++) {
    strip.setPixelColor(j, FireHeatColor(heat[j]));
  }

  strip.show();
  delay(speedDelay);
}

#endif  // PATTERN_FIRE_H
