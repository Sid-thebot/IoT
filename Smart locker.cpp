#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// MQTT broker
const char* mqtt_server = "your_MQTT_BROKER_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);

const int lockPin = 2;  // GPIO pin connected to the lock

void setup() {
  Serial.begin(115200);
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH);  // Assume HIGH is locked

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("lock_command");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String command;
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }

  if (command == "open") {
    digitalWrite(lockPin, LOW);  // Assume LOW is unlocked
    client.publish("lock_status", "unlocked");
  } else if (command == "close") {
    digitalWrite(lockPin, HIGH);  // Assume HIGH is locked
    client.publish("lock_status", "locked");
  }
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      if (client.connect("ESP32Client")) {
        Serial.println("connected");
        client.subscribe("lock_command");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        delay(2000);
      }
    }
  }
  client.loop();
}
