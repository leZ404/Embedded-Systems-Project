#define F_CPU 8000000UL
#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>
#include <moteur.h>
#include <DEL.h>
#include <sonorite.h>
#include <bouton.h>

/*Boucle de démarrage:
Bouton Interrupt pour le mode parcours, bouton blanc pour le mode reprise. Lorsqu'un bouton est appuyé, 
le choix est confirmé à l'aide de la DEL libre. Elle devra clignoter à 5 Hz pendant 3 secondes. 
En vert pour le mode suivi, en rouge pour le mode reprise.
Le robot ne fait rien d'autre pendant le clignotement. Une fois ce dernier terminé, le robot passe au mode d'opération choisi.
*/


//routine d'interruption<s
volatile bool bouttonappuie = false;
ISR(INT0_vect)
`{

    _delay_ms(30);
    bouttonappuie = true;
    EIFR |= (1 << INTF0);
    //inserer fonction mode reprise
}

//routine d'initialisation
void initialisationInt0()
{

    cli();
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01) | (1 << ISC00); // raising edge

    sei();
}



/Fin Boucle de démarrage:/

/avancement des roues en fonction des photoresistance

//Appuyer sur un bouton
Del del;
Bouton bouton;



void clignoter(uint8_t nbFois, const int lumiere)
{
    for (int i = 0; i < nbFois; i++)
    {
        PORTB = lumiere;
        _delay_ms(250);
        PORTB = 0x00;
        _delay_ms(250);
    }
}



int main()
{
    
    while (true)
    {
        //Boucle de démarrage, Mode Suivi:
        if (bouton.appuiBouton(PA0))
        {
            del.clignoter(15, LUMIERE_VERTE);
        }
        //Fin Boucle demarrage, Mode Suivi

        initialisationInt0();
        //Boucle de démarrage, Mode reprise:
        if (bouttonappuie == true && compteur < 120)
        {
            compteur++;
            _delay_ms(100); // 1/10 secondes , t = 0 compteur=1 --> t= 0.1secondes compteur= 1
            del.clignoter(15, LUMIERE_ROUGE);
        }


        // //Boucle de démarrage, Mode Reprise
        //  if (bouton.appuiBouton(PA0))
        // {
            
        // }
    }
   
}