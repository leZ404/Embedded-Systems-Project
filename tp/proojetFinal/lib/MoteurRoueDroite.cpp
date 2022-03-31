#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <MoteurRoueDroite.h>

//uint8_t  Moteur::sVariable = X;

const uint8_t MAX_PWM = 255; // valeur maximale qu'un registre peut avoir
MoteurRoueDroite::MoteurRoueDroite(uint8_t pinDirectionDroite)
    : _directionDroite(pinDirectionDroite)
{
    DDRB |= (1 << _directionDroite) |  (1 << PB3) ;
}
void MoteurRoueDroite::avancer(uint8_t valPWM) // Prend la valeur PWM
{
    PORTB = 0;
    PORTB = 0;
    OCR0A = valPWM; //0-255
    PORTB &= ~(1 << _directionDroite);
    

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};

void MoteurRoueDroite::reculer(uint8_t valPWM) // Prend la valeur PWM
{
    PORTB = 0;
    PORTB = 0;
    OCR0A = valPWM; //0-255
    PORTB |= ~(1 << _directionDroite);
    

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};
void MoteurRoueDroite::arret()
{
    OCR0A = 0;

};

void MoteurRoueDroite::ajustementPwmNavigation(uint8_t pourcentageRoueDroite)
{

    OCR0A = pourcentageRoueDroite * MAX_PWM / 100; // comme on procede en pourcentage on devrait diviser par 100 vu que OCR0X= 255 est un rendement de 100%
    

    TCNT0 = 0;
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01);
};
