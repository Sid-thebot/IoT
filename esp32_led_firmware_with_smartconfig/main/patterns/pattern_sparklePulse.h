#ifndef PATTERN_SPARKLEPULSE_H
#define PATTERN_SPARKLEPULSE_H

#include <Adafruit_NeoPixel.h>

void sparklePulse(Adafruit_NeoPixel &strip) {
  static unsigned long lastUpdate = 0;
  static uint8_t pulse = 0;
  static int8_t direction = 1;
  static unsigned long sparkleTime = 0;
  static int sparklePixel = random(strip.numPixels());

  unsigned long now = millis();

  if (now - lastUpdate > 20) {
    lastUpdate = now;

    // Smoothly pulse the background
    pulse += direction * 5;
    if (pulse >= 150 || pulse <= 10) {
      direction *= -1;
    }

    for (int i = 0; i < strip.numPixels(); i++) {
      if (i == sparklePixel) {
        strip.setPixelColor(i, strip.Color(255, 255, 255)); // Sparkle white
      } else {
        strip.setPixelColor(i, strip.Color(pulse, pulse, pulse));
      }
    }

    strip.show();
  }

  // Change sparkle pixel every 150ms
  if (now - sparkleTime > 150) {
    sparkleTime = now;
    sparklePixel = random(strip.numPixels());
  }
}

#endif  // PATTERN_SPARKLEPULSE_H
