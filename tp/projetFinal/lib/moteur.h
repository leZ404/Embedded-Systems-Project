
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


    // arreter les roues
    void arret();


    // fonction pour ajuster le pwm selon des pourcentages (celui de droite est independant de celui de gauche) 
    void ajustementPwmNavigation(uint16_t valRoueDroite, uint16_t valRoueGauche);

private:
    uint8_t _directionDroite;      // pin de direction roue droite 
    uint8_t _directionGauche;     // pin de direction roue gauche

};