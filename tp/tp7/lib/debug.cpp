//Inclure debug.h
#include 'debug.h'

#define printf(args) custom_rs232_printf args

// Utilisation:
char myString[] = "Test";
printf(("My string %s", myString));