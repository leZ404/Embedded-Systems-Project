/****************************************************************************
 * Travail : PROJET FINAL
Section # : 02
Équipe # : EQUIPE_NO 3544
Auteurs : Ryan Lahbabi , Zied Kaabi, Ashveer Golam, Omar Bamrim
Correcteur : Jerome Collin  .
Nom du robot : GOAT
 ****************************************************************************/

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

enum class Mode
{
    SUIVRE_MUR,
    ATTENTE,
    MODE_TOURNER,
    SUIVI_LUMIERE,
    FIN_PARCOURS
};

Mode instruction = Mode::SUIVRE_MUR;

/****************************************************************************
 * Declaration des instances et constantes .
 ****************************************************************************/

Moteur moteur(PB5, PB6);
Bouton bouton;
can capteur;
Del del;
Print print;
Memoire24CXXX memoireExterne;

const uint16_t AJUSTEMENT_DROIT = 200;
const uint16_t AJUSTEMENT_GAUCHE = 115;
const uint16_t DEMITOUR_DROIT = 115;
const uint16_t DEMITOUR_GAUCHE = 170;
const uint16_t AVANCER_DROIT = 120;
const uint16_t AVANCER_GAUCHE = 110;
const uint16_t DISTANCE_MUR = 300;
const uint16_t TROP_PROCHE = 350;
const uint16_t ABSENCE_MUR = 170;
const uint16_t LUMIERE_FORTE = 190;
const uint8_t DELAIS_MEMOIRE = 5;
const uint8_t ARRET = 0;
const uint8_t PRECISION = 5;
const uint8_t IMPULSE_GAUCHE = 250;
const uint8_t IMPULSE_DROITE = 250;
const uint8_t DELAY_IMPULSION = 200;
const uint16_t DEUX_SECONDE = 2000;

const uint8_t AVANCE = 10;
const uint8_t DROITE = 20;
const uint8_t GAUCHE = 30;
const uint8_t PULSE = 40;

uint8_t adresseMemoire = 0;
uint8_t adresseParcours = 0;
bool mur = true;
bool enregistrement = true;
bool signal = false;

/****************************************************************************
 * Fonction:    ecriture()
 * Description: Ecrit dans l'EPROM les instruction exectées par le robot lors
                du mode parcours.
 * Paramètres:  uint16_t
 * Retour:      Aucun
 ****************************************************************************/

void ecriture(uint8_t inst)
{
    if (enregistrement)
    {
        memoireExterne.ecriture(adresseMemoire, inst);
        _delay_ms(DELAIS_MEMOIRE);
        adresseMemoire++;
    }
}

/****************************************************************************
 * Methode :    impulsionPwm()
 * Description: Corrige un probléme  de l'ordre du hardware. Elle consite en
 *              chauffer les roues juste après un make install.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void impulsionPwm()
{
    moteur.ajustementPwmNavigation(IMPULSE_DROITE, IMPULSE_GAUCHE);
    _delay_ms(DELAY_IMPULSION);
    ecriture(PULSE);
}

/****************************************************************************
 * Fonction:    lumiereDroite()
 * Description: retourne une valeur selon l'intensité lumineuse détectée par
                la photoresistance du côté droit du bread board branché au
                PORTA3
 * Paramètres:  Aucun
 * Retour:      uint16_t
 ****************************************************************************/

uint16_t lumiereDroite()
{
    return ((capteur.lecture(3) >> 2) + PRECISION);
}

/****************************************************************************
 * Fonction:    lumiereGauche()
 * Description: retourne une valeur selon l'intensité lumineuse détectée par
                la photoresistance du côté gauche du bread board branché au
                PORTA4 (l'intensité détectée et la valeur de retour sont
                proportionelles).
 * Paramètres:  Aucun
 * Retour:      uint16_t
 ****************************************************************************/

uint16_t lumiereGauche()
{
    return (capteur.lecture(4) >> 2);
}

/****************************************************************************
 * Fonction:    obstacle()
 * Description: retourne une valeur selon la distance détectée par le capteur
                IR entre le robot et le mur (la distance détectée  et la
                valeur de retour sont proportionelles).
 * Paramètres:  Aucun
 * Retour:      uint16_t
 ****************************************************************************/
uint16_t obstacle()
{
    return capteur.lecture(7);
}

/****************************************************************************
 * Fonction:    initialisation()
 * Description: Initialise les ports en mode entrée.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void initialisation()
{
    DDRC |= 0x00;
    DDRD |= 0x00;
    DDRB |= 0xff;
    DDRA |= 0x00;
}

/****************************************************************************
 * Fonction:    suivreMur()
 * Description: Permet de suivre le mur à 20 cm de celui-ci grâce à la
                méthode obstacle(). La del s'allume en fonction de la
                distance avec le mur.
 * Paramètres:  Aucun
 * Retour:      Aucun
 * Note: Nous n'utilisons pas de fonction des fonctions pour les while pour
         des raisons materielles.
 ****************************************************************************/

void suivreMur()
{

    mur = true;
    while (mur)
    {

        while (obstacle() > DISTANCE_MUR && obstacle() < TROP_PROCHE)
        {

            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
            ecriture(AVANCE);
        }
        while (obstacle() > TROP_PROCHE)
        {

            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
            ecriture(GAUCHE);
        }
        while (obstacle() < DISTANCE_MUR && obstacle() > ABSENCE_MUR)
        {

            moteur.ajustementPwmNavigation(AJUSTEMENT_GAUCHE, AJUSTEMENT_DROIT);
            ecriture(DROITE);
        }

        if (obstacle() < ABSENCE_MUR)
        {

            moteur.ajustementPwmNavigation(ARRET, ARRET);
            mur = false;
            instruction = Mode::ATTENTE;
        }
    }
}

