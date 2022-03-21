#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>

int main()
{
  DDRD= 0xff;
  DDRB= 0xff;
  Memoire24CXXX m;
  Print p;
  uint8_t i = 0;
  uint8_t donne = p.USART_Receive();

  while(donne != 0xff) {
    donne = p.USART_Receive();
    m.ecriture(i,donne);
    i++;
  }
  
}