#include <Arduino.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <RTClib.h> // Include the RTC library

#define RST_PIN       5      // Reset pin (RST) of MFRC522
#define SS_PIN        4      // Slave Select (SS) pin of MFRC522
#define SOL_LOCK_PIN  2      // Pin connected to the solenoid lock

#define SDA_PIN       21     // I2C SDA Pin
#define SCL_PIN       22     // I2C SCL Pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD I2C address and LCD dimensions
RTC_DS1307 rtc; // Create RTC object

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27}; // Row pin numbers
byte colPins[COLS] = {26, 25, 32, 33}; // Column pin numbers
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C bus
  pinMode(SOL_LOCK_PIN, OUTPUT); // Set solenoid lock pin as output

  SPI.begin();                  // Initialize SPI bus
  mfrc522.PCD_Init();           // Initialize MFRC522 RFID reader

  rtc.begin(); // Initialize RTC module
  if (!rtc.isrunning()) { // Set RTC time if not set
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.init();                   // Initialize the LCD
  lcd.backlight();              // Turn on the backlight

  lcd.setCursor(0, 0);
  lcd.print("RFID & Keypad Lock");
}

void loop() {
  // Scan for RFID tags
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RFID Tag:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      lcd.print(" ");
      lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      lcd.print(mfrc522.uid.uidByte[i], HEX);
    }
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RFID & Keypad Lock");
  }

  // Check for keypad input
  char key = keypad.getKey();
  if (key != NO_KEY) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Key pressed:");
    lcd.setCursor(0, 1);
    lcd.print(key);
    if (key == '#') {
      digitalWrite(SOL_LOCK_PIN, HIGH); // Unlock the solenoid lock
      delay(5000); // Keep the lock open for 5 seconds
      digitalWrite(SOL_LOCK_PIN, LOW);  // Lock the solenoid lock
    }
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RFID & Keypad Lock");
  }
}
