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
  m.ecriture(0,byte1);
  //uint16_t temp = byte1 << 8;
  
  uint8_t byte2 = p.USART_Receive();
  m.ecriture(1,byte2);
  uint16_t taille = byte1;
  taille = taille << 8;
  taille |= byte2;



  for (uint8_t i = 2 ; i <  taille ; i++)
  {
    uint8_t donne=0;
     donne =p.USART_Receive();                 
     PORTB= (1 << PB0);                  
    _delay_ms(3000);
    uint8_t temp =0;
     temp = m.ecriture(i,donne);
     if(temp=!0)       // allumer del rouge pour tester si la fonction ecriture marche bien ( cest bien le cas)
     {
    PORTB= (1 << PB1);
    _delay_ms(3000);
     }

    PORTB = 0;
    _delay_ms(3000);
  }
    PORTB = 0;
    



  //m.ecriture(0,x);
  
  
  //p.USART_Init()   // faut trouver le param (voir discord)

  // unsigned char c ='k' ; 

 // const char * str = "This is a string literal. See the double quotes?";

  //p.afficherChaineCaractere(str);

  //p.afficherCaractere(c);


}
