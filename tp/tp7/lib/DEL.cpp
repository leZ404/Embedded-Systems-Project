#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<DEL.h>



Del::Del()
{
    DDRB |= 0xff;
}



void Del::SetCouleurLumiere(Etat etat)
{
        if (etat == Etat::ETEINT) { 
            PORTB |= LUMIERE_ETEINTE;
            }
            else if (etat == Etat::VERT)
            { 
                PORTB |= LUMIERE_VERTE;
            }
             else if (etat == Etat::ROUGE)
            { 
               PORTB  |=LUMIERE_ROUGE; 
            }
}


void Del::clignoter( uint8_t nbFois,  const uint8_t Couleurlumiere)
{
    for (int i=0 ; i< nbFois ; i++){
        PORTB|= Couleurlumiere;
        _delay_ms(250);
        PORTB |=0x00;
        _delay_ms(250);
    }

}
