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
#define UNE_SECONDE 1000

Moteur moteur(PB5, PB6);
Bouton bouton;
can capteur;
Del del;
Print print;
Memoire24CXXX memoireExterne;

const uint16_t AJUSTEMENT = 150;
const uint16_t AVANCER_DROIT = 100;
const uint16_t AVANCER_GAUCHE = 100;
const uint16_t DISTANCE_20CM = 270;
const uint16_t MUR_LOIN = 220;
const uint16_t ABSENCE_MUR = 120;
const uint16_t LUMIERE_FORTE = 700;

const uint16_t CLIGNOTER = 0x02;
const uint16_t ATTENDRE = 0x02;
const uint16_t DAL = 0x44;
const uint16_t DET = 0x45;
const uint16_t ARRET = 0x60;
const uint16_t ARRET_1 = 0x61;
const uint16_t AVANCE = 0x62;
const uint16_t TOURNE_DROITE = 0x64;
const uint16_t TOURNE_GAUCHE = 0x65;


uint8_t count = 0;
uint8_t i = 0;

bool mur = false;
bool finParcours = false;
bool reprise = false;

Etat instruction = Etat::SUIVRE_MUR;

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

uint16_t lumiereDroite()
{
    return capteur.lecture(4); //photoresistance de droite lumiere.lecture(4)
}

uint16_t lumiereGauche()
{
    return capteur.lecture(1); //photoresistance de gauche lumiere.lecture(1)
}

uint16_t obstacle()
{
    return capteur.lecture(7);
}

initialisation()
{
    DDRC = 0x00;
    DDRD = 0x00;
    DDRB = 0xff;
    DDRA = 0x00;
}

void faireParcours()
{
    del.clignoter(15, LUMIERE_VERTE);
    while (!finParcours)
    {
        switch (instruction)
        {
        case Etat::SUIVRE_MUR:
            suivreMur();
            break;

        case Etat::ATTENTE:
            attendre();
            break;
        case Etat::SUIVI_LUMIERE:
            suivreLumiere();
            break;

        case Etat::MODE_TOURNER:
            demiTour();
            break;

        case Etat::SUIVRE_SANS_ENREGISTRER:
            suivreUnique();
            break;

        case Etat::FIN_PARCOURS:
            fin();
            finParcours = !finParcours;
            break;
        }
    }
}

void suivreMur()
{
    mur = true;
    while (mur)
    {
        if (obstacle() < ABSENCE_MUR)
            {
                mur = !mur;
                instruction = Etat::ATTENTE;
                break;
            }
        while( obstacle() > MUR_LOIN &&  obstacle() < DISTANCE_20CM  )
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE );
            del.clignoter(4,LUMIERE_ROUGE);
        }
        
        while( obstacle() < MUR_LOIN  &&  obstacle() > ABSENCE_MUR )
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AJUSTEMENT );
            del.SetCouleurLumiere(Etat::VERT);
        }
           
        while( obstacle() > DISTANCE_20CM )
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT, AVANCER_GAUCHE );
            del.SetCouleurLumiere(Etat::ROUGE);
        }
        
        
   
    }
}

void attendre()
{
    signal = false;
    while (!signal)
    {
        if (lumiereDroite() > LUMIERE_FORTE) || (lumiereGauche() > LUMIERE_FORTE)) // Mode Suivi Lumiere
            {
                // METTRE CONDITION POUR DIFFERENTIER DROITE OU GAUCHE DANS LECRITURE
                instruction = Etat::SUIVI_LUMIERE;
                signal = !signal;
            }

        if (bouton.appuiBouton(PA0)) // Mode Fin Parcours
        {
            instruction = Etat::FIN_PARCOURS;
            signal = !signal;
        }

        if (bouton.appuiBouton(PA2)) // BOUTON BLANC MODE TOURNER
        {
            finParcours = false;
            instruction = Etat::MODE_TOURNER;
            signal = !signal;
        }
    }
}

void suivreLumiere()
{
    uint16_t gauche = lumiereGauche();
    uint16_t droite = lumieredroite();

    while (gauche > LUMIERE_FORTE || droite > LUMIERE_FORTE) // Mode Suivi Lumiere
    {
        moteur.ajustementPWM(gauche >> 2, droite >> 2);

        if (droite > gauche)
        {
            memoireExterne.ecriture(count++, TOURNE_DROITE);
        }
        else
        {
            memoireExterne.ecriture(count++, TOURNE_GAUCHE);
        }
    }
    instruction = Etat::SUIVRE_MUR;
}

void demiTour()
{
    //AJUSTEMENRPWM AVEC VALEUR ET DELAY DU TEST
      while( obstacle() > ABSENCE_MUR &&  obstacle() < DISTANCE_20CM  )
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE );
            del.ambrer(10)
        }
        
        while( obstacle() < ABSENCE_MUR )
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AJUSTEMENT );
            del.ambrer(10)
        }
           
        while( obstacle() > DISTANCE_20CM )
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT, AVANCER_GAUCHE );
            del.ambrer(10)
        }
    instruction = Etat::SUIVRE_SANS_ENREGISTRER;
}

void suivreUnique()
{
    mur = true;
    while (mur)
    {
       while( obstacle() > ABSENCE_MUR &&  obstacle() < DISTANCE_20CM  )
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE );
        }
        
        while( obstacle() < ABSENCE_MUR )
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AJUSTEMENT );
        }
           
        while( obstacle() > DISTANCE_20CM )
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT, AVANCER_GAUCHE );
        }
        else if (obstacle() > ABSENCE_MUR)
        {
            mur = !mur;
            instruction = Etat::FIN_PARCOURS;
        }
    }
}

void fin()
{
    del.SetCouleurLumiere(Etat::ROUGE);
    del.SetCouleurLumiere(Etat::VERT);
    if (bouton.appuiBouton(PA2)) // Debut mode reprise
    {
        del.clignoter(15, LUMIERE_ROUGE);
        modeReprise();
        reprise = !reprise;
    }
    if (bouton.appuiBouton(PA0)) // Debut mode parcours
    {
        instruction = Etat::DEBUT_PARCOURS;
    }
}

void modeReprise()
{
    uint16_t code = 0;
    while (i <= count)
    {
        memoireExterne.lecture(i, &code);
        i++;

        switch (code)
        {
        case ATT:
            _delay_ms(UNE_SECONDE);
        case MAV:
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
        case TRG:
            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
        case TRD:
            moteur.ajustementPwmNavigation(AJUSTEMENT_GAUCHE, AJUSTEMENT_DROIT);
        }
    }
}

int main()
{
    initialisation();

    while (true)
    {
        if (bouton.appuiBouton(PA0))
        {
            faireParcours();
        }
    }
}