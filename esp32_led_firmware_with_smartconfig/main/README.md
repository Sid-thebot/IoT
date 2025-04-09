# 🌈 ESP32 LED Pattern Web Controller

This project allows you to control 30 LED animation effects (plus OFF and live color control) from any device via a web dashboard. It uses **ESP32**, **Adafruit NeoPixel**, and **SmartConfig** WiFi setup.

---

## ✨ Features

- 🔌 **SmartConfig** (configure WiFi via mobile)
- 🌐 **Web Dashboard** to select patterns
- 🎨 **Live Hue Slider** for user-defined color
- 🔁 **30+ LED Patterns** (fire, ripple, rainbow, twinkle, etc.)
- 🚫 **OFF Button** to shut down LEDs
- 📱 Mobile-friendly interface

---

## 🧰 Hardware Required

- 1 × **ESP32** development board  
- 1 × **WS2812B / WS2811** 5V LED ring/strip  
- Optional: Capacitor (1000μF 6.3V+) and resistor (300–500Ω)  
- External 5V Power supply (if using >10 LEDs)

---

## 📂 Folder Structure
esp32_led_pattern_firmware/
├── main.ino                  ← Main program file
├── smartconfig.h             ← SmartConfig logic
├── webpage.h                 ← Web UI HTML code
└── patterns/
    ├── pattern_fire.h
    ├── pattern_rainbow.h
    ├── ...
    └── pattern_userColor.h


---

## 🚀 How to Upload

1. **Install Required Libraries:**
   - `Adafruit NeoPixel`
   - `ESPAsyncWebServer`
   - `AsyncTCP`
   - `FastLED`

2. **Open `main.ino`** in Arduino IDE or PlatformIO

3. **Put all `.h` files** in the same `src/` or `main/` folder (Arduino requires this)

4. **Connect your ESP32**, select correct board and port.

5. **Upload the sketch.**

---

## 📱 How to Use

1. On first boot, ESP32 enters **SmartConfig** mode.
2. Use the **ESP Touch app** or similar to send your WiFi credentials.
3. ESP32 connects and shows up on your network.
4. Visit its IP in a browser (use Serial Monitor to find IP).
5. Select patterns, toggle OFF, or control color via the slider.

---

## 📷 Preview

![Preview](https://i.imgur.com/O71c3aG.png)  
(Replace with your actual dashboard screenshot)

---

## 🧠 Notes

- Pattern `0` = OFF  
- Pattern `30` = User Color (hue-controlled)  
- Pattern change happens instantly on click  
- Hue slider sends values to `/color` endpoint live

---

## 📄 License

MIT License  
Created by **Sidthebot28 (aka Siddhant Shaw)** ❤️ 
Created by ❤️ with help from ChatGPT and open-source libraries.
