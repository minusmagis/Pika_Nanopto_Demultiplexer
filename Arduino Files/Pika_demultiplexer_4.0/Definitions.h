/*
 * This file contains all the definitions for constants used throughout all the subroutines
 */

// We define the time we want the test run to stay within each LED (in milliseconds)
#define Test_Delay_1 200

// We define the time we want the test run to stay within each LED (in milliseconds)
#define Test_Delay_2 50

// We define (or not) a debugging variable to force some printouts for debugging the software
//#define Debugging 0

// We define which board version are we using
#define Board_Version 3

// We define the Delay for the Relay actuation, so that the relays have time to change from one to the next (in milliseconds)
// In case we are debugging we set the delay for a much longer time to properly diagnose the board
#if defined Debugging
  #define Relay_Delay 200
#else
  #define Relay_Delay 50
#endif
