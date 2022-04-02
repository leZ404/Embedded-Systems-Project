#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "sonorite.h"

const uint16_t FORMULE = 31250; // =  F_CPU / 2 * PRESCALER

Sonorite::Sonorite()
{
    TCNT1 = 0;
    DDRD = 0xFF;
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << CS12);
    TCCR1B |= (1 << WGM12);
}

void Sonorite::tempsNote(uint16_t compteur)
{
    //OCR1A = compteur;

    // Port D5 en sortie (OC1A)
    // PORTD &= ~(1 << PD4);                                              // Force un 0 au port adjacent

    TCNT1 = 0; //Utilisation de timer1 vu que l'on utilise deja timer0 pour moteur
    OCR1A = compteur;
    TCCR1A |= (1 << COM1A0); // Compare Register
    TCCR1B |= (1 << CS12);   //Prescaler 256
    TCCR1B |= (1 << WGM12);  // Mode CTC (suggerer par le tp9)
    TCCR1C = 0;
}

uint16_t Sonorite::calcul_compteur(uint16_t note)
{
    uint16_t temp = tableFrequence[note - MIN];
    uint16_t compteur = FORMULE / (2 * temp + 2); // formule de fOCnA doc p120 (haredcored parceque les cst ne marchent pas)
    return compteur;
}
void Sonorite::jouerNote(uint8_t note)
{

    uint16_t compteur = calcul_compteur(note);
    tempsNote(note);
}

void Sonorite::arret()
{
    //Nous mettons tout a zero dans l'ordre qu'on les a initiliaser
    DDRD = 0x00;
    TCNT1 = 0;
    OCR1A = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B = 0;
    TCCR1C = 0;
    TIMSK1 = 0;
}

const uint16_t Sonorite::getTableCompteur(uint8_t i) { return tableCompteur[i]; } //geter pour table Compteur (on l utilise pas finalement)