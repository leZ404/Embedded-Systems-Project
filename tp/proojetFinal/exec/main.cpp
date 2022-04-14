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
    DDRC = 0x00;
    DDRB = 0xff;
    DDRA= 0x00;
    DDRD = 0x00;

Moteur moteur(PB5, PB6);
Bouton bouton;
//Infrarouge infrarouge;
can obstacle;

 Del del ;
 Print p; 
 Memoire24CXXX m;
 Bouton b; 

 uint16_t lumiereDroite=  obstacle.lecture(1) >> 2;  //photoresistance de droite lumiere.lecture(1)
 uint16_t lumiereGauche =  obstacle.lecture(2) >> 2; //photoresistance de gauche  lumiere.lecture(4)

 
//TEST PHOTORESISTANCE ET OBSTACLE
bool mur = true;
while(mur)
{     
    // // p.afficherEntier8bit(obstacle.lecture(2)>>2);
    // // _delay_ms(500);
    // // p.afficherCaractere('\n');
    
    //  //Test Suivi Lumiere

    //  while(obstacle.lecture(0)) < 100)
    //  {
    //      moteur.ajustementPWM(lumiereGauche, lumiereDroite);

    //  }
    //  while(obstacle.lecture(1)) < 100)
    //  {
    //      moteur.ajustementPWM(lumiereGauche, lumiereDroite);

    //  }

     //Test mode Tourner
    if (obstacle.lecture(7) < 120)
            {
                mur = !mur;
                moteur.ajustementPwmNavigation(0,0);
                _delay_ms(10000);
                break;
            }
    while(obstacle.lecture(7) > 220 && obstacle.lecture(7) < 270  )
       {
            moteur.ajustementPwmNavigation(100, 100 );
            del.clignoter(4,LUMIERE_ROUGE);
       }
        while(obstacle.lecture(7) < 220 )
       {
            moteur.ajustementPwmNavigation(100, 150 );
            del.SetCouleurLumiere(Etat::VERT);
       }

       while(obstacle.lecture(7) > 270 )
       {
            moteur.ajustementPwmNavigation(140, 100 );
            del.SetCouleurLumiere(Etat::ROUGE);
       }
    
    //moteur.ajustementPwmNavigation(100, 0);
   
    
//      if(obstacle.lecture(3) > 1020)
//     {
//   //p.afficherEntier8bit(obstacle.lecture(7)>>2);
//     del.clignoter(4,LUMIERE_ROUGE);
//    moteur.ajustementPwmNavigation(100, 0);
//     _delay_ms(500);
//     }
 
   
   // moteur.ajustementPwmNavigation(150, 150);
    //  p.afficherEntier8bit(obstacle.lecture(8)>>2);
    //  p.afficherCaractere('\n');

// if(obstacle.lecture(7) > 430)

// {
//   //  p.afficherEntier8bit(obstacle.lecture(7)>>2);
//     del.clignoter(4,LUMIERE_VERTE);
//    moteur.ajustementPwmNavigation(100, 0);
//     _delay_ms(500);
// }

}
//_delay_ms(20000);

//del.SetCouleurLumiere(Etat::ROUGE);
//_delay_ms(20000);
//del.clignoter(4,LUMIERE_VERTE);

 
  

   



// Test BOUTON:
// while(true)
// {
//     del.SetCouleurLumiere(Etat::ROUGE);
//     // if (bouton.appuiBouton(PC5))  //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//     // {
//     //     del.clignoter(15, LUMIERE_VERTE);
//     // }
//      if (bouton.appuiBouton(PC4))  //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//     {
//         del.clignoter(15, LUMIERE_ROUGE);
//     }
//  }



}