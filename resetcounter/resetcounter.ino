#include <EEPROM.h>
void setup() {
  // Inicjalizacja połączenia z EEPROM
  EEPROM.begin();

  // Ustawianie wartości pamięci EEPROM na 0
  for (int i = 5; i >= 0; i--) {
    EEPROM.write(i, 0);
  }

  // Zakończenie połączenia z EEPROM
  EEPROM.end();
}
void loop(){
  
}
