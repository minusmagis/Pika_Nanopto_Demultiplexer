/*
    Master thesis arduino Nanopto time saver
    This programme is used to control a demultiplexer of 24-1 channels.
    It needs a specific pcb design, for more questions contact minusmagis@gmail.com


    2020 02 20 changes: We changed the pins to add cooling and heating capabilities. Now pin 9 and 10 will be used to drive an h bridge that will cool or heat the sample.
    Remember to send the data witout line ending!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  (otherwise it will not work :3 )

                                                                          READ THE LINE IMMEDIATELY ABOVE

    Old mapping: to new mapping (of the green pcb and on the lower pcb side

    L     R

    L.06  L.10
    L.05  L.09
    L.08  L.12
    L.07  L.11
    R.10  L.03
    R.09  L.04
    R.12  L.01
    R.11  L.02
    R.06  R.03
    R.05  R.04
    R.08  R.01
    R.07  R.02

*/



String Cell; //String that will determine which cell is being measured
String CellLabel; //String that will be the name of the cell
String CellBit; //The bitcode of each cell
uint8_t Bit0 = 0; // Ground Bit, it will always be zero
uint8_t Bit1 = 0; //Bits that will determine the signal emitted to the arduino, hence the cell that will be connected
uint8_t Bit2 = 0;
uint8_t Bit3 = 0;
uint8_t Bit4 = 0;
uint8_t Bit5 = 0;
uint8_t NotBit1 = 0; // stores the values of the reset pins
uint8_t NotBit2 = 0;
uint8_t NotBit3 = 0;
uint8_t NotBit4 = 0;
uint8_t NotBit5 = 0;


#define PWMPin 9
#define HnCPin 10         // hot is Low and cold is high


void setup()
{
  //  Serial.println("Multiplexer and HnC arduino");
  for (uint8_t pin = 2; pin < 14; pin++)
  {
    pinMode(pin, OUTPUT);             //Defines pins from 2 to 13 as an output
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);

  Serial.begin(9600);                 // Begins Serial communication

}

