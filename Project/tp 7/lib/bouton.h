#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>

class Bouton
{
public:
    Bouton()
    {
        DDRD |= 0x00;
    };
    //~Bouton();

    bool appuiBouton(uint8_t pinBouton);

};
