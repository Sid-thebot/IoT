#ifndef PATTERN_FLASHFADE_H
#define PATTERN_FLASHFADE_H

#include <Adafruit_NeoPixel.h>

void flashFade(Adafruit_NeoPixel &strip) {
  static unsigned long lastUpdate = 0;
  static int brightness = 0;
  static int direction = 5;  // Fade increment
  static bool flashPhase = true;
  static int flashCounter = 0;

  unsigned long now = millis();

  if (now - lastUpdate > 20) {
    lastUpdate = now;

    if (flashPhase) {
      // Flash to full white
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
      }
      strip.show();
      flashCounter++;

      if (flashCounter > 2) {
        flashPhase = false;
        flashCounter = 0;
        brightness = 255;
        direction = -5;
      }
    } else {
      // Fade out
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
      }
      strip.show();

      brightness += direction;
      if (brightness <= 0) {
        flashPhase = true;  // Go back to flashing
      }
    }
  }
}
#endif
