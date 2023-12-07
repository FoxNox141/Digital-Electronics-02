#include <Arduino.h>
#include <EEPROM.h>

//inspirováno z této stránky: https://docs.arduino.cc/learn/programming/eeprom-guide, upraveno + přebrány části ze cvik a dalších zdrojů

// Structure for storing sensor data in EEPROM
typedef struct {
  uint8_t soilMoistmeter;  // Soil moisture value
  uint8_t airHumidity;   // Air humidity value
  uint8_t temperature; //
} 

Databank;

int addr = 0;


void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Indication that the serial port is open
  Serial.println("Serial port is open!");
}

void loop() {
  int soilMoistmeter = analogRead(0) / 4;
  int airHumidity = analogRead(1) / 4;
  int temperature = analogRead(2) / 4;

  // Create a SensorData object
  Databank sensorValue;
  sensorValue.soilMoistmeter = (uint8_t)soilMoistmeter;
  sensorValue.airHumidity = (uint8_t)airHumidity;
  sensorValue.temperature = (uint8_t)temperature;

  // Write the sensor data to EEPROM
  writeDataToEEPROM(addr, &sensorValue);

  // Advance to the next address. When at the end, restart from the beginning.
  addr = addr + 1;
  if (addr == EEPROM.length()) {
    addr = 0;
  }
  delay(1000);
}

// Writing data to EEPROM
void writeDataToEEPROM(uint16_t address, const Databank * data) 
{
  EEPROM.write(address, data->soilMoistmeter);
  EEPROM.write(address + sizeof(data->soilMoistmeter), data->airHumidity);
  EEPROM.write(address + sizeof(data->soilMoistmeter) + sizeof(data->airHumidity), data->temperature);
}
// Reading data from EEPROM
void readDataFromEEPROM(uint16_t address, Databank * data) 
{
  data->soilMoistmeter = EEPROM.read(address);
  data->airHumidity = EEPROM.read(address + sizeof(data->soilMoistmeter));
  data->temperature = EEPROM.read(address + sizeof(data->soilMoistmeter) + sizeof(data->airHumidity));
}