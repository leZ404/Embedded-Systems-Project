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
    Moteur(uint8_t pinDirectionDroite, uint8_t pinDirectionGauche); // constructeur 
    //  ~Moteur();     // ne pas commenter les destructeurs non implementes ne fait pas fonctionner les test (erreur au niveau du make)

    // avancer les 2 roues avec vitesse MAX
    void avancer();

    // E=1 / D = 0
    // reculer le 2 roues avec vitesse MAX  
    void reculer();

    // arreter les roues
    void arret();


    // fonction pour ajuster le pwm selon des pourcentages (celui de droite est independant de celui de gauche) 
    void ajustementPwmNavigation(uint8_t pourcentageDroite, uint8_t dureeRoueGauche);

private:
    uint8_t _directionDroite;      // pin de direction roue droite 
    uint8_t _directionGauche;     // pin de direction roue gauche

};
