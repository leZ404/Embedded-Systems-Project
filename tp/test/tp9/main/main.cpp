
#define F_CPU 8000000UL
#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "memoire_24.h"
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

const uint16_t DBT = 0x01;
const uint16_t ATT = 0x02;
const uint16_t DAL = 0x44;
const uint16_t DET = 0x45;
const uint16_t SGO = 0x48;
const uint16_t SAR = 0x09;
const uint16_t MAR = 0x60;
const uint16_t MAR_AUTRE = 0x61;
const uint16_t MAV = 0x62;
const uint16_t MRE = 0x63;
const uint16_t TRD = 0x64;
const uint16_t TRG = 0x65;
const uint16_t DBC = 0xC0;
const uint16_t FBC = 0xC1;
const uint16_t FIN = 0xFF;

void modeParcours()
{

    del.clignoter(15, LUMIERE_VERTE);

    dbt = true;
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

void retirerInt0()
{
    EIMSK = 0x00;
    EICRA = 0x00;
}

//Test de l'ecriture et lecture des instructions en memoire

//Concepte de notre code
int main()

{

    Memoire24CXXX memoire;
    uint16_t adresseMemoire = 0;
    uint8_t donne = 0;
    memoire.ecriture(0, donne++);
    _delay_ms(5);
    p.afficherChaineCaractere("Ecriture fait");
    
    memoire.lecture(adresseMemoire, &donne);
    _delay_ms(5);
    p.afficherChaineCaractere("Lecture fait");
    p.afficherEntier8bit(donne);
}

// uint8_t tableau[255];

// for (uint8_t i = 0 ; i < 255 ; i++)
// {

// }

// moteur.ajustementPwmNavigation(100,100);