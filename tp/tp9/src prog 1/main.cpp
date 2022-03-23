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
uint8_t donnee; 
   uint16_t emplacement=0x00;
   uint8_t first_half = p.USART_Receive();
   m.ecriture(emplacement++, first_half);    // on a oublier de faire l ecriture des 2 premiers octets pour le push d'avant (ce qui explique le comportement instable du robot)
   uint8_t second_half = p.USART_Receive();
   m.ecriture(emplacement++, second_half);  // on a oublier de faire l ecriture des 2 premiers octets pour le push d'avant (ce qui explique le comportement instable du robot)
   uint16_t taille = (((uint16_t)first_half << 8) | second_half);



  for (uint16_t i = 2 ; i <  taille ; i++)

  {

    donnee = p.USART_Receive();                 

    // PORTB = LUMIERE_VERTE;            // allumer del en vert pour tester le bon fonctionnement de  'USART_Receive'     
    // _delay_ms(3000);            
    m.ecriture(emplacement++, donnee);
    _delay_ms(10);
    //PORTB = LUMIERE_ROUGE;            // allumer del en vert pour tester le bon fonctionnement de  'USART_Receive'      
  }

  
}