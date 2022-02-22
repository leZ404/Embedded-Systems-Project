/*
Travail : TRAVAIL_PRATIQUE 6, Problème 1
Section # : 02
Équipe # : EQUIPE_NO 35 
Auteurs : Ryan Lahbabi , Zied Kaabi 
Correcteur : Marianne

Description du programme: Le programme ci-dessous répond au problème 1.
Ce porgramme permet de compiler sur un microprocesseur atmega 324 
qui incrémente un compteur 10 fois par seconde et change le comportement d'une LED en fonction du bouton poussoir blanc sur le breadboard. 
Le programme  contrôle la del  par demande d'interruption externe 0 (INT0_vect) en connectant le signal de sortie au port PD2 de la carte mere. 
Nous avons utilisé une fonction "clignoter" qui permet a la DEL de s'allumer et s'éteintdre dépendamment de la valeur du compteur au rythme de 2 fois par seconde.
afin de traiter le problème de debounce, nous avons inclus un délais anti_rebond de 30 ms dans la fonction ISR de l'interruption du Boutton.

Identifications matérielles (Broches I/O):
INT 0/1: PD2; DDRD --> Ces input prennent comme valeur 0 ou 1 afin de savoir si le courant passe ou non.
Analog Digital Converter: PB0; PB1; DDRB --> Ces Output ressort le courant conduit par le bouton poussoir Blanc . 
PB0 ressort le courant afin d'allumer la DEL bicoolore en vert et PB1 allume la DEL bicolore en rouge
On réfère PD2 au bouton poussoir blanc sur le breadboard.
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
volatile bool bouttonappuie = false;

//routine d'interruption mode Any edge
ISR(INT0_vect)
{

    _delay_ms(30);
    bouttonappuie = (PIND & (1 << PD2));
    EIFR |= (1 << INTF0);
}

//routine d'initialisation
void initialisationInt0()
{

    cli();
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);

    sei();
}

void clignoter(uint8_t nbFois, const int lumiere)
{
    for (int i = 0; i < nbFois; i++)
    {
        PORTB = lumiere;
        _delay_ms(250);
        PORTB = 0x00;
        _delay_ms(250);
    }
}

int main()
{
    const int LUMIERE_ETEINTE = 0x00;
    const int LUMIERE_ROUGE = (1 << PB1);
    const int LUMIERE_VERTE = (1 << PB0);
    uint8_t compteur = 0;
    initialisationInt0();
    DDRB = 0xff;
    DDRD = 0x00;
    while (!bouttonappuie)
    {
    }
    while (bouttonappuie == true && compteur < 120)
    {
        compteur++;
        _delay_ms(100); // 1/10 secondes , t = 0 compteur=1 --> t= 0.1secondes compteur= 1
    }

    clignoter(1, LUMIERE_VERTE);
    _delay_ms(2000);
    clignoter(compteur / 2, LUMIERE_ROUGE);
    PORTB = LUMIERE_VERTE;
    _delay_ms(1000);
    PORTB = LUMIERE_ETEINTE;

    return 0;
}