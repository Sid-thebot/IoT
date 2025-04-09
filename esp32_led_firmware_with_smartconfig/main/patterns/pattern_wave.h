// pattern_wave.h

#ifndef PATTERN_WAVE_H
#define PATTERN_WAVE_H

#include <Adafruit_NeoPixel.h>
#include <math.h>

void waveEffect(Adafruit_NeoPixel &strip, int speed = 10) {
  static int pos = 0;
  pos++;
  for (int i = 0; i < strip.numPixels(); i++) {
    float wave = (sin((i + pos) * 0.3) + 1.0) * 127.5; // 0 to 255
    strip.setPixelColor(i, strip.Color(wave, 0, 255 - wave));
  }
  strip.show();
  delay(speed);
}

#endif
