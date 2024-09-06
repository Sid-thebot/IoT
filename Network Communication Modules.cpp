#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(1000);
  mySerial.print("AT+CMGF=1\r");
  delay(100); 
  mySerial.print("AT+CMGS=\"+1234567890\"\r");
  delay(100);
  mySerial.print("Hello from Arduino!\r"); 
  delay(100);
  mySerial.write(26); // ASCII code of CTRL+Z
}
 
void loop() {
}
