#define F_CPU 8000000UL
#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>
#include <moteur.h>
#include <DEL.h>
#include <sonorite.h>
#include <bouton.h>
#include <can.h>

enum class Instruction
{
    DEBUTPARCOURS,
    SUIVREMUR,
    ATTENTE,
    MODETOURNER,
    SUIVILUMIERE, 
    FINPARCOURS
};


int main()
{

DDRC = 0xff;
DDRB = 0xff;
DDRA= 0x00;
Moteur moteur(PB5, PB6);
Bouton bouton;
can obstacle;
Del del ;
Print p; 
Memoire24CXXX m;
Bouton b; 
uint16_t AJUSTEMENT_DROIT = 75;
uint16_t AJUSTEMENT_GAUCHE = 150;
uint16_t lumiereDroite=  obstacle.lecture(4);  //photoresistance de droite lumiere.lecture(1)
uint16_t lumiereGauche =  obstacle.lecture(1); //photoresistance de gauche  lumiere.lecture(4)
uint16_t obstacle =  obstacle.lecture(7);
while (true)
    {
    if (b.appuiBouton(PA0)) 
    {     
    del.clignoter(4,LUMIERE_VERTE);
        switch(instruction)
        {
            case Instruction::SUIVREMUR:
            if(obstacle > 320)
            {
                moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
                    _delay_ms(1000);
            }

             case Instruction::ATTENTE:
             case Instruction::MODETOURNER:
             case Instruction::DEBUTPARCOURS:
             case Instruction::FINPARCOURS:

        }
    }
    }