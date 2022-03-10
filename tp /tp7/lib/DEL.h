#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>


//class Del pour PORTB 


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

void clignoter( uint8_t nbFois,  int Couleurlumiere);



private: 
int _Couleurlumiere; 
 


};    