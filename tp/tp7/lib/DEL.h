#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>


//class Del pour PORTB 


const uint8_t LUMIERE_ETEINTE = 0x00;

const uint8_t LUMIERE_ROUGE = (1 << PB1);

const uint8_t LUMIERE_VERTE = (1 << PB0);


enum class Etat
{
 ETEINT,
 VERT,
 ROUGE,
};



class Del 
{
public: 
    Del();
    ~Del();
    
    // eteindre ou allumer la Del selon une couleur definie 
    void SetCouleurLumiere(Etat etat);
    

// clignoter aqu rythme de 2 fois par secondes 

void clignoter( uint8_t nbFois, const uint8_t Couleurlumiere);



private: 

};    