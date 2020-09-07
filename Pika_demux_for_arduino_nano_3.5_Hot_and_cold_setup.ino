/*
    Master thesis arduino Nanopto time saver
    This programme is used to control a demultiplexer of 24-1 channels.
    It needs a specific pcb design, for more questions contact minusmagis@gmail.com


    2020 02 20 changes: We changed the pins to add cooling and heating capabilities. Now pin 9 and 10 will be used to drive an h bridge that will cool or heat the sample.
    Remember to send the data witout line ending!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  (otherwise it will not work :3 )

                                                                          READ THE LINE IMMEDIATELY ABOVE

    2020 09 07 changes: The mapping was completely wrong and we are now recalibrating it

*/



String Cell;                          //String that will determine which cell is being measured
String CellLabel;                     //String that will be the name of the cell
String CellBit;                       //The bitcode of each cell
uint8_t Bit0 = 0;                     // Ground Bit, it will always be zero
uint8_t Bit1 = 0;                     //Bits that will determine the signal emitted to the arduino, hence the cell that will be connected
uint8_t Bit2 = 0;
uint8_t Bit3 = 0;
uint8_t Bit4 = 0;
uint8_t Bit5 = 0;
uint8_t NotBit1 = 0;                  // Stores the values of the reset pins
uint8_t NotBit2 = 0;
uint8_t NotBit3 = 0;
uint8_t NotBit4 = 0;
uint8_t NotBit5 = 0;


#define PWMPin 9                      // Pin that will be used to PWM the signal
#define HnCPin 10                     // Pin that will decide the polarity of the H bridge (hot is Low and cold is high)


// This is a very simple setup loop that sets all pins as outputs and begins serial coms
void setup()
{
  for (uint8_t pin = 2; pin < 14; pin++) //First we define all pins as outputs
  {
    pinMode(pin, OUTPUT);             // Defines pins from 2 to 13 as an output
  }
  pinMode(A0, OUTPUT);                // Also the analog pins
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);

  Serial.begin(9600);                 // We begin Serial communication
  Serial.println("Arduino Multiplexer Hot N' Cold");        // We also print a welcome message so that we know which arduino we are talking to
}

// The main loop waits for an input within the serial connection and when provided with one evaluates if it fits within the available commands.
// Whenever feeded a valid comand the loop executes the corresponding function. This programming style is a bit clumsy since I programmed it with little knowledge about C++

