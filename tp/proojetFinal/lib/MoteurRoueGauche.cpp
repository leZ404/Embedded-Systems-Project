#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <MoteurRoueGauche.h>

//uint8_t  Moteur::sVariable = X;

const uint8_t MAX_PWM = 255; // valeur maximale qu'un registre peut avoir
MoteurRoueGauche::MoteurRoueGauche(uint8_t pinDirectionGauche)
    : _directionGauche(pinDirectionGauche)
{
    DDRB |= (1 << _directionGauche) |  (1 << PB4) ;
}
void MoteurRoueGauche::avancer(uint8_t valPWM) // Prend la valeur PWM
{
    PORTB = 0;
    PORTB = 0;
    OCR0B = valPWM; //0-255
    PORTB &= ~(1 << _directionGauche);
    

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};

void MoteurRoueGauche::reculer(uint8_t valPWM) // Prend la valeur PWM
{
    PORTB = 0;
    PORTB = 0;
    OCR0B = valPWM; //0-255
    PORTB |= ~(1 << _directionGauche);
    

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};
void MoteurRoueGauche::arret()
{
    OCR0B = 0;

};

void MoteurRoueGauche::ajustementPwmNavigation(uint8_t pourcentageRoueGauche)
{

    OCR0B = pourcentageRoueGauche * MAX_PWM / 100; // comme on procede en pourcentage on devrait diviser par 100 vu que OCR0X= 255 est un rendement de 100%
    

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};
