// This script takes the selected label and copies the corresponding binary label into the Binary_Label[] char array so that it can be used by the Relay Actuate script.

// We need to include the header file to have all the binary representations
#include "Label_Mapping.h"

// We declare a new array that will hold the Binary label
char Binary_Label[] = "00000";

void R_Translator(int R_Label)
{
  switch (R_Label) {
    case 1:
      strcpy(Binary_Label, R_01);
      Relay_Actuate();
      break;

    case 2:
      strcpy(Binary_Label, R_02);
      Relay_Actuate();
      break;

    case 3:
      strcpy(Binary_Label, R_03);
      Relay_Actuate();
      break;

    case 4:
      strcpy(Binary_Label, R_04);
      Relay_Actuate();
      break;

    case 5:
      strcpy(Binary_Label, R_05);
      Relay_Actuate();
      break;

    case 6:
      strcpy(Binary_Label, R_06);
      Relay_Actuate();
      break;

    case 7:
      strcpy(Binary_Label, R_07);
      Relay_Actuate();
      break;

    case 8:
      strcpy(Binary_Label, R_08);
      Relay_Actuate();
      break;

    case 9:
      strcpy(Binary_Label, R_09);
      Relay_Actuate();
      break;

    case 10:
      strcpy(Binary_Label, R_10);
      Relay_Actuate();
      break;

    case 11:
      strcpy(Binary_Label, R_11);
      Relay_Actuate();
      break;

    case 12:
      strcpy(Binary_Label, R_12);
      Relay_Actuate();
      break;

    default:
      UnknownCommand();         //In the case of anything else, send: Unknown Command
      break;
  }
}


void L_Translator(int L_Label)
{
  switch (L_Label) {
    case 1:
      strcpy(Binary_Label, L_01);
      Relay_Actuate();
      break;

    case 2:
      strcpy(Binary_Label, L_02);
      Relay_Actuate();
      break;

    case 3:
      strcpy(Binary_Label, L_03);
      Relay_Actuate();
      break;

    case 4:
      strcpy(Binary_Label, L_04);
      Relay_Actuate();
      break;

    case 5:
      strcpy(Binary_Label, L_05);
      Relay_Actuate();
      break;

    case 6:
      strcpy(Binary_Label, L_06);
      Relay_Actuate();
      break;

    case 7:
      strcpy(Binary_Label, L_07);
      Relay_Actuate();
      break;

    case 8:
      strcpy(Binary_Label, L_08);
      Relay_Actuate();
      break;

    case 9:
      strcpy(Binary_Label, L_09);
      Relay_Actuate();
      break;

    case 10:
      strcpy(Binary_Label, L_10);
      Relay_Actuate();
      break;

    case 11:
      strcpy(Binary_Label, L_11);
      Relay_Actuate();
      break;

    case 12:
      strcpy(Binary_Label, L_12);
      Relay_Actuate();
      break;

    case 13:
      strcpy(Binary_Label, L_13);    // Added this char array to protect the L_12 array from getting corrupted it does not serve any functional purpose but without it L_12 goes corrupt
      break;

    default:
      UnknownCommand();         //In the case of anything else, send: Unknown Command
      break;
  }
}
