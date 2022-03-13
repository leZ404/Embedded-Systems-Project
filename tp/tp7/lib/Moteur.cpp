#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <Moteur.h>

//uint8_t  Moteur::sVariable = X;
// OC0A - pb 3 roue gauche pin direction pb2
// OC0B - pb 4 roue droite pin direction
const uint8_t MAX_PWM = 255; // c est plus correcte de la declarer comme cst que comme DEFINE

Moteur::Moteur(uint8_t pinDirectionDroite, uint8_t pinDirectionGauche)
    : _directionDroite(pinDirectionDroite), _directionGauche(pinDirectionGauche)
{
    DDRB |= (1 << _directionDroite) | (1 << _directionGauche) | (1 << PB3) | (1 << PB4);
}

void Moteur::avancer()

{
    OCR0A = MAX_PWM;
    OCR0B = MAX_PWM;
    PORTB &= ~(1 << _directionDroite);
    PORTB &= ~(1 << _directionGauche);
};

// E=1 / D = 0

void Moteur::reculer()
{
    OCR0A = MAX_PWM;
    OCR0B = MAX_PWM;
    PORTB |= (1 << _directionDroite);
    PORTB |= (1 << _directionGauche);
};

// E = 0 / D= X
void Moteur::arret()
{
    OCR0A = 0;
    OCR0B = 0;
};

void Moteur::ajustementPwmNavigation(uint8_t pourcentageRoueDroite, uint8_t pourcentageRoueGauche)
{

    OCR0A = pourcentageRoueDroite * MAX_PWM / 100; // peut on conserver le 100 comme chiffre magique
    OCR0B = pourcentageRoueGauche * MAX_PWM / 100;

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};
