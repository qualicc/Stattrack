#include <Arduino.h>
#include <TM1637TinyDisplay6.h>  
#include <EEPROM.h>
const int CLK = 3; // Set the CLK pin connection to the display
const int DIO = 2; // Set the DIO pin connection to the display
const int buttonPin = 11; // Set the button pin
TM1637TinyDisplay6 display(CLK, DIO); //set up the 6-Digit Display.

bool helper = true; // helper for button break 
int buttonState = 0;  // variable for reading the pushbutton status
int number = 0; // current kill counter

void setup()
{
 display.setBrightness(0x0a, true); //set the diplay to maximum brightness

 pinMode(buttonPin, INPUT);

 // Read the last saved value from EEPROM for each digit
  for (int i = 0; i < 6; i++) {
    byte digitValue = EEPROM.read(i);
    number = number * 10 + digitValue;
  }

  display.showNumberDec(number); // Display the saved value
}
void saveNumberToEEPROM()
{
  // Save each digit of the number to EEPROM
  int tempNumber = number;
  for (int i = 5; i >= 0; i--) {
    byte digitValue = tempNumber % 10;
    tempNumber /= 10;
    EEPROM.write(i, digitValue);
  }
}
void loop()
{

  buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      if(helper)
      {
        number++;
        saveNumberToEEPROM();
        helper = false;
      }
    }
    else
    {
      helper = true;
    }
  display.showNumberDec(number); //Display the kill counter;
}