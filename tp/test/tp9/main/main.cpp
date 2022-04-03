
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
#define CAPTEUR_IR 2
#define DISTANCE_20 320

//Creation des instances de classes
Del del;
Bouton bouton;
Moteur moteur(PB3, PB4);
Print p;
can can;


//variable globale
volatile bool dbt = false;
enum class State
{
    DBT = 0x01,
    ATT = 0x02,
    DAL = 0x44,
    DET = 0x45,
    SGO = 0x48,
    SAR = 0x09,
    MAR = 0x60,
    MAR_AUTRE = 0x61,
    MAV = 0x62,
    MRE = 0x63,
    TRD = 0x64,
    TRG = 0x65,
    DBC = 0xC0,
    FBC = 0xC1,
    FIN = 0xFF,
};

void modeParcours()
{
    if (bouton.appuiBouton(PA0))
    {
        del.clignoter(15, LUMIERE_ROUGE);
        //return true;
        dbt = true;
    }
    //return false;
}

bool testCapteurIR()
{
    if (can.lecture(CAPTEUR_IR) > DISTANCE_20) //valeur ~20cm = 320 pour le capteur
    {
        del.SetCouleurLumiere(Etat::ROUGE);
        return true;
    }
    del.SetCouleurLumiere(Etat::VERT);
    return false;
}

ISR(INT0_vect)
{
    //del.clignoter(15, LUMIERE_ROUGE);
    modeParcours();
    EIFR |= (1 << INTF0);
}

void initialisationInt0()
{

    cli();
    DDRA &= ~(1 << PA0);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01) | (1 << ISC00); // raising edge
    sei();
}

int main()
{
    
    initialisationInt0();
    while (true)
    {

        if (dbt)
        {
            //mode parcours
            del.clignoter(15, LUMIERE_VERTE);
            dbt = !dbt;
        }
        del.SetCouleurLumiere(Etat::ROUGE);
    }
}