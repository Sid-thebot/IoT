#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Create an RF24 object
RF24 radio(9, 10); // CE, CSN 

// Address through which two modules communicate.
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  const char text[] = "Hello from Arduino uno 1";
  radio.stopListening();
  radio.write(&text, sizeof(text));
  Serial.println("Message sent");
  delay(1000);
}
