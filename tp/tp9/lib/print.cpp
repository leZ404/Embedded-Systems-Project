#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <print.h>


Print::Print()      // constructeur 
{
    USART_Init();
}




void Print::USART_Init()
{
    /* Set baud rate */
    
UBRR0H = 0;

UBRR0L = 0xCF;
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void Print::afficherCaractere( const char donnees)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = donnees;

}


void Print::afficherChaineCaractere(const char *donnees)
{
    uint8_t index = 0;
    while (donnees[index] != '\0')
    {
        afficherCaractere(donnees[index]);
    }
};



unsigned char Print::USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}

