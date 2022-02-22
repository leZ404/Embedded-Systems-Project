/*
Travail : TRAVAIL_PRATIQUE 6, Problème 2
Section # : 02
Équipe # : EQUIPE_NO 35
Auteurs : Ryan Lahbabi , Zied Kaabi 
Correcteur : Marianne

Description du programme: Le programme ci-dessous répond au problème 2:
Ce porgramme permet de compiler sur un processeur atmega 324 la détection de la lumière capter par une photorésistance. En fonction de la lumière recu par la photorésistandce, 
la DEL change de couleur. Lorsque la lumière reçu est intense, comme pour une lampe de poche la DEL devient rouge. Lorsque la photorésistance reçoit une lumière ambiante, 
la DEL devient ambrer, elle clignote à très grande vitesse entre rouge et vert. Notre fontion clignoter permet d'établir ce clignotement. 
Enfin lorsque la lumière ne capte aucune lumière ou presque, la DEL Devient verte.

Identifications matérielles (Broches I/O):
Nous avons fais en sorte d'avoir en référence analogique +5.0 volts sur notre robot afin de régler le voltage de sortie du diviseur.
Utilisation d'une résistance 10K (brun-noir-orange) (Digi-Key: S10KQTR-ND) placer en série avec une photorésistance (Digi-Key: PDV-P8101-ND) 
sur le breadbord connectés avec un fil de données(bleu) reliés à deux PIN du DDRA et un fil d'alimentation(rouge) reliés au VCC de l'Atmega 324
INT 0/1: DDRA --> Cet input prend comme valeur 0 ou 1 afin de savoir si le courant passe ou non.
Analog Digital Converter: PB0; PB1; DDRB --> Ces Output ressort le courant conduit par la photorésistance. 
PB0 ressort le courant afin d'allumer la DEL bicoolore en vert et PB1 allume la DEL bicolore en rouge

Machine à états du problème 2:
| Problème2           |                |                |
|---------------------|----------------|----------------|
| ROUGE, VERT, AMBRER |                |                |
|                     |                |                |
| Entrées             | Etats prochain | Etats présents |
|  adcVal>500         | ROUGE          | VERT           |
| 500>adcVal>100      | AMBRER         | VERT           |
| adcVal<100          | VERT           | VERT           |
| adcVal>500          | ROUGE          | AMBRER         |
| adcVal<100          | VERT           | AMBRER         |
| 500>adcVal>100      | AMBRER         | AMBRER         |
| adcVal<100          | VERT           | ROUGE          |
| 500>adcVal>100      | AMBRER         | ROUGE          |
|  adcVal>500         | ROUGE          | ROUGE          |
Les valeur de adcVal ot été obtenue après plusieurs tests avec différents éclairage jusqu'à avoir les résultats attendus.

*/
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "can.h"
can variable = can();

enum class Etat
{
    AMBRER,
    VERT,
    ROUGE,
};
// une valeur superieur a 500 (lumiere est basse) nous permet d'avoir une DEL de couleur Verte 
// une valeur entre 500 et 100 (lumiere est a un bon niveau) nous permet d'avoir une DEL de couleur ambre
// une valeur inferieur a 100 (lumiere est trop forte) nous permet d'avoir une DEL de couleur  Rouge

const int LIMITEDELVERTE = 100;
const int LIMITEDELAMBRE = 500;


// Fonction de clignotement afin d'avoir une lumière ambrer
void ambrer(const int lumiere1, const int lumiere2)
{
    while ((variable.lecture(1) < LIMITEDELAMBRE) && (variable.lecture(1) >= LIMITEDELVERTE))
    {
        PORTB = lumiere1;
        _delay_ms(20);
        PORTB = lumiere2;
        _delay_ms(20);
    }
}

int main()
{
    DDRA = 0x00;
    DDRB = 0xff;
    const int LUMIERE_ROUGE = (1 << PB1);
    const int LUMIERE_VERTE = (1 << PB0);

    Etat etatCourant = Etat::VERT;

    PORTB = LUMIERE_VERTE;

    for (;;)
    {
        variable.lecture(1);

        switch (etatCourant)
        {

        case Etat::VERT:
            if ((variable.lecture(1) < LIMITEDELAMBRE) && (variable.lecture(1) >= LIMITEDELVERTE))
            {
                ambrer(LUMIERE_VERTE, LUMIERE_ROUGE);
                etatCourant = Etat::AMBRER;
            }
            else if (variable.lecture(1) < LIMITEDELVERTE)
            {
                PORTB = LUMIERE_ROUGE;
                etatCourant = Etat::ROUGE;
            }

            break;

        case Etat::ROUGE:
            if (variable.lecture(1) >= LIMITEDELAMBRE)
            {
                PORTB = LUMIERE_VERTE;
                etatCourant = Etat::VERT;
            }
            else if ((variable.lecture(1) < LIMITEDELAMBRE) && (variable.lecture(1) >= LIMITEDELVERTE))
            {
                ambrer(LUMIERE_VERTE, LUMIERE_ROUGE);
                etatCourant = Etat::AMBRER;
            }

            break;

        case Etat::AMBRER:

            if (variable.lecture(1) < LIMITEDELVERTE)
            {
                PORTB = LUMIERE_ROUGE;
                etatCourant = Etat::ROUGE;
            }

            else if (variable.lecture(1) >= LIMITEDELAMBRE)
            {
                PORTB = LUMIERE_VERTE;
                etatCourant = Etat::VERT;
            }
        }
    }
    return 0;
}