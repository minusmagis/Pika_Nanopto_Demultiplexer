/* 
 *  Master thesis arduino Nanopto time saver
 *  This programme is used to control a demultiplexer of 24-1 channels. 
 *  It needs a specific pcb design, for more questions contact minusmagis@gmail.com
 *  
 */


/*
 * Pins to be connected: 
 * Arduino pins:
 * 2,3,4,5,(6,A5),(7,A4,A3)
 * to PCB set:
 * 0,1,2,3,(4),(5)
 * 
 * Arduino pins:
 * (9,A0,A1),(10,A2),11,12,13,14(GND)
 * to PCB Reset:
 * (5),(4),3,2,1,0
 */
 
String Cell; //String that will determine which cell is being measured
String CellCode; //String that holds the entire code of each cell
String CellLabel; //String that will be the name of the cell
String CellBit; //The bitcode of each cell
  int Bit0 = 0; // Ground Bit, it will always be zero
  int Bit1 = 0; //Bits that will determine the signal emitted to the arduino, hence the cell that will be connected
  int Bit2 = 0;
  int Bit3 = 0;
  int Bit4 = 0;
  int Bit5 = 0;
  int NotBit1 = 0; // stores the values of the reset pins
  int NotBit2 = 0;
  int NotBit3 = 0;
  int NotBit4 = 0;
  int NotBit5 = 0;

