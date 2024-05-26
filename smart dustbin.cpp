#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const int servoPin = 11;

long duration;
int distance;
Servo servo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
  // Initialize Wi-Fi module here (code not shown)
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by setting it HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distance = duration * 0.034 / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // If distance is less than a threshold (e.g., 10 cm), the bin is full
  if (distance < 10) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    // Send notification via Wi-Fi (code not shown)
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
  }
  
  // Optional: Control servo to open/close lid based on distance
  if (distance < 10) {
    servo.write(90); // Open lid
  } else {
    servo.write(0); // Close lid
  }
  
  delay(1000); // Wait for a second before next measurement
}
