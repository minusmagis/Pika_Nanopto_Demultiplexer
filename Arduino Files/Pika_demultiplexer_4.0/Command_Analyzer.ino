// This script analyzes the input command to decide which function to execute

// We first import external variables that are needed within this script
extern bool newData;
extern char Command[];
extern char Binary_Label[];


// This function takes the variable Command and extracts the first letter to decide which function to execute
void Command_Analyzer()
{
  if (newData)                                       // We only execute if there is new data available
  {
    switch (Command[0])
    {
      case 'R':                               // Extract the label and set the corresponding R cell
        R_Translator(Label_Extract());
        break;

      case 'L':                               // Extract the label and set the corresponding L cell
        L_Translator(Label_Extract());
        break;

      case 'T':                               // Run through all the channels to test the connection
        Test_Run();
        break;

      case 'H':                               // Display help menu
        Help();
        break;

      case 'h':                               // Display help menu
        Help();
        break;

      case ';':                               //In the case of a ; ignore the rest
        break;

      default:
        UnknownCommand();                   //In case of anything else, send: Unknown Command
        break;
    }

    newData = false;                          // Set the newData flag to false once you have executed the necessary functions
  }
}


// This function extracts the third and fourth values of the input command, where the label information is stored and returns it as an int
int Label_Extract()
{
  int Label = (Command[2] - 48) * 10 + (Command[3] - 48);   // To extract the number we just substract the 0 value to each of the characters and take the first as the tenths and the second as the units

#ifdef Debugging
  Print_Label(Label);                                       // Print the label only when debugging
#endif

  return Label;                                             //Return the label value as an int
}

// This function displays an Unknown command echo with the input command for debugging purposes
void UnknownCommand()
{
  Serial.print("echo:Unknown command: ");
  Serial.print('"');
  Serial.print(Command);
  Serial.println('"');
}

// This function just prints the label the arduino has received for debugging purposes
void Print_Label(int Label_Number)
{
  Serial.print("Received Label : ");
  Serial.println(Label_Number);
}
