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

enum class Code
{
    AVANCER,
    ATTENDRE,
    TOURNER_GAUCHE,
    TOURNER_DROITE
};



Mode instruction = Mode::DEBUT_PARCOURS;
Code enregistrer = Code::ATTENDRE;

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

uint16_t count = 0x00;
uint16_t i = 0;
bool mur = true;
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

// ISR(TIMER2_COMPA_vect)
// {
//     if (Mode == Etat::SUIVRE_MUR)
//         memoireExterne.ecriture();
//     else if (Mode == Etat::SUIVI_LUMIERE)
//         memoireExterne.ecriture();
//     else if (Mode == Etat::FIN_PARCOURS)
//         memoireExterne.ecriture()
// }



void debutParcours()
{
    del.clignoter(15, LUMIERE_VERTE);
    while (obstacle()  < ABSENCE_MUR)
    {
        del.SetCouleurLumiere(Etat::ROUGE);
        moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
    }
    instruction = Mode::SUIVRE_MUR;
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

        if (bouton.appuiBouton(PD0))
        {
            mur = !mur;
            instruction = Mode::FIN_PARCOURS;
            del.SetCouleurLumiere(Etat::ROUGE);
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
    
    while ((obstacle() <= DISTANCE_20CM))
    {
        del.ambrer();
        moteur.ajustementPwmNavigation(DEMITOUR_DROIT, DEMITOUR_GAUCHE);
    }
    instruction = Mode::SUIVRE_MUR;
}


void finParcours()
{

    if (bouton.appuiBouton(PD4)) // Debut mode reprise
    {
            del.SetCouleurLumiere(Etat::ROUGE);


    }
    if (bouton.appuiBouton(PD4)) // Debut mode parcours
    {
        instruction = Mode::DEBUT_PARCOURS;
        del.clignoter(5, LUMIERE_VERTE);
    }
}



void fin()
{

    if (bouton.appuiBouton(PD0)) // Debut mode reprise
    {
        del.clignoter(15, LUMIERE_ROUGE);

    }
    if (bouton.appuiBouton(PD4)) // Debut mode parcours
    {
        instruction = Mode::DEBUT_PARCOURS;
        del.clignoter(5, LUMIERE_VERTE);
    }
}


void modeReprise()
{
    del.clignoter(15, LUMIERE_ROUGE);
    uint8_t reprise;
    while (i <= count)
    {
        memoireExterne.lecture(i, &reprise);
        i++;

        switch (enregistrer)
        {
        case Code::ATTENDRE:
            _delay_ms(UNE_SECONDE);
        case Code::AVANCER:
            pulsePwm();
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
        case Code::TOURNER_GAUCHE:
            pulsePwm();
            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
        case Code::TOURNER_DROITE:
            pulsePwm();
            moteur.ajustementPwmNavigation(AJUSTEMENT_GAUCHE, AJUSTEMENT_DROIT);
        }
    }
    del.SetCouleurLumiere(Etat::VERT);
    _delay_ms(10000);

}

void ecrire(uint8_t pwm)
{
    memoireExterne.ecriture(count++, pwm);
    _delay_ms(DELAY_MEMOIRE);
}

void faireParcours()
{
    Print p;
    bool finParcours = false;
    del.clignoter(15, LUMIERE_ROUGE);
    while (!finParcours)
    {

        switch (instruction)
        {
        case Mode::DEBUT_PARCOURS:
            debutParcours();

            break;

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
            _delay_ms(UNE_SECONDE);
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
    del.SetCouleurLumiere(Etat::ROUGE);
    _delay_ms(10000);
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