void loop()
{
  if (Serial.available() > 0)                                                 // If the serial is trying to communicate calls the functiond SelectedCell() stated below and
  {                                                                           // assigns its value to the string Cell that will determine which cell is being measured
    Cell = SelectedCell();                                                    // The function SelectedCell extracts the characters from the serial and stores them within a string                               
    
    //Serial.println(Cell);                                                   // For debugging purposes
    
    if (Cell.length() > 3)                                                    // If the length of the command is longer than 3, meaning it is most likely a complete command c
    {                                                                         // we call the function SelectedCellName that will output the label of the cell as well as the bitstring needed to contact that specific cell
          
      //Serial.print("Plain data from serial = ");                            // For debugging purposes
      
      CellBit = SelectedCellName(Cell);                                       // We assign the bitstring (binary code) of the cell that we desire to connect to the variable CellBit
      
      //Serial.println(CellBit);                                              // For debugging purposes
      
      if (CellBit != "")                                                      // If the bitstring is not empty, it means we have a valid input that we can use to decide which relays we have to flip
      {
        
        //        Serial.print("     Cell binary code = ");                   // For debugging purposes
        //        Serial.println(CellBit);                   
        //        Serial.println("-----------------------------------------------"); 
        
        Bit1 = ReadBit(CellBit, 1);                                           // Assign the value of the first bit from the bitcode to a variable Bit1
        Bit2 = ReadBit(CellBit, 2);                                           // Assign the value of the second bit from the bitcode to a variable Bit2
        Bit3 = ReadBit(CellBit, 3);                                           // Assign the value of the third bit from the bitcode to a variable Bit3
        Bit4 = ReadBit(CellBit, 4);                                           // Assign the value of the forth bit from the bitcode to a variable Bit4
        Bit5 = ReadBit(CellBit, 5);                                           // Assign the value of the fifth bit from the bitcode to a variable Bit5
        NotBit1 = invert(Bit1);                                               // Use the function invert to generate the complementary values from BitX values
        NotBit2 = invert(Bit2);
        NotBit3 = invert(Bit3);
        NotBit4 = invert(Bit4);
        NotBit5 = invert(Bit5);
        
        //        Serial.print(Bit1);                                         // For debugging purposes
        //        Serial.println(NotBit1);  
        //        Serial.print(Bit2);
        //        Serial.println(NotBit2);
        //        Serial.print(Bit3);
        //        Serial.println(NotBit3);
        //        Serial.print(Bit4);
        //        Serial.println(NotBit4);
        //        Serial.print(Bit5);
        //        Serial.println(NotBit5);
        //        Serial.println("-----------------------------------------------");
        //        Serial.println("Please introduce the next cell label you want to measure:");  // Write this message on the serial port so that the use knows that he can change the cell number

        digitalWrite(2, LOW);                                                 // The pin 0 reset and set is always ground in this case one corresponds to pin 14 and the other to pin 2 on the arduino,
                                                                              // pin 14 is ground by default in arduino
                                                                              
        digitalWrite(3, Bit1);                                                // Write the value of BitX (etither 0 or 1) to each pin on the arduino to contact the cell
        digitalWrite(2, NotBit1);                                             // We write the inverse value on the reset pins so that we make sure each relay is on the desired position. (These relays are bistable so they need to be set
                                                                              // and reset so that they are placed on the propper position
        delay(5);                                                             // We introduce a small delay so that the relays have time to switch
                                                                                  
        digitalWrite(2, LOW);                                                 // We set the set and reset to low to lower power consumption
        digitalWrite(3, LOW);
        delay(5);
        
        digitalWrite(A4, Bit2);                                               // We repeat for every pin untill every relay is on their desired position
        digitalWrite(A5, NotBit2);
        delay(5);
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        delay(5);
        digitalWrite(4, Bit3);
        digitalWrite(5, NotBit3);
        delay(5);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);

        delay(5);
        digitalWrite(A1, Bit4);
        digitalWrite(A0, Bit4);
        digitalWrite(A3, NotBit4);
        digitalWrite(A2, NotBit4);
        delay(5);
        
        for (uint8_t i = 2; i < 14; i++)                                      //Write low on every bit to limit current consumption, in this way we give all the power to the following bits, which will require it
        {
          digitalWrite(i, LOW);
        }
        digitalWrite(A0, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A3, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        digitalWrite(A6, LOW);
        digitalWrite(A7, LOW);
        delay(5);
        digitalWrite(11, Bit5);
        digitalWrite(12, Bit5);
        digitalWrite(13, Bit5);
        digitalWrite(6, NotBit5);
        digitalWrite(7, NotBit5);
        digitalWrite(8, NotBit5);
        delay(5);
        
        for (uint8_t i = 2; i < 14; i++)                                      // We finally write all bits to LOW to reduce power consumption
        {
          digitalWrite(i, LOW);
        }
        digitalWrite(A0, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A3, LOW);
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        digitalWrite(A6, LOW);
        digitalWrite(A7, LOW);

      }
    }
    
    else {
      
      //Serial.println("Incorrect Cellbit");                                  // For debugging purposes
      
      Serial.read();                                                          // In case we receive an empty input we read the serial to clear it
    }
  }
}

uint8_t invert(uint8_t value)                                                 // This is a small function that inverts the value of the incoming bit, if the input is 1 the output is 0 and viceversa, the difference with a NOT statement
{                                                                             // is that this works with a uint8_t value and not a boolean
  
  uint8_t Buffer = 0;                                                         //Buffer value that will be used in the function
  if (value == 1 || value == 0)                                               //Only perform the function if the input values are binary
  {
    Buffer = (value - 1) * (value - 1);                                       // transforms a 0 into a 1 and viceversa
  }
  else                                                                        // If the values are not binary in nature do nothing
  {
  }
  return (Buffer);                                                            // Return the inverted value
}


