#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sonorite.h"

Sonorite::Sonorite(){
}

void Sonorite::tempsNote(uint8_t index) {

    DDRD |= (1 << PD5) | (1 << PD4); // Port D5 en sortie (OC1A)
    PORTD &= ~(1 << PD4);            // Force un 0 au port adjacent
    const uint16_t  tableActif[] = {4545, 4290, 4050, 3822, 3608, 3405, 3214, 3034, 2863, 2703, 2551,
                                  2408, 2273, 2145, 2025, 1911, 1804, 1703, 1012, 956, 902, 851,
                                  804, 758, 716, 676, 636, 602, 568}; //En nanosecondes
    //Utilisation de timer1 vu que l'on utilise deja timer0 pour moteur
    TCNT1 = 0;
    OCR1A = tableActif[index];
    TCCR1A |= (1 << COM1A0); // Compare Register
    TCCR1B |= (1 << CS12);   //Prescaler 256
    TCCR1B |= (1 << WGM12);  // Mode CTC (suggerer par le tp9)
    TCCR1C = 0;

}

void Sonorite::jouerNote(uint8_t note) {
    index = note - MIN; //Si note = 45, et MIN = 45, l'index sera a 0 et ainsi de suite
    //TableFrequence modifier pour arrondir les valeurs
    const uint16_t tableFrequence[] = { 110, 117, 123, 132, 139, 147, 156, 165,
                                        175, 185, 196, 20765, 220, 233, 247, 262,
                                        277, 294, 311, 330, 349, 370, 392, 415,
                                        440, 466, 494, 523, 554, 587, 622, 659,
                                        698, 740, 784, 831, 880 };
    const uint16_t nbIteration = tableFrequence[index];
    for (int i = 0; i < nbIteration; i++)
    {
        tempsNote(note);
    }

}

void Sonorite::arret() {
    //Nous mettons tout a zero dans l'ordre qu'on les a initiliaser
    DDRD = 0x00;
    TCNT1 = 0;
    OCR1A = 0;
    TCCR1A = 0; // Compare Register
    TCCR1B = 0;   //Prescaler 256
    TCCR1B = 0;  // Mode CTC (suggerer par le tp9)
    TCCR1C = 0;
}