// This script goes through every cell for a certain ammount of time so that one can debug both the software and the pcb correct operation

// We need to include the Definitions for the delays
#include "Definitions.h"

// This function basically runs through all the labels, first right and then left, with a small delay inbetween so that the user has time to check if the connection is correct or not
void Test_Run()
{
  for (int m = 1; m < 13; m++) {
    R_Translator(m);
    delay(Test_Delay_1);
  }
  for (int n = 1; n < 13; n++) {
    L_Translator(n);
    delay(Test_Delay_1);
  }
  for (int m = 1; m < 13; m++) {
    R_Translator(m);
    delay(Test_Delay_2);
  }
  for (int n = 1; n < 13; n++) {
    L_Translator(n);
    delay(Test_Delay_2);
  }
}