uint8_t ReadBit (String BitCode, uint8_t BitNum)                              // This function reads the specified bit within the bitstring of the incoming command
{
  uint8_t Bit = 1;                                                            // We first initialize the variables we will use
  String Buffer = String("");
  Buffer = BitCode.substring((BitNum - 1), BitNum);                           // We extract the substring from the bitstring called BitCode within the specified position
  Bit = Buffer.toInt();                                                       // We transform the character into an integer
  return (Bit);                                                               // We return the value
}


String SelectedCellName(String CellName)                                      // This function translates the input serial string to its corresponding bitstring, it is grossely unoptimized but it works.
{
  String bitString = String("");                                              // We initialize some variables
  String HotCold = String("");
  
  HotCold = CellName.substring(0, 2);                                         // We extract the first character to see if the input is prompting us to heat or cool the setup

  if (CellName == "82464849")                               //R.01 *          // If the input CellName is equal to this particular string, which in this case corresponds to R.01 we set the bitstring to 01000 which turns the 
  {                                                                           // relays so that the connected cell is R.01
    bitString = String("01000");                            //R.01 *          // We chech if the cellname corresponds to any of the specified commands and if it does we set the bitstring to its corresponding cell
  }
  else if (CellName == "82464850")                          //R.02 *
  {
    bitString = String("01001");                            //R.02 *
  }
  else if (CellName == "82464851")                          //R.03 *
  {
    bitString = String("01011");                            //R.03 *
  }
  else if (CellName == "82464852")                          //R.04 *
  {
    bitString = String("01010");                            //R.04 *
  }
  else if (CellName == "82464853")                          //R.05 *
  {
    bitString = String("11100");                            //R.05 *
  }
  else if (CellName == "82464854")                          //R.06 *
  {
    bitString = String("11101");                            //R.06 *
  }
  else if (CellName == "82464855")                          //R.07 *
  {
    bitString = String("11111");                            //R.07 *
  }
  else if (CellName == "82464856")                          //R.08 *
  {
    bitString = String("11110");                            //R.08 *
  }
  else if (CellName == "82464857")                          //R.09 *
  {
    bitString = String("11010");                            //R.09 *
  }
  else if (CellName == "82464948")                          //R.10 *
  {
    bitString = String("11011");                            //R.10 *
  }
  else if (CellName == "82464949")                          //R.11 *
  {
    bitString = String("11001");                            //R.11 *
  }
  else if (CellName == "82464950")                          //R.12 *
  {
    bitString = String("11000");                            //R.12 *
  }
  else if (CellName == "76464849")                          //L.01 *
  {
    bitString = String("00010");                            //L.01 *
  }
  else if (CellName == "76464850")                          //L.02 *
  {
    bitString = String("00011");                            //L.02 *
  }
  else if (CellName == "76464851")                          //L.03 *
  {
    bitString = String("00001");                            //L.03 *
  }
  else if (CellName == "76464852")                          //L.04 *
  {
    bitString = String("00000");                            //L.04 *
  }
  else if (CellName == "76464853")                          //L.05 *
  {
    bitString = String("10100");                            //L.05 *
  }
  else if (CellName == "76464854")                          //L.06 *
  {
    bitString = String("10101");                            //L.06 *
  }
  else if (CellName == "76464855")                          //L.07 *
  {
    bitString = String("10111");                            //L.07 *
  }
  else if (CellName == "76464856")                          //L.08 *
  {
    bitString = String("10110");                            //L.08 *
  }
  else if (CellName == "76464857")                          //L.09 *
  {
    bitString = String("10010");                            //L.09 *
  }
  else if (CellName == "76464948")                          //L.10 *
  {
    bitString = String("10011");                            //L.10 *
  }
  else if (CellName == "76464949")                          //L.11 *
  {
    bitString = String("10001");                            //L.11 *
  }
  else if (CellName == "76464950")                          //L.12 *
  {
    bitString = String("10000");                            //L.12 *
  }
  
  else if (HotCold == "72")                                                       // If the first letter is an H it means that the user wants to heat up the holder
  {
    if (CellName.length() == 8) {                                                 // After the H there must be a 3 digit number from 000 to 255 that specifies the amount of power we want to use for heating, being 0 no power and 255 max power
      
      int PWMSignal = 0;                                                          // We initialize some variables
            
      PWMSignal = Stringtoint(CellName);                                          // We turn the CellName which contains the 3 digit number into an integer using the Stringtoint() function
      PWMSignal = constrain(PWMSignal, 0, 255);                                   // We constrain the input value within the limits of the arduino PWM
      digitalWrite(HnCPin, LOW);                                                  // Bring the pin low to set it for heating
      delay(10);                                                                  // A small delay prevents having the H bridge in short circuit
      analogWrite(PWMPin, PWMSignal);                                             // Write the power at wich you want to heat up
            
      //Serial.print("Heating at this power = ");                                 // For debugging purposes
      //Serial.println(PWMSignal);
    }
  }
  else if (HotCold == "67")                                                       // If the first letter is an C it means that the user wants to cool down the holder
  {
    if (CellName.length() == 8) {                                                 // After the C there must be a 3 digit number from 000 to 255 that specifies the amount of power we want to use for cooling, being 0 no power and 255 max power
      
      int PWMSignal = 0;                                                           // We initialize some variables

      PWMSignal = Stringtoint(CellName);                                          // We turn the CellName which contains the 3 digit number into an integer using the Stringtoint() function
      PWMSignal = constrain(PWMSignal, 0, 255);                                   // We constrain the input value within the limits of the arduino PWM
      digitalWrite(HnCPin, HIGH);                                                 // Bring the pin high to set it for cooling
      delay(10);                                                                  // A small delay prevents having the H bridge in short circuit
      analogWrite(PWMPin, PWMSignal);                                             //Write the power at wich you want to cool down

      //Serial.print("Cooling at this power = ");                                 // For debugging purposes
      //Serial.println(PWMSignal);
    }
  }
  
  else
  {
    //Serial.println("Cell not recognized");                                      // For debugging purposes
  }
  return (bitString);                                                             // We return the bitstring so that the cell can be propperly selected
}


