#include <Servo.h>

// Define pin connections
const int flameSensorPin = A0; // Analog pin for flame sensor
const int relayPin = 7;        // Digital pin for relay
const int servoPin = 9;        // Digital pin for servo

Servo myServo; // Create servo object

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the relay pin as an output
  pinMode(relayPin, OUTPUT);
  
  // Initially turn off the pump
  digitalWrite(relayPin, HIGH);
  
  // Attach the servo to the servo pin
  myServo.attach(servoPin);

  // Set the initial position of the servo
  myServo.write(90); // Middle position (adjust based on your setup)
}

void loop() {
  // Read the flame sensor value
  int flameSensorValue = analogRead(flameSensorPin);
  
  // Print the sensor value to the serial monitor (for debugging)
  Serial.println(flameSensorValue);
  
  // Threshold value for flame detection (adjust based on your sensor's specifications)
  int threshold = 500;

  if (flameSensorValue < threshold) {
    // Flame detected
    digitalWrite(relayPin, LOW); // Turn on the pump
    Serial.println("Flame detected! Pump ON.");
    
    // Move the servo to a specific position
    myServo.write(180); // Move to one extreme position
  } else {
    // No flame detected
    digitalWrite(relayPin, HIGH); // Turn off the pump
    Serial.println("No flame detected. Pump OFF.");
    
    // Move the servo to another position
    myServo.write(0); // Move to the other extreme position
  }
  
  // Small delay for stability
  delay(100);
}