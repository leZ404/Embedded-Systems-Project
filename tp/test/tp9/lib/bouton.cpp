#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <bouton.h>
bool Bouton::appuiBouton(uint8_t pinBouton)
{

    const uint8_t DELAIS_ANTIREBOND = 10;

    if (PINA & (1 << pinBouton))
    {
        _delay_ms(DELAIS_ANTIREBOND);
        if (PINA & (1 << pinBouton))
        { // traitement de l'anti-rebond dans la fonction.
            return true;
        }
        return false;
    }
}
