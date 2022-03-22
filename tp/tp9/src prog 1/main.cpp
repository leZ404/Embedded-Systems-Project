/*
Travail : TRAVAIL_PRATIQUE 9
Section # : 02
Équipe # : EQUIPE_NO 3544
Auteurs : Ryan Lahbabi , Zied Kaabi, Ashveer Golam, Omar Bamrim 
Correcteur : Jerome Collin 
*/

#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>


int main()
{
 
  Memoire24CXXX m;
  Print p = Print(); 

   uint16_t emplacement=0x00;
   uint16_t taille = (((uint16_t)p.USART_Receive()) << 8) | p.USART_Receive();


  for (uint16_t i = 2 ; i <  taille ; i++)

  {

    uint8_t donnee = p.USART_Receive();                 

    // PORTB = LUMIERE_VERTE;     // allumer del en vert pour tester le bon fonctionnement de  'USART_Receive'     
    // _delay_ms(3000);            
    m.ecriture(emplacement++, donnee);
    _delay_ms(10);
    //PORTB = LUMIERE_ROUGE;     // allumer del en vert pour tester le bon fonctionnement de  'USART_Receive'      
  }

  
}