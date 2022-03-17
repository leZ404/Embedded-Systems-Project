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
  DDRB= 0xff;
  Memoire24CXXX m;
  Print p; 
  uint8_t byte1 = p.USART_Receive();
  uint8_t byte2 = p.USART_Receive();
  uint16_t taille = byte1;
  taille = taille << 8;
  taille |= byte2;


  for (uint8_t i = 1 ; i < taille ; i++)
  {
    uint8_t donne =p.USART_Receive();
    m.ecriture(i,donne);
    PORTB = 1;
  }
      PORTB = 0;



  //m.ecriture(0,x);
  
  
  //p.USART_Init()   // faut trouver le param (voir discord)

  // unsigned char c ='k' ; 

 // const char * str = "This is a string literal. See the double quotes?";

  //p.afficherChaineCaractere(str);

  //p.afficherCaractere(c);


}
