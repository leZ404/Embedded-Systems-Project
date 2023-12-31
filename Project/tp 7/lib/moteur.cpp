#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <moteur.h>

//uint8_t  Moteur::sVariable = X;

const uint8_t MAX_PWM = 255; // valeur maximale qu'un registre peut avoir
Moteur::Moteur(uint8_t pinDirectionDroite, uint8_t pinDirectionGauche)
    : _directionDroite(pinDirectionDroite), _directionGauche(pinDirectionGauche)
{
    DDRB |= (1 << _directionDroite) | (1 << _directionGauche) | (1 << PB3) | (1 << PB4);
}
void Moteur::arret()
{
    OCR0A = 0;
    OCR0B = 0;
};

void Moteur::ajustementPwmNavigation(uint16_t valRoueDroite, uint16_t valRoueGauche)
{
    PORTB = 0;

    OCR0A = valRoueDroite; // comme on procede en pourcentage on devrait diviser par 100 vu que OCR0X= 255 est un rendement de 100%
    OCR0B =  valRoueGauche;

   
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};

