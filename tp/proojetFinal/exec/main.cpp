#define F_CPU 8000000UL
#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>
#include <moteur.h>
#include <DEL.h>
#include <sonorite.h>
#include <bouton.h>
#include <can.h>

/*
/*Boucle de démarrage:
Bouton Interrupt pour le mode parcours, bouton blanc pour le mode reprise. Lorsqu'un bouton est appuyé, 
le choix est confirmé à l'aide de la DEL libre. Elle devra clignoter à 5 Hz pendant 3 secondes. 
En vert pour le mode suivi, en rouge pour le mode reprise.
Le robot ne fait rien d'autre pendant le clignotement. Une fois ce dernier terminé, le robot passe au mode d'opération choisi.
/*


//routine d'interruption<s
volatile bool bouttonappuie = false;
ISR(INT0_vect)
`{

    _delay_ms(30);
    bouttonappuie = true;
    EIFR |= (1 << INTF0);
    //inserer fonction mode reprise
}

//routine d'initialisation
void initialisationInt0()
{

    cli();
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01) | (1 << ISC00); // raising edge

    sei();
}



/Fin Boucle de démarrage:/

/avancement des roues en fonction des photoresistance

//Appuyer sur un bouton
Del del;
Bouton bouton;



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
    
    while (true)
    {
        //Boucle de démarrage, Mode Suivi:
        if (bouton.appuiBouton(PA0))
        {
            del.clignoter(15, LUMIERE_VERTE);
        }
        //Fin Boucle demarrage, Mode Suivi

        initialisationInt0();
        //Boucle de démarrage, Mode reprise:
        if (bouttonappuie == true && compteur < 120)
        {
            compteur++;
            _delay_ms(100); // 1/10 secondes , t = 0 compteur=1 --> t= 0.1secondes compteur= 1
            del.clignoter(15, LUMIERE_ROUGE);
        }


        // //Boucle de démarrage, Mode Reprise
        //  if (bouton.appuiBouton(PA0))
        // {
            
        // }
    }
   
}
*/


const uint16_t MAX_CAN = 1024;

//Appuyer sur un bouton 

int main()
{
  //  DDRC = 0xff;
     DDRB = 0xff;
     DDRA= 0x00;
//  PORTC = (1<<PC2);
 Moteur moteur(PB5, PB6);
Bouton bouton;
//Infrarouge infrarouge;
 //can lumiere=  can();
can obstacle=  can();

 Del del ;
 Print p; 
 Memoire24CXXX m;


 uint16_t lumiereDroite=  1002 >> 2;  //photoresistance de droite lumiere.lecture(1)
 uint16_t lumiereGauche =  1024 >> 2; //photoresistance de gauche  lumiere.lecture(4)


 //moteur.avancer(200);
//moteur.ajustementPwmNavigation( pourcentageLumiereDroite,  pourcentageLumiereGauche);

while(true)
{
     del.SetCouleurLumiere(Etat::VERT);
     _delay_ms(3000);

    del.SetCouleurLumiere(Etat::ROUGE);
    moteur.ajustementPwmNavigation(140, 140);
  

if(obstacle.lecture(7) > 320)
{
    del.SetCouleurLumiere(Etat::ETEINT);
   moteur.ajustementPwmNavigation(65, 0);
    _delay_ms(2000);
   //moteur.avancer(230);
   // moteur.ajustementPwmNavigation(70, 45);

}

}
_delay_ms(20000);

del.SetCouleurLumiere(Etat::ROUGE);
_delay_ms(20000);
del.clignoter(4,LUMIERE_VERTE);

 
  

   }

// while(true)
// {
//     PORTC = (1<<PC2);

//     if (bouton.appuiBouton(PA2))  //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//     {
//         del.clignoter(15, LUMIERE_ROUGE);
//     }
// }
// if (boutonInterrupt)  //mode suivi
// {
//     del.clignoter(15, LUMIERE_VERTE);
// }


