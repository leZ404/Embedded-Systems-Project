#pragma once
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
class Sonorite {
public:
    Sonorite();
    void tempsNote(uint8_t note);   //Timer
    void jouerNote(uint8_t index);  //PWM
    void arret();                   //on arrete le son 


    const uint8_t MIN = 45;         // note musicale minimale 
    
    
    uint8_t index;
};