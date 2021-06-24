// This Script extracts the Serial input and places it in a character array called Command[] so that it can be further used for cell selection and other features

const byte CommandSize = 64;                                               // Expect commands of up to 64 bytes
char Command[CommandSize];                                                 // initialize an array of characters that will be the received command
bool newData = false;                                                      // Start assuming there is no new data

// This function scans the serial input, extracts the Command sent to the arduino and stores it within the Command[] char array
void Get_Command ()                                                        
{
  static byte ndx = 0;                                                      // Define the index where the array will be written
  char endMarker = '\n';                                                    // Define the endmarker that will be recognized
  char rc;                                                                  // Received character

  if (Serial.available() > 0) {                                             // If there is data in the serial port then:
    if (newData == true) {
      Serial.println("echo: busy: processing");                             // If the newdata flag is still true send a message stating that arduino is still processing
    }
    while (Serial.available() > 0 && newData == false) {                    // While there is data in the serial port and the newData is not true keep reading
      rc = Serial.read();                                                   // Read the current byte in the buffer and store it in rc
      if (rc != endMarker) {                                                // If rc is not equal to the endmarker it means it is part of the command so write it on the array (in the place indicated by indx)
        Command[ndx] = rc;
        ndx++;                                                              // Increment the ndx counter so that the next character is written in the next spot on the array
        if (ndx >= CommandSize) {                                           // If the ndx overflows (is bigger than the commandSize specified) bring it down by one and start writing over the last value
          ndx = CommandSize - 1;                                            // of the array thus only replacing the last char and not causing errors
        }
      }
      else {
        Command[ndx] = '\0';                                                // Else (if rc == endMarker) then write \0 null value to the end of the array
        ndx = 0;                                                            // Reset the index counter for the next command
        newData = true;                                                     // Update the newdata flag to true

#ifdef Debugging
        Print_Command();                                                    // Print the input command for debugging purposes
#endif
      }
    }
  }
}


// This function prints the received command, it is basically useful for debugging the software
void Print_Command ()                                                       
{
  Serial.print("Received Command : ");
  Serial.println(Command);
}
