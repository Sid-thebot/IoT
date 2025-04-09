// pattern_comet.h

#ifndef PATTERN_COMET_H
#define PATTERN_COMET_H

#include <Adafruit_NeoPixel.h>

void comet(Adafruit_NeoPixel &strip, uint32_t color, int speed) {
  static int cometPos = 0;
  static int direction = 1;

  strip.clear();

  // Draw comet with fading tail
  for (int i = 0; i < 5; i++) {
    int pos = cometPos - i * direction;
    if (pos >= 0 && pos < strip.numPixels()) {
      int fade = 255 - (i * 50);  // Tail fade
      uint32_t fadedColor = strip.Color(
        (uint8_t)(color >> 16) * fade / 255,
        (uint8_t)(color >> 8 & 0xFF) * fade / 255,
        (uint8_t)(color & 0xFF) * fade / 255
      );
      strip.setPixelColor(pos, fadedColor);
    }
  }

  strip.show();
  delay(speed);

  cometPos += direction;
  if (cometPos <= 0 || cometPos >= strip.numPixels() - 1) {
    direction *= -1;  // Bounce
  }
}

#endif
