#include <Arduino.h>
#include <EEPROM.h>

/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() 
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduino Duemilanove: 512 B EEPROM storage.
    - Arduino Uno:         1 kB EEPROM storage.
    - Arduino Mega:        4 kB EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }
  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(500);
}

  void loop() {
  /***
    need to divide by 4 because analog inputs range from
    0 to 1023 and each byte of the EEPROM can only hold a
    value from 0 to 255.
  ***/
  int val = analogRead(0) / 4;

  /***
    Update the particular EEPROM cell.
    these values will remain there when the board is
    turned off.
  ***/
  EEPROM.update(address, val);

  /***
    The function EEPROM.update(address, val) is equivalent to the following:

    if( EEPROM.read(address) != val ){
      EEPROM.write(address, val);
    }
  ***/


  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduino Duemilanove: 512 B EEPROM storage.
    - Arduino Uno:         1 kB EEPROM storage.
    - Arduino Mega:        4 kB EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(100);
}

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addr = 0;

void setup() {

  /** Empty setup. **/
}

void loop() {

  /***

    Need to divide by 4 because analog inputs range from

    0 to 1023 and each byte of the EEPROM can only hold a

    value from 0 to 255.

  ***/

  int val = analogRead(0) / 4;

  /***

    Write the value to the appropriate byte of the EEPROM.

    these values will remain there when the board is

    turned off.

  ***/

  EEPROM.write(addr, val);

  /***

    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:

    - Arduno Duemilanove: 512b EEPROM storage.

    - Arduino Uno:        1kb EEPROM storage.

    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.

    This will make your code portable to all AVR processors.

  ***/

  addr = addr + 1;

  if (addr == EEPROM.length()) {

    addr = 0;

  }

  /***

    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an

    EEPROM address is also doable by a bitwise and of the length - 1.

    ++addr &= EEPROM.length() - 1;

  ***/

  delay(100);
}

// #define Components used init


// #define ARRAY_SIZE  define working place size
// #define LAST_SELECTED_EEPROM (int) selects last input (optional)

/* 
int Array[4] = { };

int i;

void setModes() 
{
  for (i = 0 ; i < ARRAY_SIZE ; i++) {
    pinMode(Array[i], OUTPUT);
  }
}

void setInitialStates()
{
  for (i = 0 ; i < ARRAY_SIZE ; i++) {
    digitalWrite(Array[i], LOW);
  }
}

void powerOn(int Index)
{
  for (i = 0; i < ARRAY_SIZE; i++) {
    if (i == Index) {
      digitalWrite(Array[i], HIGH);
    }
    else {
      digitalWrite(Array[i], LOW);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setModes();
  int lastSelectedIndex = EEPROM.read(LAST_SELECTED_EEPROM);
  powerOn(lastSelectedIndex);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    int ledIndex = Serial.parseInt();
    if (ledIndex >= 0 && ledIndex < ARRAY_SIZE) {
      powerOnLed(ledIndex);
      // write on the eeprom
      EEPROM.write(LAST_SELECTED_LED_EEPROM_ADDR, ledIndex);
    }
  }
}

*/