void loop()
{
  if (Serial.available() > 0)    // If the serial is trying to communicate calls the functiond SelectedCell() stated below and
  {
    //    Serial.println("-----------------------------------------------");  // print a dashed line
    Cell = SelectedCell();                // assigns its value to the string Cell that will determine which cell is being measured
    //Serial.println(Cell);
    if (Cell.length() > 3)
    {
      // Calls the function of Selected CellName that will output the label of the cell as well as the bitstring needed to contact that specific cell
      //      Serial.print("Plain data from serial = ");
      CellBit = SelectedCellName(Cell);      // Assign the binary code of the cell being read to the variable CellBit
      //Serial.println(CellBit);                // Prints the cell that is being read
      if (CellBit != "")                    // If there is data in the CellBit
      {
        //        Serial.print("     Cell binary code = ");  // Print "        Cell binary code ="
        //        Serial.println(CellBit);                   // Print the binary code associated with the cell being read
        //        Serial.println("-----------------------------------------------");  // print a dashed line
        Bit1 = ReadBit(CellBit, 1);  //Assign the value of the first bit from the bitcode to a variable Bit1
        Bit2 = ReadBit(CellBit, 2);  //Assign the value of the second bit from the bitcode to a variable Bit2
        Bit3 = ReadBit(CellBit, 3);  //Assign the value of the third bit from the bitcode to a variable Bit3
        Bit4 = ReadBit(CellBit, 4);  //Assign the value of the forth bit from the bitcode to a variable Bit4
        Bit5 = ReadBit(CellBit, 5);  //Assign the value of the fifth bit from the bitcode to a variable Bit5
        NotBit1 = invert(Bit1);      //Use the function invert to generate the complementary values from BitX values
        NotBit2 = invert(Bit2);
        NotBit3 = invert(Bit3);
        NotBit4 = invert(Bit4);
        NotBit5 = invert(Bit5);
        //        Serial.print(Bit1);       //Troubleshooting to see if BitX values are actually a binary value and to see if the complementary are really complementary
        //        Serial.println(NotBit1);  // If it is a zero on the right it should be a one on the left
        //        Serial.print(Bit2);
        //        Serial.println(NotBit2);
        //        Serial.print(Bit3);
        //        Serial.println(NotBit3);
        //        Serial.print(Bit4);
        //        Serial.println(NotBit4);
        //        Serial.print(Bit5);
        //        Serial.println(NotBit5);
        //        Serial.println("-----------------------------------------------");
        //        Serial.println("Please introduce the next cell label you want to measure:");  //Write this message on the serial port so that the use knows that he can change the cell number
        digitalWrite(2, LOW);        //The pin 0 reset and set is always ground in this case on corresponds to pin 14 and the other to pin 2 on the arduino, pin 14 is ground by default in arduino
        digitalWrite(3, Bit1);     //Write the value of BitX (etither 0 or 1) to each pin on the arduino to contact the cell
        digitalWrite(2, NotBit1);
        delay(5);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        delay(5);
        digitalWrite(A4, Bit2);
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
        for (uint8_t i = 2; i < 14; i++) //Write low on every bit to limit current consumption, this is to give more power to the following bits that will require it
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
        for (uint8_t i = 2; i < 14; i++)
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
      //Serial.println("nono");
      Serial.read();
    }
  }
}

uint8_t invert(uint8_t value)
{
  uint8_t Buffer = 0; //Buffer value that will be used in the function
  if (value == 1 || value == 0)  //Only perform the function if the input values are binary
  {
    Buffer = (value - 1) * (value - 1); // transforms a 0 into a 1 and viceversa
  }
  else
  {
  }
  return (Buffer); // Return the inverted value
}

uint8_t ReadBit (String BitCode, uint8_t BitNum)
{
  uint8_t Bit = 1;
  String Buffer = String("");
  Buffer = BitCode.substring((BitNum - 1), BitNum);
  Bit = Buffer.toInt();
  return (Bit);
}



String SelectedCellName(String CellName)
{

  String bitString = String("");
  String HotCold = String("");
  HotCold = CellName.substring(0, 2);

  if (CellName == "82464849")                           //R.01
  {
    bitString = String("10110");                            //R.01
  }
  else if (CellName == "82464850")                          //R.02
  {
    bitString = String("10111");                            //R.02
  }
  else if (CellName == "82464851")                          //R.03
  {
    bitString = String("10101");                            //R.03
  }
  else if (CellName == "82464852")                          //R.04
  {
    bitString = String("10100");                            //R.04
  }
  else if (CellName == "82464853")                          //R.05
  {
    bitString = String("01000");                            //R.05
  }
  else if (CellName == "82464854")                          //R.06
  {
    bitString = String("01001");                            //R.06
  }
  else if (CellName == "82464855")                          //R.07
  {
    bitString = String("01011");                            //R.07
  }
  else if (CellName == "82464856")                          //R.08
  {
    bitString = String("01010");                            //R.08
  }
  else if (CellName == "82464857")                          //R.09
  {
    bitString = String("00010");                            //R.09
  }
  else if (CellName == "82464948")                          //R.10
  {
    bitString = String("00011");                            //R.10
  }
  else if (CellName == "82464949")                          //R.11
  {
    bitString = String("00001");                            //R.11
  }
  else if (CellName == "82464950")                          //R.12
  {
    bitString = String("00000");                            //R.12
  }
  else if (CellName == "76464849")                          //L.01
  {
    bitString = String("10000");                            //L.01
  }
  else if (CellName == "76464850")                          //L.02
  {
    bitString = String("10001");                            //L.02
  }
  else if (CellName == "76464851")                          //L.03
  {
    bitString = String("10011");                            //L.03
  }
  else if (CellName == "76464852")                          //L.04
  {
    bitString = String("10010");                            //L.04
  }
  else if (CellName == "76464853")                          //L.05
  {
    bitString = String("11110");                            //L.05
  }
  else if (CellName == "76464854")                          //L.06
  {
    bitString = String("11111");                            //L.06
  }
  else if (CellName == "76464855")                          //L.07
  {
    bitString = String("11101");                            //L.07
  }
  else if (CellName == "76464856")                          //L.08
  {
    bitString = String("11100");                            //L.08
  }
  else if (CellName == "76464857")                          //L.09
  {
    bitString = String("11000");                            //L.09
  }
  else if (CellName == "76464948")                          //L.10
  {
    bitString = String("11001");                            //L.10
  }
  else if (CellName == "76464949")                          //L.11
  {
    bitString = String("11011");                            //L.11
  }
  else if (CellName == "76464950")                          //L.12
  {
    bitString = String("11010");                            //L.12
  }
  else if (HotCold == "72")                                   // heating
  {
    if (CellName.length() == 8) {
      int PWMSignal = 0;
      //Serial.print("Heating at this power = ");
      PWMSignal = Stringtoint(CellName);
      PWMSignal = constrain(PWMSignal, 0, 255);
      digitalWrite(HnCPin, LOW);                               // Bring the pin low to set it for heating
      delay(10);
      analogWrite(PWMPin, PWMSignal);                          //Write the power at wich you want to heat up
      //Serial.println(PWMSignal);
    }
  }
  else if (HotCold == "67")                                               // Cooling
  {
    if (CellName.length() == 8) {
      int PWMSignal = 0;
      //Serial.print("Cooling at this power = ");
      PWMSignal = Stringtoint(CellName);
      PWMSignal = constrain(PWMSignal, 0, 255);
      digitalWrite(HnCPin, HIGH);                               // Bring the pin high to set it for cooling
      delay(10);
      analogWrite(PWMPin, PWMSignal);                          //Write the power at wich you want to cool down
      //Serial.println(PWMSignal);
    }
  }
  else
  {
    //Serial.println("no");
  }
  return (bitString);
}

int Stringtoint (String Toint) {
  String OutString = String("");
  for (uint8_t i = 2; Toint.length() > i; i += 2)
  {
    OutString += (Toint.substring(i, i + 2).toInt() - 48);
  }
  //  Serial.print(OutString);
  return OutString.toInt();
}

String SelectedCell ()
{
  String CellNum;                                                  // String that will determine the cell being measured
  CellNum = String("");                                            // Assign a void value to the string CellNum
  delay(50);                                                   //Small delay to allow for the serial to buffer all the data
  if (Serial.available() > 1)  // If there are in the serial 2 or 3 values (L12 counts as 3 and R1 counts as 2 values) read the seria, otherwise (see else if)
  {
    CellNum = String("");                          //Reset CellNum to a blank space before reading
    for (int i = Serial.available(); i > 0; i--) // Take the amount of digits in the serial and read them; i.e if the Serial.available() is 3 it will read the serial 3 times
    {
      CellNum += Serial.read(); // Append the read value to the previous one to form a complete string with all the values from the serial
    }
    Serial.println(CellNum);  //Print the raw data for development purposes //Comment if not developing
  }
  return (CellNum);     //As this is a function it returns the string of the CellNum that has been selected
}