void setup() 
{
  for(int pin = 3; pin < 14; pin++)
  {
    pinMode(pin,OUTPUT);              //Defines pins from 2 to 13 as an output
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
    
  Serial.begin(9600);                 // Begins Serial communication
}

void loop() 
{
  if (Serial.available() > 0)    // If the serial is trying to communicate calls the functiond SelectedCell() stated below and
  {
Serial.println("-----------------------------------------------");  // print a dashed line  
Cell = SelectedCell();                // assigns its value to the string Cell that will determine which cell is being measured
if(Cell.length() > 3)
{
CellCode = SelectedCellName(Cell);   // Calls the function of Selected CellName that will output the label of the cell as well as the bitstring needed to contact that specific cell
//Serial.print("Plain data from serial = ");
//Serial.println(Cell);                 // Prints the cell that is being read
CellLabel = CellCode.substring(5);      // Assign the label of the cell being read to the variable CellLabel
CellBit = CellCode.substring(0,5);      // Assign the binary code of the cell being read to the variable CellBit

if (CellCode != "")                    // If there is data in the CellCode
{
  Serial.print("Cell Label =  ");      //Print "Cell Label = " 
  Serial.print(CellLabel);             // Print the cell label i.e L14
  Serial.print("     Cell binary code = ");  // Print "        Cell binary code ="
  Serial.println(CellBit);                   // Print the binary code associated with the cell being read
  Serial.println("-----------------------------------------------");  // print a dashed line
  Bit1 = ReadBit(CellBit,1);   //Assign the value of the first bit from the bitcode to a variable Bit1
  Bit2 = ReadBit(CellBit,2);   //Assign the value of the second bit from the bitcode to a variable Bit2
  Bit3 = ReadBit(CellBit,3);   //Assign the value of the third bit from the bitcode to a variable Bit3
  Bit4 = ReadBit(CellBit,4);   //Assign the value of the forth bit from the bitcode to a variable Bit4
  Bit5 = ReadBit(CellBit,5);   //Assign the value of the fifth bit from the bitcode to a variable Bit5
  NotBit1 = invert(Bit1);      //Use the function invert to generate the complementary values from BitX values
  NotBit2 = invert(Bit2);
  NotBit3 = invert(Bit3);
  NotBit4 = invert(Bit4);
  NotBit5 = invert(Bit5);
  Serial.print(Bit1);       //Troubleshooting to see if BitX values are actually a binary value and to see if the complementary are really complementary
  Serial.println(NotBit1);  // If it is a zero on the right it should be a one on the left 
  Serial.print(Bit2);
  Serial.println(NotBit2);
  Serial.print(Bit3);
  Serial.println(NotBit3);
  Serial.print(Bit4);
  Serial.println(NotBit4);
  Serial.print(Bit5);
  Serial.println(NotBit5);
  digitalWrite(2,LOW);         //The pin 0 reset and set is always ground in this case on corresponds to pin 14 and the other to pin 2 on the arduino, pin 14 is ground by default in arduino
  digitalWrite(13,Bit1);      //Write the value of BitX (etither 0 or 1) to each pin on the arduino to contact the cell
  digitalWrite(3,NotBit1);
  digitalWrite(12,Bit2);
  digitalWrite(4,NotBit2);
  digitalWrite(11,Bit3);
  digitalWrite(5,NotBit3);
  digitalWrite(10,Bit4);
  digitalWrite(A2,Bit4);
  digitalWrite(6,NotBit4);
  digitalWrite(A5,NotBit4);
  digitalWrite(9,Bit5);
  digitalWrite(A0,Bit5);
  digitalWrite(A1,Bit5);
  digitalWrite(7,NotBit5);
  digitalWrite(A3,NotBit5);
  digitalWrite(A4,NotBit5);
  delay(100);
  for(int i = 2; i<14; i++)
  {
    digitalWrite(i,LOW);
  }
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
  
  }
 }
}
}

int invert(int value)
{
  int Buffer = 0; //Buffer value that will be used in the function
  if (value == 1 || value == 0)  //Only perform the function if the input values are binary
  {
    Buffer = (value-1)*(value-1);  // transforms a 0 into a 1 and viceversa
  }
  else 
  {
  Serial.println("Error in the bitcode"); //If the value is not binary output an error
  }
  return(Buffer);  // Return the inverted value
}

int ReadBit (String BitCode,int BitNum)
{
  int Bit = 0;
  String Buffer = String("");
  Buffer = BitCode.substring((BitNum-1),BitNum);
  Bit = Buffer.toInt();
  return(Bit);
}

String SelectedCellName(String CellName)
{
  String Output = String("");
  delay(100);
  String CellLbl = String("");
  String bitString = String("");

  
  if (CellName == "11449" || CellName == "8249")
  {
    CellLbl = String("R1");
    bitString = String("11001");
  }
  else if (CellName == "11450" || CellName == "8250")
  {
    CellLbl = String("R2");
    bitString = String("11000");
  }
  else if (CellName == "11451" || CellName == "8251")
  {
    CellLbl = String("R3");
    bitString = String("11010");
  }
  else if (CellName == "11452" || CellName == "8252")
  {
    CellLbl = String("R4");
    bitString = String("11011");
  }
  else if (CellName == "11453" || CellName == "8253")
  {
    CellLbl = String("R5");
    bitString = String("10011");
  }
  else if (CellName == "11454" || CellName == "8254")
  {
    CellLbl = String("R6");
    bitString = String("10010");
  }
  else if (CellName == "11455" || CellName == "8255")
  {
    CellLbl = String("R7");
    bitString = String("10000");
  }
  else if (CellName == "11456" || CellName == "8256")
  {
    CellLbl = String("R8");
    bitString = String("10001");
  }
  else if (CellName == "11457" || CellName == "8257")
  {
    CellLbl = String("R9");
    bitString = String("10101");
  }
  else if (CellName == "1144948" || CellName == "824948")
  {
    CellLbl = String("R10");
    bitString = String("10100");
  }
  else if (CellName == "1144949" || CellName == "824949")
  {
    CellLbl = String("R11");
    bitString = String("10110");
  }
  else if (CellName == "1144950" || CellName == "824950")
  {
    CellLbl = String("R12");
    bitString = String("10111");
  }
  else if (CellName == "10849" || CellName == "7649")
  {
    CellLbl = String("L1");
    bitString = String("11111");
  }
  else if (CellName == "10850" || CellName == "7650")
  {
    CellLbl = String("L2");
    bitString = String("11110");
  }
  else if (CellName == "10851" || CellName == "7651")
  {
    CellLbl = String("L3");
    bitString = String("11100");
  }
  else if (CellName == "10852" || CellName == "7652")
  {
    CellLbl = String("L4");
    bitString = String("11101");
  }
  else if (CellName == "10853" || CellName == "7653")
  {
    CellLbl = String("L5");
    bitString = String("00011");
  }
  else if (CellName == "10854" || CellName == "7654")
  {
    CellLbl = String("L6");
    bitString = String("00010");
  }
  else if (CellName == "10855" || CellName == "7655")
  {
    CellLbl = String("L7");
    bitString = String("00000");
  }
  else if (CellName == "10856" || CellName == "7656")
  {
    CellLbl = String("L8");
    bitString = String("00001");
  }
  else if (CellName == "10857" || CellName == "7657")
  {
    CellLbl = String("L9");
    bitString = String("01001");
  }
  else if (CellName == "1084948" || CellName == "764948")
  {
    CellLbl = String("L10");
    bitString = String("01000");
  }
  else if (CellName == "1084949" || CellName == "764949")
  {
    CellLbl = String("L11");
    bitString = String("01010");
  }
  else if (CellName == "1084950" || CellName == "764950")
  {
    CellLbl = String("L12");
    bitString = String("01011");
  }
  else
  {
    Serial.println("Value not valid, it should be something like L12"); 
    Serial.println("where L means left side and 12 is the number of the cell");
    Serial.println("The range goes from 1 to 12, and left or right can be choosen");
  }
  Output = bitString;
  Output += CellLbl;
  return (Output);
}

String SelectedCell ()
{
  String CellNum;                                                  // String that will determine the cell being measured
  CellNum = String("");                                            // Assign a void value to the string CellNum
     delay(300);                                                   //Small delay to allow for the serial to buffer all the data
        if (Serial.available() == 2 || Serial.available() == 3)    // If there are in the serial 2 or 3 values (L12 counts as 3 and R1 counts as 2 values) read the seria, otherwise (see else if)
        {  
                CellNum = String("");                          //Reset CellNum to a blank space before reading
                for(int i = Serial.available();i>0;i--) // Take the amount of digits in the serial and read them; i.e if the Serial.available() is 3 it will read the serial 3 times
                {
                CellNum += Serial.read(); // Append the read value to the previous one to form a complete string with all the values from the serial 
                }
        }
        else if (Serial.available()>3) // If the serial input is a string with more than 3 digits it is not aa valid input
        {
           Serial.println("Incorrect value format introduced :( ");  //Print that is not a valid input
           Serial.println("Probably too long, max 3 characters needed");
           Serial.println("Example L12");
           for(int i = Serial.available() ;i>0;i--)          //Measures the length of the input string 
                {
                Serial.read();    // Reads all throughout the length of the string to flush the serial input and leave it to zero
                }
         // Serial.print("Comprovant hauria de ser 0 = ");    //It is used as a Debugger function to see if the serial input is being really flushed to 0
         // Serial.println(Serial.available());               //It prints it should be zero and afterwards prints the value of the Serial.available() that should be zero if it has been correctly flushed
        }
return (CellNum);     //As this is a function it returns the string of the CellNum that has been selected
}

