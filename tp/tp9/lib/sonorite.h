#pragma once
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
class Sonorite {
public:
    Sonorite();
    void tempsNote(uint16_t compteur) ;   //Timer
    void jouerNote(uint8_t index);  //PWM
    void arret();                   //on arrete le son 


    const uint8_t MIN = 45;         // note musicale minimale 
    
    uint16_t calcul_compteur(uint16_t note);
    uint8_t index;

    const uint16_t getTableCompteur(uint8_t i);

    private :
    const uint16_t tableFrequence[37] = { 110, 117, 123, 132, 139, 147, 156, 165,
                                        175, 185, 196, 208, 220, 233, 247, 262,
                                        277, 294, 311, 330, 349, 370, 392, 415,
                                        440, 466, 494, 523, 554, 587, 622, 659,
                                        698, 740, 784, 831, 880 };
    
    const uint16_t tableCompteur[37] = { 140, 132, 126, 117, 116, 105, 99, 94,   //valeur de compteur pour une frequence bien definie calculee a partir de la formule fOCnA doc p120 
                                        88, 84, 79 , 74, 70, 66, 63, 59,         // valeurs arrondies vu qu'on peut pas prendre des float
                                        56, 52, 50, 47, 44, 42, 39, 37,          // on a pas finalement utilise ce tableau (error : was not declared in this scope dans le main) pourtant on avait un getter
                                        35, 33, 31, 29, 28, 26, 25, 23,
                                        22, 21, 19, 18, 17 };                                     
};