#define BLYNK_TEMPLATE_ID "***************"
#define BLYNK_TEMPLATE_NAME "**************"
#define BLYNK_AUTH_TOKEN "***********************************"
#include <DHT.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>    
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h> 

#define sensor1 34
#define DHTPIN 4  
#define DHTTYPE DHT11  
#define ANALOG_PIN A0 
#define FLOW_SENSOR_PIN 19  // Pin for the flow sensor
#define RELAY_PIN 23        // Pin for the relay

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

char ssid[] = "Sid";
char pass[] = "11111111";

volatile int flowPulseCount = 0;
float flowRate = 0.0;
unsigned long oldTime = 0;

AsyncWebServer server(80);

void IRAM_ATTR flowPulseCounter() {
  flowPulseCount++;
}

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  pinMode(sensor1, INPUT);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowPulseCounter, FALLING);
  dht.begin();
  
  // Start the web server
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0, 0); // Set cursor to the first column of the first row
  lcd.print("IP Address:"); // Print IP Address label
  lcd.setCursor(0, 1); // Set cursor to the first column of the second row
  lcd.print(WiFi.localIP()); // Print the actual IP address
  
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<!DOCTYPE html>";
    html += "<html lang='en'>";
    html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>Soil Monitoring System</title>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; margin: 0; padding: 0; }";
    html += ".container { max-width: 800px; margin: 20px auto; padding: 20px; background-color: #fff; border-radius: 10px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }";
    html += "h1 { text-align: center; color: #333; }";
    html += "p { margin: 10px 0; }";
    html += ".sensor-label { color: #007bff; }"; // Color for sensor labels
    html += ".sensor-value { font-weight: bold; }"; // Bold font for sensor values
    html += ".humidity { color: #28a745; }"; // Green color for humidity
    html += ".temperature { color: #dc3545; }"; // Red color for temperature
    html += ".co2 { color: #17a2b8; }"; // Cyan color for CO2 concentration
    html += ".flow { color: #6610f2; }"; // Purple color for flow rate
    html += "</style>";
    html += "<script>";
    html += "function updateData() {";
    html += "var xhttp = new XMLHttpRequest();";
    html += "xhttp.onreadystatechange = function() {";
    html += "if (this.readyState == 4 && this.status == 200) {";
    html += "var data = JSON.parse(this.responseText);";
    html += "document.getElementById('soil-value').innerText = data.soil + '%';";
    html += "document.getElementById('humidity-value').innerText = data.humidity + '%';";
    html += "document.getElementById('temperature-value').innerText = data.temperature + '°C';";
    html += "document.getElementById('co2-value').innerText = data.co2 + ' ppm';";
    html += "document.getElementById('flow-value').innerText = data.flow + ' L/min';";
    html += "}";
    html += "};";
    html += "xhttp.open('GET', '/data', true);";
    html += "xhttp.send();";
    html += "}";
    html += "setInterval(updateData, 2000);"; // Update data every 2 seconds
    html += "</script>";
    html += "</head>";
    html += "<body>";
    html += "<div class='container'>";
    html += "<h1>Soil Monitoring System</h1>";
    html += "<p><span class='sensor-label'>Soil Moisture:</span> <span id='soil-value' class='sensor-value'></span></p>";
    html += "<p class='humidity'><span class='sensor-label'>Humidity:</span> <span id='humidity-value' class='sensor-value'></span></p>";
    html += "<p class='temperature'><span class='sensor-label'>Temperature:</span> <span id='temperature-value' class='sensor-value'></span></p>";
    html += "<p class='co2'><span class='sensor-label'>CO2 Concentration:</span> <span id='co2-value' class='sensor-value'></span></p>";
    html += "<p class='flow'><span class='sensor-label'>Flow Rate:</span> <span id='flow-value' class='sensor-value'></span></p>";
    html += "</div>";
    html += "</body>";
    html += "</html>";
    request->send(200, "text/html", html);
    });

    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(200);
    doc["soil"] = map((100-analogRead(sensor1)), 0, 4095, 0, 100); // Map the soil sensor value to the range of 0 to 100
    doc["humidity"] = dht.readHumidity();
    doc["temperature"] = dht.readTemperature();
    doc["co2"] = readCO2();
    doc["flowRate"] = flowRate;
    serializeJson(doc, *response);
    request->send(response);
  });
  
  server.begin();
}
void soilMoisture() {
  int value1 = analogRead(sensor1);
  value1 = map(value1, 0, 4095, 0, 100);

  Blynk.virtualWrite(V0, (100 - value1));
  Serial.print("Soil Percentage = ");
  Serial.print(value1);
  Serial.println("");

  // Control the relay based on soil moisture level
  if (value1 < 30) {  // Example threshold for soil moisture
    digitalWrite(RELAY_PIN, HIGH);  // Turn on the relay
    Blynk.virtualWrite(V5, 255);    // Turn on the LED on Blynk dashboard
    Serial.println("Relay ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off the relay
    Blynk.virtualWrite(V5, 0);      // Turn off the LED on Blynk dashboard
    Serial.println("Relay OFF");
  }

  delay(2000);
}

void th() {
  delay(2000); 

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); 
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, temperature);
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

void co2() {
  float CO2_ppm = readCO2();
  Blynk.virtualWrite(V3, CO2_ppm);
  Serial.print("CO2 concentration: ");
  Serial.print(CO2_ppm);
  Serial.println(" ppm");
  delay(2000);  // Delay between readings
}

float readCO2() {
  int sensorValue = analogRead(ANALOG_PIN);
  float voltage = sensorValue * (3.3 / 4095.0); 
  float CO2_ppm = map(sensorValue, 0, 4095, 0, 2000);
  return CO2_ppm;
}

void calculateFlow() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - oldTime;

  if (elapsedTime > 1000) {  // Only calculate flow rate every 1 second
    noInterrupts();
    float flowRate = (flowPulseCount / 7.5);  // Example conversion, adjust according to your flow sensor
    flowPulseCount = 0;
    interrupts();

    oldTime = currentTime;

    Blynk.virtualWrite(V4, flowRate);
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");
  }
}

void loop() {
  soilMoisture();
  th();
  co2();
  calculateFlow();
  Blynk.run();
  delay(200);
}
