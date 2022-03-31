#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//uint8_t  Moteur::sVariable = X;

class MoteurRoueDroite
{

public:

MoteurRoueDroite(uint8_t pinDirectionDroite);
   


void avancer(uint8_t valPWM); // Prend la valeur PWM


void reculer(uint8_t valPWM); // Prend la valeur PWM


void arret();


void ajustementPwmNavigation(uint8_t pourcentageRoueDroite);


private:

 uint8_t _directionDroite; 

 };