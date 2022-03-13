#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <Moteur.h>
#include <print.h>
#include <DEL.h>
#include <bouton.h>
//#define printf(args) custom_rs232_printf args
// Utilisation:
int main()
{
    DDRB |= 0xff;
    DDRD |= 0x00;

    // test LED

    Del led;
    Bouton b;
    led.clignoter(10, LUMIERE_VERTE);
    led.clignoter(10, LUMIERE_ROUGE);
    led.SetCouleurLumiere(Etat::VERT); // allumer del en vert pendant 5 sec
    _delay_ms(5000);
    led.SetCouleurLumiere(Etat::ROUGE); // allumer del en rouge pendant 5 sec
    _delay_ms(5000);
    led.SetCouleurLumiere(Etat::ETEINT); // allumer del en rouge pendant 5 sec

    // test moteur ( on fait tourner la roue droite puis roue gauche puis les 2 ensemble au rythme de 50% et en fin stop)
    Moteur moteur(PB5, PB6);
    moteur.ajustementPwmNavigation(50, 0);
    _delay_ms(5000);
    moteur.ajustementPwmNavigation(0, 50);
    _delay_ms(5000);
    moteur.ajustementPwmNavigation(50, 50);
    _delay_ms(5000);
    moteur.ajustementPwmNavigation(0, 0);
    moteur.avancer(); // moteur avance a 100%
    _delay_ms(5000);
    moteur.reculer(); // moteur recule a 100%
    _delay_ms(5000);

    
    //test bouton : allumer la led  ( lumiere rouge) a l appui du bouton Interrupt (liee au pin PD2)
    while (true)
    {

        if (b.appuiBouton(PD2))
        {
            led.SetCouleurLumiere(Etat::ROUGE);
        }
    }

    //test Print.cpp affichage
    /*
  Print p; 
  p.USART_Init()   // faut trouver le param (voir discord)

   unsigned char c ='k' ; 
  const char * str = "This is a string literal. See the double quotes?";
 p.afficherChaineCaractere2(str);
  p.afficherCaractere(c);
*/
}