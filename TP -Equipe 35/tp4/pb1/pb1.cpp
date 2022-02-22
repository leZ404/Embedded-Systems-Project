#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum class Etat
{
    ETEINT,
    VERT,
    ROUGE,
};

volatile bool bouttonappuie = false;
volatile Etat etatCourant = Etat::ROUGE;
const int LUMIERE_ETEINTE = 0x00;
const int LUMIERE_ROUGE = (1 << PA1);
const int LUMIERE_VERTE = (1 << PA0);

bool appuiBouton(uint8_t pinBouton)
{
    const uint8_t DELAIS_ANTIREBOND = 10;

    if (PIND & (1 << pinBouton))
    {
        _delay_ms(DELAIS_ANTIREBOND);
        if (PIND & (1 << pinBouton))
        { // traitement de l'anti-rebond dans la fonction.
            return true;
        }
        return false;
    }
}


ISR(INT0_vect)
{

 appuiBouton(PD2);

    
    _delay_ms(30);
    // In SimulIde the next line must be commented to work, but with the robot must be uncommented
    //if (PIND & (1 << PD2)) // Comment this line in SimulIde
    //{

    switch (etatCourant)
    {
        // PORTA &= ~((1 << PA0) | (1 << PA1)); //...  if ((appuiBouton(PIND2))
        // PORTA |= bouttonappuie ? (1 << PA0) : (1 << PA1);
    case Etat::ROUGE:
        PORTA = LUMIERE_ROUGE;

        if (bouttonappuie == true)
        {
            etatCourant = Etat::VERT;
            bouttonappuie = false;
        }

        break;
    case Etat::VERT:
        PORTA = LUMIERE_VERTE;

        if (bouttonappuie == true)
        {
            etatCourant = Etat::ETEINT;
            bouttonappuie = false;


        }

        break;

    case Etat::ETEINT:
        PORTA = LUMIERE_ETEINTE;

        if (bouttonappuie == true)
        {
            etatCourant = Etat::ROUGE;
            bouttonappuie = false;

            

        }
        break;
    }

bouttonappuie = (!bouttonappuie);
EIFR |= (1 << INTF0);
}


void initialisationInt0()
{

    cli();
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01) | (1 << ISC00); // raising edge
    sei();
}

int main()
{

    initialisationInt0();

    DDRA = 0xff;
    DDRD = 0x00;

    while (true)
    {
    }
}