int Stringtoint (String Toint) {                                                  // This function transforms the heating and cooling commands to integer values that we can use for PWM
  
  String OutString = String("");                                                  // We initialize some variables
  
  for (uint8_t i = 2; Toint.length() > i; i += 2)                                 // We scan the command skipping the first two values to avoid the letter (H or C) itself and start converting the string character by character to an integer
  {
    OutString += (Toint.substring(i, i + 2).toInt() - 48);                        // We extract two values from the string, which correspond to one character and we convert them to an integer, we substract 48 because of the ascii convention
  }
  
  //  Serial.print(OutString);                                                    // For debugging purposes
  
  return OutString.toInt();                                                       // Finally we convert the resulting string, which contains the number in the shape of a string, and we return it as an integer.
}


String SelectedCell ()                                                            // This function scans the serial input, extracts the characters sent to the arduino and returns them as a string 
{
  String CellNum;                                                                 // String that will determine the cell being measured
  CellNum = String("");                                                           // Assign a void value to the string CellNum
  
  delay(50);                                                                      // Small delay to allow for the serial to buffer all the data
  
  if (Serial.available() > 1)                                                     // If there is anything on the serial we will read it and process it
  {
    CellNum = String("");                                                         // Reset CellNum to a blank space before reading
    for (int i = Serial.available(); i > 0; i--)                                  // Take the amount of digits in the serial and read them; i.e if the Serial.available() is 3 it will read the serial 3 times
    {
      CellNum += Serial.read();                                                   // Append the read value to the previous one to form a complete string with all the values from the serial
    }
    //Serial.println(CellNum);                                                    // Print the raw data for development purposes //Comment if not developing
  }
  return (CellNum);                                                               // As this is a function it returns the string of the CellNum that has been selected
}
