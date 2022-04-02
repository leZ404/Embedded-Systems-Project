#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>

class Bouton
{
public:
    Bouton()
    {
        DDRA |= 0x00;
    };
    //~Bouton();

    bool appuiBouton(uint8_t pinBouton);

};
