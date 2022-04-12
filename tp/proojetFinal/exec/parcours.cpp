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
Print print;
Memoire24CXXX memoireExterne;

const uint16_t AJUSTEMENT_DROIT = 150;
const uint16_t AJUSTEMENT_GAUCHE = 75;
const uint16_t DEMITOUR_DROIT = 100;
const uint16_t DEMITOUR_GAUCHE = 200;
const uint16_t AVANCER_DROIT = 150;
const uint16_t AVANCER_GAUCHE = 150;
const uint16_t DISTANCE_20CM = 430;
const uint16_t ABSENCE_MUR = 700;
const uint16_t LUMIERE_FORTE = 700;
const uint16_t lumiereDroite = obstacle.lecture(4); //photoresistance de droite lumiere.lecture(1)
const uint16_t lumiereGauche = obstacle.lecture(1); //photoresistance de gauche  lumiere.lecture(4)

const uint16_t DBT = 0x01;
const uint16_t ATT = 0x02;
const uint16_t DAL = 0x44;
const uint16_t DET = 0x45;
const uint16_t SGO = 0x48;bouton.
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
    DEBUT_PARCOURS,
    SUIVRE_MUR,
    ATTENTE,
    MODE_TOURNER,
    SUIVI_LUMIERE,
    SUIVRE_SANS_ENREGISTRER,
    FIN_PARCOURS
};

uint16_t obstacle()
{
    return capteur.lecture(7);
}

int main()
{
    DDRD = 0x00
    DDRC = 0x00;
    DDRB = 0xff;
    DDRA = 0x00;


    
    uint8_t count = 0;
    uint8_t i = 0;

    bool mur = false;
    bool finParcours = false;
    
    Etat instruction = Etat::SUIVRE_MUR;
    
    while (true)
    {
        if (bouton.appuiBouton(PA0))
        { faireParcours();
            
        }
    }

    void faireParcours()
    {
        del.clignoter(15, LUMIERE_VERTE);
        mur = true;
                switch (instruction)
                {
                    case Etat::SUIVRE_MUR:
                        break;

                            //A la fin du mur, mettre mur = false

                    case Etat::ATTENTE:
                        if ((capteur.lecture(0) > LUMIERE_FORTE) || (capteur.lecture(2) > LUMIERE_FORTE ))  // Mode Suivi Lumiere
                        {
                            moteur.ajustementPWM(lumiereGauche, lumiereDroite);
                             // METTRE CONDITION POUR DIFFERENTIER DROITE OU GAUCHE DANS LECRITURE
                            instruction = Etat::SUIVI_LUMIERE;
                            break;
                        }

                        if (bouton.appuiBouton(PA0)) // Mode Fin Parcours
                        {
                            instruction = Etat::FIN_PARCOURS;
                            break;
                        }

                        if (bouton.appuiBouton(PA2)) // BOUTON BLANC MODE TOURNER
                        {
                            finParcours = false;
                            instruction = Etat::MODE_TOURNER;
                            break;
                        }

                    case Etat::SUIVI_LUMIERE:
                        while (capteur.lecture(0)) > LUMIERE_FORTE)  // Mode Suivi Lumiere
                            {
                                moteur.ajustementPWM(lumiereGauche, lumiereDroite);
                                 // METTRE CONDITION POUR DIFFERENTIER DROITE OU GAUCHE DANS LECRITURE
                            }

                        while (capteur.lecture(2)) > LUMIERE_FORTE)
                            {
                                moteur.ajustementPWM(lumiereGauche, lumiereDroite); // METTRE CONDITION POUR DIFFERENTIER DROITE OU GAUCHE DANS LECRITURE
                                memoireExterne.ecriture(count++, TRG);
                                _delay_ms(1000);
                                memoireExterne.ecriture(count++, ATT);
                            }
                        instruction = Etat::SUIVRE_MUR;
                        break;
                    }

                    case Etat::MODE_TOURNER:
                    {
                        //AJUSTEMENRPWM AVEC VALEUR ET DELAY DU TEST
                        moteur.ajustementPWM(DEMITOUR_DROIT, DEMITOUR_GAUCHE);

                        instruction = Etat::SUIVRE_SANS_ENREGISTRER;
                        break;
                    }

                    case Etat::SUIVRE_SANS_ENREGISTRER:
                        while (mur)
                        {
                            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
                            memoireExterne.ecriture(count++, MAV);

                            if (obstacle() > DISTANCE_20CM)
                            {
                                moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
                                memoireExterne.ecriture(count++, TRG);
                                _delay_ms(1000);
                                memoireExterne.ecriture(count++, ATT);
                            }
                            else if (obstacle() > ABSENCE_MUR)
                    {
                        mur = false;
                        instruction = Etat::FIN_PARCOURS;
                    }
                    break;
                    //A la fin du mur, mettre mur = false
            
            case Etat::FIN_PARCOURS:
                del.SetCouleurLumiere(Etat::ROUGE);
                del.SetCouleurLumiere(Etat::VERT)
                if (bouton.appuiBouton(PA2)) // Debut mode reprise
                {
                    del.clignoter(15, LUMIERE_ROUGE);
                    memoireExterne..lecture(); //Faire le mode reprise
                
                if (bouton.appuiBouton(PA0)) // Debut mode parcours
                {
                    instruction = Etat::DEBUT_PARCOURS;
                }
                break
        }
    }
}   
    



void suivreMur(Del del)
{
    while (mur)
    {
        if(obstacle() >= DISTANCE_20CM)
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
            memoireExterne.ecriture(count++, MAV);

        if (obstacle() < DISTANCE_20CM)
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
            memoireExterne.ecriture(count++, TRG);
            _delay_ms(1000);
            memoireExterne.ecriture(count++, ATT);
        }

        if (obstacle() > ABSENCE_MUR)del.clignoter(15,)
        {
            mur = false;
            instruction = Etat::ATTENTE;
            break;
        }
    }

}