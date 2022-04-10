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

Moteur moteur(PB5, PB6);
Bouton bouton;
can capteur;
Del del;
Print p;
Memoire24CXXX m;
Bouton b;

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

enum class Etat
{
    DEBUTPARCOURS,
    SUIVREMUR,
    ATTENTE,
    MODETOURNER,
    SUIVILUMIERE,
    FINPARCOURS
};

uint16_t obstacle()
{
    return capteur.lecture(7);
}

int main()
{

    DDRC = 0xff;
    DDRB = 0xff;
    DDRA = 0x00;

    uint16_t AJUSTEMENT_DROIT = 75;
    uint16_t AJUSTEMENT_GAUCHE = 150;
    uint16_t lumiereDroite = obstacle.lecture(4); //photoresistance de droite lumiere.lecture(1)
    uint16_t lumiereGauche = obstacle.lecture(1); //photoresistance de gauche  lumiere.lecture(4)

    uint8_t count = 0;
    uint8_t i = 0;
    bool mur = false;
    Etat instruction = Etat::DEBUTPARCOURS;
    while (true)
    {
        if (b.appuiBouton(PA0))
        {
            del.clignoter(4, LUMIERE_VERTE);
            switch (instruction)
            {
            case Etat::SUIVREMUR:
                while (mur)
                {
                    moteur.ajustementPwmNavigation(100);
                    m.ecriture(count++, MAV);

                    if (obstacle() > 430)
                    {
                        moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
                        m.ecriture(count++, TRG);
                        _delay_ms(1000);
                        m.ecriture(count++, ATT);
                    }

                    //A la fin du mur, mettre mur = false
                }
                instruction = Etat::ATTENTE;
                break;
            case Etat::ATTENTE:
            case Etat::MODETOURNER:
            case Etat::DEBUTPARCOURS:
                while (obstacle() < 430)
                {
                    moteur.ajustementPwmNavigation(100);
                    m.ecriture(count++, MAV);
                }
                instruction = Etat::SUIVREMUR;
                mur = true;
                break;
            case Instruction::FINPARCOURS:
            }
        }
    }