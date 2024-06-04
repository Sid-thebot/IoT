#include <ESP8266WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();

        client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        client.print("<html><body><h1>Hello, World!</h1></body></html>");
        break;
      }
    }
    client.stop();
    Serial.println("Client Disconnected");
  }
}
