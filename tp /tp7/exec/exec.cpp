
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<Moteur.h>

                 // qd j enleve les includes : moteur, delay DDRB, DDRD not declared in this scope
int main()         // qd je met les includes : <Moteur.h> ,"Moteur.cpp" no such file or directory 
{
    Moteur moteur(PB3,PB4);
    DDRB |= 0xff;
    DDRD |= 0x00;


    while (true)
    {
    moteur.ajustementPwmNavigation(50,50);
     /*
     _delay_ms(5000);

    moteur.ajustementPwmNavigation ( 2 , 2);
    _delay_ms(5000);
   moteur.ajustementPwmNavigation(100,100);
     _delay_ms(5000);

*/
    }
}