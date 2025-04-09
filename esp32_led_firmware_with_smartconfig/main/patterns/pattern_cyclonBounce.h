// pattern_cyclonBounce.h

#ifndef PATTERN_CYCLON_BOUNCE_H
#define PATTERN_CYCLON_BOUNCE_H

#include <Adafruit_NeoPixel.h>

void cyclonBounce(Adafruit_NeoPixel &strip, int eyeSize = 4, int speedDelay = 30, int returnDelay = 50) {
  int i;
  for (i = 0; i < strip.numPixels() - eyeSize - 2; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    for (int j = 1; j <= eyeSize; j++) {
      strip.setPixelColor(i + j, strip.Color(255, 0, 0));
    }
    strip.setPixelColor(i + eyeSize + 1, strip.Color(255, 0, 0));
    strip.show();
    delay(speedDelay);
  }

  delay(returnDelay);

  for (i = strip.numPixels() - eyeSize - 2; i > 0; i--) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    for (int j = 1; j <= eyeSize; j++) {
      strip.setPixelColor(i + j, strip.Color(255, 0, 0));
    }
    strip.setPixelColor(i + eyeSize + 1, strip.Color(255, 0, 0));
    strip.show();
    delay(speedDelay);
  }

  delay(returnDelay);
}

#endif
// pattern_cyclonBounce.h

void pattern_cyclonBounce(Adafruit_NeoPixel &strip) {
  // Effect code here
}
