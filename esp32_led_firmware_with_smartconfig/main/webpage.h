const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>LED Pattern Selector</title>
  <style>
    :root {
      --bg: linear-gradient(135deg, #0f2027, #203a43, #2c5364);
      --card-bg: rgba(255, 255, 255, 0.05);
      --btn-bg: rgba(0, 255, 255, 0.1);
      --btn-hover-bg: #0ff;
      --btn-color: #0ff;
      --btn-hover-color: #000;
      --off-bg: #d00000;
      --off-hover: #ff4e4e;
      --font: 'Segoe UI', sans-serif;
    }

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      min-height: 100vh;
      font-family: var(--font);
      background: var(--bg);
      color: var(--btn-color);
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 30px 15px;
    }

    h2 {
      margin-bottom: 20px;
      font-size: 2rem;
      text-shadow: 0 0 8px #0ff;
    }

    .off-button {
      background-color: var(--off-bg);
      color: #fff;
      font-weight: bold;
      padding: 16px 24px;
      border: none;
      border-radius: 12px;
      cursor: pointer;
      margin-bottom: 30px;
      transition: background 0.3s ease;
      font-size: 16px;
      width: 100%;
      max-width: 1000px;
    }

    .off-button:hover {
      background-color: var(--off-hover);
    }

    .grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(140px, 1fr));
      gap: 16px;
      width: 100%;
      max-width: 1000px;
      margin-bottom: 40px;
    }

    button.pattern {
      background: var(--btn-bg);
      color: var(--btn-color);
      border: 1px solid rgba(0,255,255,0.2);
      border-radius: 12px;
      padding: 12px;
      font-size: 14px;
      cursor: pointer;
      backdrop-filter: blur(5px);
      transition: 0.3s ease;
    }

    button.pattern:hover {
      background: var(--btn-hover-bg);
      color: var(--btn-hover-color);
      transform: scale(1.05);
    }

    .slider-container {
      background: var(--card-bg);
      border-radius: 16px;
      padding: 20px;
      width: 100%;
      max-width: 500px;
      text-align: center;
      box-shadow: 0 8px 16px rgba(0, 255, 255, 0.1);
    }

    input[type=range] {
      width: 90%;
      margin-top: 10px;
      accent-color: #0ff;
    }

    h3 {
      margin-bottom: 10px;
      font-weight: 500;
    }

    @media(max-width: 480px) {
      h2 {
        font-size: 1.5rem;
      }
      button.pattern, .off-button {
        font-size: 13px;
      }
    }
  </style>
</head>
<body>
  <h2>LED Pattern Selector</h2>
  <button class="off-button" onclick="setPattern(0)">OFF</button>

  <div class="grid" id="buttons"></div>

  <div class="slider-container">
    <h3>User Color: Hue Control</h3>
    <input type="range" min="0" max="360" value="0" oninput="setHue(this.value)">
  </div>

  <script>
    document.addEventListener("DOMContentLoaded", () => {
      const patterns = [
        "Fire", "Breathe", "Ripple", "Wave", "Confetti", "Juggle", "Theater Chase", "Strobe", "Color Wipe",
        "Sparkle Pulse", "Larson Scanner", "Rainbow Chase", "Meteor", "Twinkle", "Double Scanner", "Bouncing Balls",
        "Soft Twinkle", "Color Chase", "Comet", "Cyclon Bounce", "Flicker Spark", "Flash Fade", "Center Expand",
        "Side Wipe", "Matrix Rain", "Noise Flow", "Starburst", "Marching Ants", "Rainbow", "User Color"
      ];

      const buttonsContainer = document.getElementById("buttons");

      patterns.forEach((name, i) => {
        const btn = document.createElement("button");
        btn.textContent = `${i + 1}. ${name}`;
        btn.className = "pattern";
        btn.onclick = () => setPattern(i + 1);
        buttonsContainer.appendChild(btn);
      });
    });

    function setPattern(id) {
      fetch("/pattern", {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: "id=" + id
      });
    }

    function setHue(val) {
      fetch("/color", {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: "hue=" + val
      });
    }
  </script>
</body>
</html>
)rawliteral";
