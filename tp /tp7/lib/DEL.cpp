#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<DEL.h>



Del::Del()
{
 DDRB = 0Xff;
}


void Del::SetCouleurLumiere(Etat etat)
{
        if (etat == ETEINT) { 
            _Couleurlumiere = 0x00;
            }
            else if (etat == VERT)
            { 
                _Couleurlumiere = = (1 << PB0);
            }
             else if (etat == ROUGE)
            { 
               _Couleurlumiere = = (1 << PB1); 
            }
}


void Del::clignoter( uint8_t nbFois,  int Couleurlumiere)
{
    for (int i=0 ; i< nbFois ; i++){
        PORTB= Couleurlumiere;
        _delay_ms(250);
        PORTB = 0x00;
        _delay_ms(250);
    }

}
