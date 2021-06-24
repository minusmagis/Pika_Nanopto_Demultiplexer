// This script declares the pin mode for each pin and starts the serial communications

void Start_Setup()
{
  for (int pin = 2; pin <= 19; pin++)       //First we define all pins as outputs
  {
    pinMode(pin, OUTPUT);                         // Defines pins from 2 to A5 as an output
  }

  Serial.begin(9600);                             // We begin Serial communication
  Serial.println("Arduino Multiplexer Pika");     // We also print a welcome message so that we know which arduino we are talking to
}


// This function displays a small help so that the user can easily understand the commands to send
void Help() {
  Serial.println();
  Serial.println("Label commands: Left or Right from 01 to 12 (R.01 , L.07 , R.12)");
  Serial.println("Test command: Performs a sweep over the whole range of connections (Test, test)");
  Serial.println();
}
