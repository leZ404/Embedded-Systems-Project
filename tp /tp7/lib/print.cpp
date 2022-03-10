#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<print.h>

void Print::USART_Init( unsigned int baud )
{
/* Set baud rate */
UBRRnH = (unsigned char)(baud>>8);
UBRRnL = (unsigned char)baud;
/* Enable receiver and transmitter */
UCSRnB = (1<<RXENn)|(1<<TXENn);
/* Set frame format: 8data, 2stop bit */
UCSRnC = (1<<USBSn)|(3<<UCSZn0);
}

void Print::USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRnA & (1<<UDREn)) )
;
/* Put data into buffer, sends the data */
UDRn = data;
}