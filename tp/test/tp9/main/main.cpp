
#define F_CPU 8000000UL
#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>
#include <Moteur.h>
#include <DEL.h>
#include <sonorite.h>
#include <bouton.h>
#include <can.h>

//Define des valeurs
#define IR 2
#define DISTANCE_20 320

//Creation des instances de classes
Del del;
Bouton bouton;
Moteur moteur(PB3, PB4);
Print p;
can can;

void modeParcours()
{
    if (bouton.appuiBouton(PA0))
    {
        del.clignoter(15, LUMIERE_ROUGE);
    }
}


int main()
{

    while (true)
    {
        modeParcours();

        //p.afficherEntier16bit(can.lecture(2));
        if (can.lecture(IR) > DISTANCE_20)              //valeur ~20cm = 320 pour le capteur
        {
            del.SetCouleurLumiere(Etat::ROUGE);
        }
        else
        {
            del.SetCouleurLumiere(Etat::VERT);
        }
        _delay_ms(300);
        

    }
}