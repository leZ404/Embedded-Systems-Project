#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <print.h>


Print::Print()      // constructeur 
{
    // *(this).USART_Init();
}



void Print::USART_Init(const int baud)
{
    /* Set baud rate */
    UBRR0H = (const char)(baud >> 8);
    UBRR0L = (const char)baud;
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
