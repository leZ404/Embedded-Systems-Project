#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>



class Print 
{
public:
USART_Init( unsigned int baud );
afficherCaractere( unsigned char data );
afficherChaineCaractere(  string data );



private:



};