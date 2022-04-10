#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <DEL.h>

const uint8_t DELAIS_CLIGNOTER = 100;  // delai de 200 ms pour pouvir clignoter au rythme de 2 fois par sec

Del::Del()
{
    DDRB |= 0xff;
}



void Del::SetCouleurLumiere(Etat etat)
{
    if (etat == Etat::ETEINT)   
    {
        PORTB = LUMIERE_ETEINTE;       
    }
    else if (etat == Etat::VERT)
    {
        PORTB = LUMIERE_VERTE;
    }
    else if (etat == Etat::ROUGE)
    {
        PORTB= LUMIERE_ROUGE;
    }
}

void Del::clignoter(uint8_t nbFois, const uint8_t Couleurlumiere)
{
    for (uint8_t i = 0; i < nbFois; i++)
    {
        PORTB = Couleurlumiere;
        _delay_ms(DELAIS_CLIGNOTER);
        PORTB = LUMIERE_ETEINTE;
        _delay_ms(DELAIS_CLIGNOTER);
    }
}