/****************************************************************************
 * Fonction:    attendre()
 * Description: Attend signal de l'évaluateur une fois le robot ne detecte
                plus de mur ( à l’intermédiaire  entre les 2 portions de mur )
                pour éventuellement changer de mode.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void attendre()
{
    signal = false;
    while (!signal)
    {
        if ((lumiereDroite() > LUMIERE_FORTE) || (lumiereGauche() > LUMIERE_FORTE))
        {

            instruction = Mode::SUIVI_LUMIERE;
            signal = true;
        }
        if (bouton.appuiBouton(PD2))
        {
            instruction = Mode::FIN_PARCOURS;
            signal = true;
        }
        if (bouton.appuiBouton(PD7))
        {
            instruction = Mode::MODE_TOURNER;
            signal = true;
        }
    }
}

/****************************************************************************
 * Fonction:    suivreLumiere()
 * Description: Permet au robot de se déplacer grâce à l'intensité lumineuse
                perçue par les photoresistances à l'aide des methodes
                lumiereGauche() et lumiereDroite().
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void suivreLumiere()
{

    uint8_t gauche = lumiereGauche();
    uint8_t droite = lumiereDroite();

    while (lumiereDroite() > LUMIERE_FORTE || lumiereGauche() > LUMIERE_FORTE)
    {

        moteur.ajustementPwmNavigation(gauche, droite);
        ecriture(PULSE);
    }
    moteur.ajustementPwmNavigation(ARRET, ARRET);
    if (obstacle() > TROP_PROCHE)
    {
        instruction = Mode::SUIVRE_MUR;
    }
}

/****************************************************************************
 * Fonction:    demiTour()
 * Description: Permet au robot de faire un demi-tour.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void demiTour()
{

    impulsionPwm();
    do
    {
        del.ambrer();
        moteur.ajustementPwmNavigation(DEMITOUR_DROIT, DEMITOUR_GAUCHE);
    } while (obstacle() < TROP_PROCHE);
    moteur.ajustementPwmNavigation(DEMITOUR_DROIT, DEMITOUR_GAUCHE);
    _delay_ms(500);
    enregistrement = false;
    instruction = Mode::SUIVRE_MUR;
}

/****************************************************************************
 * Fonction:    modeReprise()
 * Description: Permet au robot de suivre le parcours grace aux instructions
                gardées en mémoire.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void modeReprise()
{

    del.clignoter(15, LUMIERE_ROUGE);
    uint8_t instruc = 0;
    impulsionPwm();

    while (adresseParcours < adresseMemoire)
    {

        memoireExterne.lecture(adresseParcours, &instruc);

        adresseParcours++;

        if (instruc == AVANCE)
        {
            moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
        }

        else if (instruc == GAUCHE)
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT_DROIT, AJUSTEMENT_GAUCHE);
        }

        else if (instruc == DROITE)
        {
            moteur.ajustementPwmNavigation(AJUSTEMENT_GAUCHE, AJUSTEMENT_DROIT);
        }
        else if (instruc == PULSE)
        {
            moteur.ajustementPwmNavigation(IMPULSE_DROITE, IMPULSE_GAUCHE);
        }

        _delay_ms(57);
    }

    instruction = Mode::FIN_PARCOURS;
    moteur.ajustementPwmNavigation(ARRET, ARRET);
    del.SetCouleurLumiere(Etat::VERT);
    _delay_ms(DEUX_SECONDE);
}

/****************************************************************************
 * Fonction:    fin()
 * Description: Permet de laisser le temps à la memoire externe d'enregistrer
                la première moitié du parcours et attends le signal de
                l'évaluateur pour passer en mode reprise ou mode parcours.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void fin()
{
    del.SetCouleurLumiere(Etat::ROUGE);
    _delay_ms(DEUX_SECONDE);
    del.SetCouleurLumiere(Etat::VERT);
    _delay_ms(DEUX_SECONDE);
    if (bouton.appuiBouton(PD7))
    {
        impulsionPwm();
        modeReprise();
    }
    if (bouton.appuiBouton(PD2))
    {
        del.clignoter(15, LUMIERE_VERTE);
        instruction = Mode::SUIVRE_MUR;
    }
}

/****************************************************************************
 * Fonction:    faireParcours()
 * Description: Switch case du mode parcours.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/

void faireParcours()
{

    bool finParcours = false;
    while (!finParcours)
    {
        switch (instruction)
        {
        case Mode::SUIVRE_MUR:
            impulsionPwm();
            suivreMur();
            break;

        case Mode::ATTENTE:
            attendre();
            break;

        case Mode::SUIVI_LUMIERE:
            suivreLumiere();
            break;

        case Mode::MODE_TOURNER:
            impulsionPwm();
            demiTour();
            break;

        case Mode::FIN_PARCOURS:
            fin();
            finParcours = true;
            break;
        }
    }
}

int main()
{

    initialisation();
    while (true)
    {
        if (bouton.appuiBouton(PD2))
        {
            del.clignoter(15, LUMIERE_VERTE);
            faireParcours();
        }
        if (bouton.appuiBouton(PD7))
        {
            modeReprise();
        }
    }
}