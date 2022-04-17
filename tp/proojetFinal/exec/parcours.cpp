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
#include <bouton.h>
#include <can.h>
#define UNE_SECONDE 1000

enum class Mode
{
    DEBUT_PARCOURS,
    SUIVRE_MUR,
    ATTENTE,
    MODE_TOURNER,
    SUIVI_LUMIERE,
    SUIVRE_SANS_ENREGISTRER,
    FIN_PARCOURS
};

Mode instruction = Mode::SUIVRE_MUR;

Moteur moteur(PB5, PB6);
Bouton bouton;
can capteur;
Del del;
Print print;
Memoire24CXXX memoireExterne;

const uint16_t AJUSTEMENT_DROIT = 145;
const uint16_t AJUSTEMENT_GAUCHE = 110;
const uint16_t DEMITOUR_DROIT = 100;
const uint16_t DEMITOUR_GAUCHE = 155;
const uint16_t AVANCER_DROIT = 110;
const uint16_t AVANCER_GAUCHE = 110;
const uint16_t DISTANCE_20CM = 350;
const uint16_t TROP_PROCHE = 400;
const uint16_t ABSENCE_MUR = 170;
const uint16_t LUMIERE_FORTE = 180;
const uint8_t DELAY_MEMOIRE = 5;
const uint8_t ARRET = 0;
const uint8_t PRECISION = 20;

uint16_t count = 0;
uint16_t i = 0;
bool mur = true;
bool reprise = false;
bool signal = false;

void pulsePwm()
{
    moteur.ajustementPwmNavigation(200, 200);
    _delay_ms(200);
}

uint16_t lumiereDroite()
{
    return ((capteur.lecture(3) >> 2) + PRECISION); //photoresistance de droite lumiere.lecture(4)
}

uint16_t lumiereGauche()
{
    return (capteur.lecture(4) >> 2); //photoresistance de gauche lumiere.lecture(1)
}

uint16_t obstacle()
{
    return capteur.lecture(7);
}

void ecriture(uint16_t pwm)
{
    memoireExterne.ecriture(count++, pwm);
    _delay_ms(5);
}

void initialisation()
{
    DDRC |= 0x00;
    DDRD |= 0x00;
    DDRB |= 0xff;
    DDRA |= 0x00;
}

void suivreMur()
{
    mur = true;
    while (mur)
    {
        del.clignoter(1, LUMIERE_VERTE);
        while (obstacle() > DISTANCE_20CM && obstacle() < TROP_PROCHE)
        {
            del.SetCouleurLumiere(Etat::ROUGE);
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
        }

        while (obstacle() > TROP_PROCHE)
        {
            del.SetCouleurLumiere(Etat::VERT);
            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
        }

        while (obstacle() < DISTANCE_20CM && obstacle() > ABSENCE_MUR)
        {
            del.clignoter(1, LUMIERE_ROUGE);
            moteur.ajustementPwmNavigation(AJUSTEMENT_GAUCHE, AJUSTEMENT_DROIT);
        }

        if (obstacle() < ABSENCE_MUR)
        {
            moteur.ajustementPwmNavigation(ARRET, ARRET);

            mur = !mur;
            instruction = Mode::ATTENTE;
        }
    }
}

void attendre()
{
    signal = false;
    while (!signal)
    {

        if ((lumiereDroite() > LUMIERE_FORTE) || (lumiereGauche() > LUMIERE_FORTE)) // Mode Suivi Lumiere
        {

            // METTRE CONDITION POUR DIFFERENTIER DROITE OU GAUCHE DANS LECRITURE
            instruction = Mode::SUIVI_LUMIERE;
            signal = !signal;
        }

        if (bouton.appuiBouton(PD4)) // Mode Fin Parcours
        {
            instruction = Mode::FIN_PARCOURS;
            signal = !signal;
        }

        if (bouton.appuiBouton(PD0)) // BOUTON BLANC MODE TOURNER
        {
            instruction = Mode::MODE_TOURNER;
            signal = !signal;
        }
    }
}

void suivreLumiere()
{
    uint16_t gauche = lumiereGauche();
    uint16_t droite = lumiereDroite();

    while (lumiereDroite() > LUMIERE_FORTE || lumiereGauche() > LUMIERE_FORTE)
    {
        moteur.ajustementPwmNavigation(gauche, droite);
    }

    moteur.ajustementPwmNavigation(0, 0);

    if (obstacle() > TROP_PROCHE)
    {
        del.clignoter(5, LUMIERE_ROUGE);
        instruction = Mode::SUIVRE_MUR;
    }
}

void demiTour()
{
    //AJUSTEMENRPWM AVEC VALEUR ET DELAY DU TEST
    del.SetCouleurLumiere(Etat::ROUGE);
    while ((obstacle() <= DISTANCE_20CM))
    {
        moteur.ajustementPwmNavigation(DEMITOUR_DROIT, DEMITOUR_GAUCHE);
    }
    instruction = Mode::SUIVRE_MUR;
}

void fin()
{

    if (bouton.appuiBouton(PD0)) // Debut mode reprise
    {
        del.clignoter(15, LUMIERE_ROUGE);
        //modeReprise();
    }
    if (bouton.appuiBouton(PD4)) // Debut mode parcours
    {
        instruction = Mode::DEBUT_PARCOURS;
        del.clignoter(5, LUMIERE_VERTE);
    }
}

void modeReprise()
{
    uint16_t *code;
    while (i <= count)
    {
        i++;
    }
}

void faireParcours()
{
    Print p;
    bool finParcours = false;
    del.clignoter(15, LUMIERE_VERTE);
    while (!finParcours)
    {

        switch (instruction)
        {
        case Mode::SUIVRE_MUR:
            p.afficherChaineCaractere("suivre mur--");
            pulsePwm();
            suivreMur();

            break;

        case Mode::ATTENTE:
            p.afficherChaineCaractere("attendre--");

            attendre();

            break;
        case Mode::SUIVI_LUMIERE:
            p.afficherChaineCaractere("suivre lumiere--");
            suivreLumiere();

            break;

        case Mode::MODE_TOURNER:
            pulsePwm();
            p.afficherChaineCaractere("demitour--");
            demiTour();
            p.afficherChaineCaractere("demitour-fait");

            break;

        case Mode::FIN_PARCOURS:
            fin();
            finParcours = !finParcours;
            p.afficherChaineCaractere("finParcours--");

            break;
        }
    }
}

int main()
{
    initialisation();

    while (true)
    {
        if (bouton.appuiBouton(PD0))
        {
            faireParcours();
        }
        if (bouton.appuiBouton(PD4))
        {
            modeReprise();
        }
    }
}