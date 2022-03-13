
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdio.h>
#include<stdlib.h>
#include<Moteur.h>
#include<print.h>
#include<DEL.h>

//#define printf(args) custom_rs232_printf args

// Utilisation:


int main()         
{
  DDRB |= 0xff;
  DDRD |= 0x00;
  
  //test Print.cpp affichage
  //Print p; 
  //p.USART_Init()   // faut trouver le param (voir discord)
  
   // unsigned char c ='k' ; 
  // const char * str = "This is a string literal. See the double quotes?";
 // p.afficherChaineCaractere2(str);
  //p.afficherCaractere(c);



while(true)
{
    //test moteur ( on fait tourner la roue droite puis roue gauche puis les 2 ensemble au rythme de 50% et en fin stop)
     Moteur moteur(PB5,PB6);
    moteur.ajustementPwmNavigation(50,0);
   _delay_ms(5000);
    moteur.ajustementPwmNavigation(0,50);
      _delay_ms(5000);
    moteur.ajustementPwmNavigation(50,50);
    _delay_ms(5000);
     moteur.ajustementPwmNavigation(0,0);
      moteur.avancer();    // moteur avance a 100%
    _delay_ms(5000);
      moteur.reculer();  // moteur recule a 100%
      _delay_ms(5000);

    //test LED 
     Del led; 
    led.clignoter(10,LUMIERE_VERTE);       
    led.clignoter(10,LUMIERE_ROUGE);
    led.SetCouleurLumiere(Etat::VERT);      // allumer del en vert pendant 5 sec 
    _delay_ms(5000);
     led.SetCouleurLumiere(Etat::ROUGE);     // allumer del en rouge pendant 5 sec 
        _delay_ms(5000);


}
    
}

// ya une errur ds le makefile que je comprend pas mais toutes les fcts marchent si vous les essayer en solo 
// avec la boucle  while ca marchait partiellement jsp pk 
// reste a tester print (trouver le param a passer le reste est simple) , memoire et can je ne vois pas comment les tester
//faut que le tout soit en francais ou en anglais ( pas de frenglish )
// les nom en camelUpcase
// force a vouuss guyys