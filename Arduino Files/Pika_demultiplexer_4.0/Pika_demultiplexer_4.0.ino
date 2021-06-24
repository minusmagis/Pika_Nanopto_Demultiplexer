/*
    Nanopto Pika Demultiplexer Time Saver developed for the Nanopto group at ICMAB by Martí Gibert Roca as part of his PhD thesis in 2021
    This programme is used to control a demultiplexer of 24-1 channels.
    It needs a specific pcb design that can be found at https://github.com/minusmagis/Pika_Nanopto_Demultiplexer, for more questions contact minusmagis@gmail.com
*/

#include "Definitions.h"

// The Start setup sets the needed pins as outputs. It also starts the Serial Comunication protocol and sends an identification message so that we can identify this arduino.

void setup()
{
Start_Setup();
}

// The main loop waits for an input within the serial connection and when provided with one evaluates if it fits within the available commands.
// Whenever feeded a valid comand the loop executes the corresponding function.

void loop()
{
 Get_Command();
 Command_Analyzer(); 
}
