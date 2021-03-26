#include "sram.h"

SRAM sram_a('A'); // Create object from SRAM class

void setup()
{
  Serial.begin(9600);
  SPI.begin();
}

void loop()
{
  sram_a.WriteCheckerboard();
  Serial.println(sram_a.ReadByte(1001),BIN);
  delay(100);
}
