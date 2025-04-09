// pattern_centerExpand.h

#ifndef PATTERN_CENTEREXPAND_H
#define PATTERN_CENTEREXPAND_H

#include <Adafruit_NeoPixel.h>

void centerExpand(Adafruit_NeoPixel &strip) {
  static int frame = 0;
  static unsigned long lastUpdate = 0;
  const int delayTime = 60;
  int numPixels = strip.numPixels();
  int center = numPixels / 2;

  if (millis() - lastUpdate > delayTime) {
    lastUpdate = millis();

    strip.clear();
    for (int i = 0; i <= frame; i++) {
      if (center + i < numPixels)
        strip.setPixelColor(center + i, strip.Color(0, 255, 255));
      if (center - i >= 0)
        strip.setPixelColor(center - i, strip.Color(0, 255, 255));
    }

    strip.show();

    frame++;
    if (frame > center) {
      frame = 0;
    }
  }
}
#endif
