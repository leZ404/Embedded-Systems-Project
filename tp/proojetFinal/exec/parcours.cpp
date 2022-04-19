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
    FIN_PARCOURS
};

Mode instruction = Mode::DEBUT_PARCOURS;
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
const uint8_t PRECISION = 5;
const uint8_t IMPULSE_GAUCHE = 200;
const uint8_t IMPULSE_DROITE = 200;
const uint8_t DELAY_IMPULSION = 200;

uint8_t adresseMemoire = 0;
uint8_t adresseParcours = 0;
bool mur = true;
bool enregistrement = true;
bool signal = false;

void ecriture(uint8_t pwm)
{
    if (enregistrement)
    {
        memoireExterne.ecriture(adresseMemoire++, pwm);
        _delay_ms(5);
    }
}

void impulsionPwm()
{
    moteur.ajustementPwmNavigation(IMPULSE_DROITE, IMPULSE_GAUCHE);
    _delay_ms(DELAY_IMPULSION);
    ecriture(IMPULSE_DROITE);
    ecriture(IMPULSE_GAUCHE);
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

void initialisation()
{
    DDRC |= 0x00;
    DDRD |= 0x00;
    DDRB |= 0xff;
    DDRA |= 0x00;
}

void debutParcours()
{
    del.clignoter(15, LUMIERE_VERTE);
    while (obstacle() < ABSENCE_MUR)
    {
        moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
        ecriture(AVANCER_DROIT);
        ecriture(AVANCER_GAUCHE);
    }
    instruction = Mode::SUIVRE_MUR;
}

void suivreMur()
{
    mur = true;
    while (mur)
    {
        while (obstacle() > DISTANCE_20CM && obstacle() < TROP_PROCHE)
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
            ecriture(AVANCER_DROIT);
            ecriture(AVANCER_GAUCHE);
        }
        while (obstacle() > TROP_PROCHE)
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
            ecriture(AJUSTEMENT_DROIT);
            ecriture(AJUSTEMENT_GAUCHE);
        }
        while (obstacle() < DISTANCE_20CM && obstacle() > ABSENCE_MUR)
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT_GAUCHE, AJUSTEMENT_DROIT);
            ecriture(AJUSTEMENT_GAUCHE);
            ecriture(AJUSTEMENT_DROIT);
        }
        if (obstacle() < ABSENCE_MUR)
        {
            moteur.ajustementPwmNavigation(ARRET, ARRET);
            ecriture(ARRET);
            ecriture(ARRET);
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
        if (bouton.appuiBouton(PD2)) // Mode Fin Parcours
        {
            instruction = Mode::FIN_PARCOURS;
            signal = !signal;
        }
        if (bouton.appuiBouton(PD5)) // BOUTON BLANC MODE TOURNER
        {
            instruction = Mode::MODE_TOURNER;
            signal = !signal;
        }
    }
}
void suivreLumiere()
{
    Print impr;
    uint8_t gauche = lumiereGauche();
    uint8_t droite = lumiereDroite();
    impulsionPwm();
    while (lumiereDroite() > LUMIERE_FORTE || lumiereGauche() > LUMIERE_FORTE)
    {
        
        moteur.ajustementPwmNavigation(gauche, droite);
        ecriture(gauche);
        ecriture(droite);
        impr.afficherEntier8bit(gauche);
        impr.afficherChaineCaractere("-");
        impr.afficherEntier8bit(droite);
    }
    moteur.ajustementPwmNavigation(ARRET, ARRET);
    // ecriture(ARRET);
    // ecriture(ARRET);
    if (obstacle() > TROP_PROCHE)
    {
        instruction = Mode::SUIVRE_MUR;
    }
}
void demiTour()
{
    //AJUSTEMENRPWM AVEC VALEUR ET DELAY DU TEST

    while ((obstacle() <= DISTANCE_20CM))
    {
        del.ambrer();
        moteur.ajustementPwmNavigation(DEMITOUR_DROIT, DEMITOUR_GAUCHE);
    }
    enregistrement = false;
    instruction = Mode::SUIVRE_MUR;
}

void modeReprise()
{
    Print print;
    del.clignoter(15, LUMIERE_ROUGE);
    uint8_t pwmDroite = 0;
    uint8_t pwmGauche = 0;
    for (int i = 0; i < adresseMemoire;)
    {
        memoireExterne.lecture(i++, &pwmDroite);
        _delay_ms(5);
        memoireExterne.lecture(i++, &pwmGauche);
        _delay_ms(5);
        moteur.ajustementPwmNavigation(pwmDroite, pwmGauche);
        print.afficherEntier8bit(pwmDroite);
        print.afficherEntier8bit(pwmGauche);
    }
    instruction = Mode::FIN_PARCOURS;
}

void fin()
{
    if (bouton.appuiBouton(PD5)) // Debut mode reprise
    {
        modeReprise();
    }
    if (bouton.appuiBouton(PD2)) // Debut mode parcours
    {
        instruction = Mode::DEBUT_PARCOURS;
        del.clignoter(15, LUMIERE_VERTE);
    }
}

void faireParcours()
{
    Print p;
    bool finParcours = false;
    while (!finParcours)
    {
        switch (instruction)
        {
        case Mode::DEBUT_PARCOURS:
            impulsionPwm();
            p.afficherChaineCaractere("debut parcours--");
            debutParcours();
            break;
        case Mode::SUIVRE_MUR:
            p.afficherChaineCaractere("suivre mur--");
            impulsionPwm();
            suivreMur();
            break;
        case Mode::ATTENTE:
            p.afficherChaineCaractere("attendre--");
            attendre();
            break;
        case Mode::SUIVI_LUMIERE:
//            p.afficherChaineCaractere("suivre lumiere--");
            suivreLumiere();
            break;
        case Mode::MODE_TOURNER:
            impulsionPwm();
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
    Print pr ;
    initialisation();
    while (true)
    {
        if (bouton.appuiBouton(PD2))
        {
             pr.afficherChaineCaractere("interrupt");
            faireParcours();
        }
        if (bouton.appuiBouton(PD5))
        {
        pr.afficherChaineCaractere("boton-");


            modeReprise();
        }
    }
}