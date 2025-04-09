#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#include "smartconfig.h"
#include "webpage.h"

// Include pattern headers
#include "patterns/pattern_rainbow.h"
#include "patterns/pattern_fire.h"
#include "patterns/pattern_breathe.h"
#include "patterns/pattern_ripple.h"
#include "patterns/pattern_wave.h"
#include "patterns/pattern_confetti.h"
#include "patterns/pattern_juggle.h"
#include "patterns/pattern_theaterChase.h"
#include "patterns/pattern_strobe.h"
#include "patterns/pattern_colorWipe.h"
#include "patterns/pattern_sparklePulse.h"
#include "patterns/pattern_larsonScanner.h"
#include "patterns/pattern_rainbowChase.h"
#include "patterns/pattern_meteor.h"
#include "patterns/pattern_twinkle.h"
#include "patterns/pattern_scannerDouble.h"
#include "patterns/pattern_bouncingBalls.h"
#include "patterns/pattern_softTwinkle.h"
#include "patterns/pattern_colorChase.h"
#include "patterns/pattern_comet.h"
#include "patterns/pattern_cyclonBounce.h"
#include "patterns/pattern_flickerSpark.h"
#include "patterns/pattern_flashFade.h"
#include "patterns/pattern_centerExpand.h"
#include "patterns/pattern_sideWipe.h"
#include "patterns/pattern_matrixRain.h"
#include "patterns/pattern_noiseFlow.h"
#include "patterns/pattern_starburst.h"
#include "patterns/pattern_marchingAnts.h"
#include "patterns/pattern_userColor.h"

#define LED_PIN    4
#define LED_COUNT  16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
AsyncWebServer server(80);

int currentPattern = 0;
int nextPattern = -1;
int userHue = 0;
bool hueSetByUser = false;
unsigned long lastHueChange = 0;

uint32_t hueToRGB(int hue) {
  float s = 1.0, v = 1.0;
  float c = v * s;
  float x = c * (1 - abs(fmod(hue / 60.0, 2) - 1));
  float m = v - c;

  float r, g, b;
  if (hue < 60)      { r = c; g = x; b = 0; }
  else if (hue < 120){ r = x; g = c; b = 0; }
  else if (hue < 180){ r = 0; g = c; b = x; }
  else if (hue < 240){ r = 0; g = x; b = c; }
  else if (hue < 300){ r = x; g = 0; b = c; }
  else               { r = c; g = 0; b = x; }

  return strip.Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();

  startSmartConfig();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/pattern", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("id", true)) {
      nextPattern = request->getParam("id", true)->value().toInt();
      Serial.print("Pattern selected: ");
      Serial.println(nextPattern);
    }
    request->send(200, "text/plain", "OK");
  });

  server.on("/color", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("hue", true)) {
      userHue = request->getParam("hue", true)->value().toInt();
      hueSetByUser = true;
      Serial.print("User hue set to: ");
      Serial.println(userHue);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  // Switch pattern if needed
  static int lastPattern = -1;
  if (nextPattern != -1 && nextPattern != currentPattern) {
    currentPattern = nextPattern;
    nextPattern = -1;
    strip.clear();
    strip.show();
  }

  switch (currentPattern) {
    case 0: strip.clear(); strip.show(); break; // OFF
    case 1: fireFlicker(strip, 55, 120, 15); break;
    case 2: breathingGlow(strip, strip.Color(0, 150, 255), 10); break;
    case 3: rippleEffect(strip, 20); break;
    case 4: waveEffect(strip); break;
    case 5: confettiEffect(strip); break;
    case 6: juggleEffect(strip); break;
    case 7: theaterChase(strip, strip.Color(127, 127, 127), 50); break;
    case 8: strobeEffect(strip, 0xFFFFFF, 50, 3, 200); break;
    case 9: colorWipe(strip, strip.Color(255, 0, 0), 30); break;
    case 10: sparklePulse(strip); break;
    case 11: larsonScanner(strip, strip.Color(255, 0, 0), 20); break;
    case 12: rainbowChase(strip, 30); break;
    case 13: meteorEffect(strip, strip.Color(255, 255, 255), 10, true, 30); break;
    case 14: twinkleEffect(strip); break;
    case 15: doubleScanner(strip, strip.Color(0, 255, 0), 30); break;
    case 16: bouncingBalls(strip); break;
    case 17: softTwinkle(strip); break;
    case 18: colorChase(strip, strip.Color(0, 0, 255), 30); break;
    case 19: comet(strip, strip.Color(255, 100, 0), 20); break;
    case 20: cyclonBounce(strip); break;
    case 21: flickerSpark(strip); break;
    case 22: flashFade(strip); break;
    case 23: centerExpand(strip); break;
    case 24: sideWipe(strip); break;
    case 25: matrixRain(strip); break;
    case 26: noiseFlow(strip); break;
    case 27: starburst(strip); break;
    case 28: marchingAnts(strip); break;
    case 29: rainbowCycle(strip, 10); break;
    case 30: userColorPattern(strip, hueToRGB(userHue), 50); break;
    default: strip.clear(); strip.show(); break;
  }

  // Auto cycle hue if not user-controlled
  if (!hueSetByUser && millis() - lastHueChange > 30) {
    userHue = (userHue + 1) % 360;
    lastHueChange = millis();
  }

  delay(20);
}
