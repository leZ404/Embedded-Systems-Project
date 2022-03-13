#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>



class Print 
{
public:
Print();
~Print();
void USART_Init( const int baud );
void afficherCaractere( unsigned char data );
void afficherChaineCaractere( const char* data, int length );
void afficherChaineCaractere2(const char* data);



private:



};