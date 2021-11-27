// This Script takes the binary representations of the cell connections and actuates the relays accordingly

// We need to include the definictions for the relay delays
#include "Definitions.h"

// We also define a constant 2D array that defines which arduino pins are connected to which Set and Reset pins on the PCB
#if defined Board_Version && Board_Version == 3
const int Set_Pins[][4] = {{3}, {4}, {5}, {6}, {7}};
const int Reset_Pins[][4] = {{8}, {9}, {10}, {11}, {12}};
#else
// In this case the Set pin 1 is connected to pin D3 on the arduino, Set pin 2 to pin D18 (A4), Set pin 3 to pin D4, Set pin 4 to pins 15 and 16 (A0,A1) and Set pin 5 to pins D10-D13
const int Set_Pins[][4] = {{3}, {18}, {4}, {15, 16}, {10, 11, 12, 13}};
const int Reset_Pins[][4] = {{2}, {19}, {5}, {17, 18}, {6, 7, 8, 9}};
#endif

// We import the extern char array that stores the current binary label used on the label translator script
extern char Binary_Label[];

int Set_Pin_To_Actuate = 0;
int Reset_Pin_To_Actuate = 0;

// This function takes the current Binary_Label value and sets each arduino pin to its corresponding state
void Relay_Actuate()
{
  for (int j = 0; j < 5; j++) {                             // We run through all the values of the Binary label (5 values)

    int Pin_state = Binary_Label[j] - 48;                   // We convert the current char to an integer by substracting the '0' char value (48)

    for (int k = 0; k < 4; k++) {                           // We loop through all the pins stored within the array (maximum of 4)

      Set_Pin_To_Actuate =  Set_Pins[j][k];                 // We extract the Set pin number from the Set_Pins array as well as the Reset pin number from the Reset_Pins array
      Reset_Pin_To_Actuate =  Reset_Pins[j][k];

      if (Set_Pin_To_Actuate != 0) {                        // We only actuate the pin if the pin number is not 0
        Digital_Write_Pin(Set_Pin_To_Actuate, Pin_state);        // We write the state of the current Binary label number to the selected Set pin
      }

      if (Reset_Pin_To_Actuate != 0) {                      // We only actuate the pin if the pin number is not 0
        Digital_Write_Pin(Reset_Pin_To_Actuate, invert(Pin_state));  // We write the inverse state of the current Binary label number to the selected Reset pin
      }
    }

    delay(Relay_Delay);                                     // We give some time to the relays to get into position
    Reset_All_Pin_States();                                 // We reset all the pins to low to save power

  }
}

// This function sets all the digital pins to LOW
void Reset_All_Pin_States() {

  for (int pin = 2; pin <= 19; pin++)
  {
    digitalWrite(pin, LOW);
  }

  delay(Relay_Delay);         // We wait a bit so the relays gan get into position
}


// This is a small function that inverts the value of the incoming bit, if the input is 1 the output is 0 and viceversa, the difference with a NOT statement is that this works with a uint8_t value and not a boolean
uint8_t invert(uint8_t value)
{
  uint8_t Buffer = 0;                                                         //Buffer value that will store the bit value
  if (value == 1 || value == 0)                                               //Only perform the function if the input values are binary
  {
    Buffer = (value - 1) * (value - 1);                                       // transforms a 0 into a 1 and viceversa
  }
  return (Buffer);                                                            // Return the inverted value
}


// This function prints the current pin number and its status for debugging purposes
void Print_Pin_Status(int Pin_Number, boolean Pin_State)
{
  Serial.print("Pin number: ");
  Serial.print(Pin_Number);
  Serial.print(" is ");
  Serial.println(Pin_State);
}

// This function wites high or low on the specified pin depending on the Pin_State Input
void Digital_Write_Pin(int Pin_Number, int Pin_State)
{
  boolean Actual_Write = false;
  if (Pin_State == 1)
  {
    digitalWrite(Pin_Number, HIGH);
    Actual_Write = true;
  }
  else
  {
    digitalWrite(Pin_Number, LOW);
    Actual_Write = false;
  }
#ifdef Debugging
  Print_Pin_Status(Pin_Number, Actual_Write);      // If we are debugging we print the state of each pin
#endif
}
