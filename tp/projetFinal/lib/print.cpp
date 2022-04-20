#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <print.h>



Print::Print() // constructeur
{
    USART_Init();
}

void Print::USART_Init()
{

    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void Print::afficherCaractere(const char donnees)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;

    UDR0 = donnees;
}

void Print::afficherChaineCaractere(const char *donnees)
{
    uint8_t index = 0;
    while (donnees[index] != '\0')
    {
        afficherCaractere(donnees[index]);
        index++;
    }
};

uint8_t Print::USART_Receive()
{

    while (!((UCSR0A) & (1 << RXC0)))
        ;

    return UDR0;
}

void Print::USART_Transmit(uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void Print::afficherEntier8bit(uint8_t donnees)
{
    char temp[10];
    sprintf(temp, "%d", donnees);
    afficherChaineCaractere(temp);
}

void Print::afficherEntier16bit(uint16_t donnees)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = donnees;
}