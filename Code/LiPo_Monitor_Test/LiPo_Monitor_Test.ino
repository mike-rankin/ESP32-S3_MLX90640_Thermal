#include <Wire.h>
#include "Adafruit_MAX1704X.h"

Adafruit_MAX17048 maxlipo;

void setup() 
{
  Serial.begin(115200);
  Wire.begin(18,17);  //Pico Mini 02  
  //while (!Serial) delay(10);    // wait until serial monitor opens
  delay(100);

  Serial.println(F("\nAdafruit MAX17048 simple demo"));

  maxlipo.begin();
  delay(100);
  //if (!maxlipo.begin()) {
  //  Serial.println(F("Couldnt find Adafruit MAX17048?\nMake sure a battery is plugged in!"));
  //  while (1) delay(10);
  //}
  Serial.print(F("Found MAX17048"));
  Serial.print(F(" with Chip ID: 0x")); 
  Serial.println(maxlipo.getChipID(), HEX);
}

void loop()
 {
  Serial.print(F("Batt Voltage: ")); Serial.print(maxlipo.cellVoltage(), 3); Serial.println(" V");
  Serial.print(F("Batt Percent: ")); Serial.print(maxlipo.cellPercent(), 1); Serial.println(" %");
  Serial.println();

  delay(2000);  // dont query too often!
}
