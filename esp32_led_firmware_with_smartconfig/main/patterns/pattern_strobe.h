#ifndef PATTERN_STROBE_H
#define PATTERN_STROBE_H

#include <Adafruit_NeoPixel.h>

void strobeEffect(Adafruit_NeoPixel &strip, uint32_t color = 0xFFFFFF, int flashDelay = 50, int flashCount = 3, int pause = 200) {
  static unsigned long lastUpdate = 0;
  static int state = 0;
  static int flashes = 0;
  static bool on = false;

  unsigned long now = millis();

  switch (state) {
    case 0: // Flashing
      if (now - lastUpdate > flashDelay) {
        lastUpdate = now;
        if (on) {
          strip.clear();
          strip.show();
          on = false;
          flashes++;
        } else {
          for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, color);
          }
          strip.show();
          on = true;
        }
        if (flashes >= flashCount) {
          state = 1;
          flashes = 0;
          lastUpdate = now;
        }
      }
      break;

    case 1: // Pause between flash cycles
      if (now - lastUpdate > pause) {
        state = 0;
        lastUpdate = now;
      }
      break;
  }
}

#endif  // PATTERN_STROBE_H
