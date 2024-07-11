#include <Wire.h>

// Define MCP3424 I2C addresses based on ADDR pin state
#define MCP3424_ADDRESS_GND 0x68 // ADDR pin connected to GND
#define MCP3424_ADDRESS_VDD 0x69 // ADDR pin connected to VDD

// Set the I2C address of your MCP3424 based on ADDR pin configuration
#define MCP3424_ADDRESS MCP3424_ADDRESS_GND

// MCP3424 Command Bits
#define MCP3424_START_CONVERSION 0x80
#define MCP3424_READ_CHANNEL_1   0x00
#define MCP3424_READ_CHANNEL_2   0x20
#define MCP3424_READ_CHANNEL_3   0x40
#define MCP3424_READ_CHANNEL_4   0x60
#define MCP3424_CONTINUOUS_MODE  0x10
#define MCP3424_ONE_SHOT_MODE    0x00
#define MCP3424_SAMPLE_RATE_12BIT 0x00
#define MCP3424_SAMPLE_RATE_14BIT 0x04
#define MCP3424_SAMPLE_RATE_16BIT 0x08
#define MCP3424_SAMPLE_RATE_18BIT 0x0C
#define MCP3424_GAIN_1           0x00
#define MCP3424_GAIN_2           0x01
#define MCP3424_GAIN_4           0x02
#define MCP3424_GAIN_8           0x03

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  long adcValue = readADC(MCP3424_READ_CHANNEL_1 | MCP3424_SAMPLE_RATE_18BIT | MCP3424_GAIN_1);
  Serial.print("ADC Value: ");
  Serial.println(adcValue);
  delay(1000); 
}

long readADC(byte config) {
  Wire.beginTransmission(MCP3424_ADDRESS);
  Wire.write(config | MCP3424_START_CONVERSION);
  Wire.endTransmission();

  delay(150); // Wait for conversion (adjust based on resolution)

  Wire.requestFrom(MCP3424_ADDRESS, 4);
  if (Wire.available() == 4) {
    byte byte1 = Wire.read();
    byte byte2 = Wire.read();
    byte byte3 = Wire.read();
    byte byte4 = Wire.read();
    long result = ((long)byte1 << 16) | ((long)byte2 << 8) | byte3;
    result = result >> (8 - (byte4 & 0x07)); // Adjust based on resolution
    return result;
  }
  return 0; // Return 0 if not available
}
