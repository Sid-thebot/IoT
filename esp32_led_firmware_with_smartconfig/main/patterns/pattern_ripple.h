// pattern_ripple.h

#ifndef PATTERN_RIPPLE_H
#define PATTERN_RIPPLE_H

#include <Adafruit_NeoPixel.h>

void rippleEffect(Adafruit_NeoPixel &strip, int speedDelay) {
  static int center = 0;
  static int step = -1;
  static uint32_t color = strip.Color(0, 0, 255);
  int numPixels = strip.numPixels();

  if (step == -1) {
    center = random(numPixels);
    color = strip.Color(random(256), random(256), random(256));
    step = 0;
  }

  strip.clear();

  for (int i = 0; i < numPixels; i++) {
    int distance = abs(i - center);
    if (distance == step)
      strip.setPixelColor(i, color);
  }

  strip.show();
  delay(speedDelay);

  step++;
  if (step > numPixels) {
    step = -1;
  }
}

#endif
