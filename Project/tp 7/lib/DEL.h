#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

//class Del pour PORTC


const uint8_t LUMIERE_ETEINTE = 0x00;
const uint8_t LUMIERE_ROUGE = (1 << PB0);
const uint8_t LUMIERE_VERTE = (1 << PB1);


// differents etats d'une Led

enum class Etat
{
    ETEINT,
    VERT,
    ROUGE,
};

class Del
{
public:
    Del();     // constructeur 
  //~Del();     // ne pas commenter les destructeurs non implementes ne fait pas fonctionner les test (erreur au niveau du make)

 // eteindre ou allumer la Del selon un etat bien defini
    void SetCouleurLumiere(Etat etat);

// clignoter au rythme de 2 fois par secondes

    void clignoter(uint8_t nbFois, const uint8_t Couleurlumiere);
    void ambrer();


};