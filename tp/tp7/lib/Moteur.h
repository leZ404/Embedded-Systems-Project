#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//class Moteur configuree pour PORTB

class Moteur
{
public:
    Moteur(uint8_t pinDirectionDroite, uint8_t pinDirectionGauche);
    //  ~Moteur();

    // config pont H : E=1 / D = 1
    void avancer();

    // E=1 / D = 0

    void reculer();

    // E = 0 / D= X
    void arret();

    //vitesse du moteur
    //void setVitesse(uint8_t dureeRoueDroite ,uint8_t dureeRoueGauche );

    void ajustementPwmNavigation(uint8_t pourcentageDroite, uint8_t dureeRoueGauche);

private:
    uint8_t _directionDroite;
    uint8_t _directionGauche;

    //uint8_t _frequence; // inverse de la frequence du moteur
};
