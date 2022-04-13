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


/avancement des roues en fonction des photoresistance

//Appuyer sur un bouton
Del del;
Bouton bouton;


*/

const uint16_t MAX_CAN = 1024;

//Appuyer sur un bouton

int main()
{
    DDRC = 0x00;
    DDRB = 0xff;
    DDRA = 0x00;
    DDRD = 0x00;

    Moteur moteur(PB5, PB6);
    Bouton bouton;
    //Infrarouge infrarouge;
    can obstacle;

    Del del;
    Print p;
    Memoire24CXXX m;
    Bouton b;

    uint16_t lumiereDroite ; //photoresistance de droite lumiere.lecture(1)
    uint16_t lumiereGauche ; //photoresistance de gauche  lumiere.lecture(4)

    //TEST PHOTORESISTANCE ET OBSTACLE

    while(true)
     {
    //        lumiereDroite = (obstacle.lecture(2) >> 2) +20 ; //photoresistance de droite lumiere.lecture(1)
    //         lumiereGauche = (obstacle.lecture(4) >> 2 ); //photoresistance de gauche  lumiere.lecture(4)
    //           p.afficherCaractere('D');
    //         p.afficherEntier8bit(lumiereDroite);
    //         _delay_ms(500);
    //         p.afficherCaractere('-');
    //          p.afficherCaractere('G');
    //          p.afficherEntier8bit(lumiereGauche);
    //            p.afficherCaractere('\n');
    //     while(obstacle.lecture(2) > 700 || obstacle.lecture(4) > 700)
    //     {

    //         lumiereDroite = (obstacle.lecture(2) >> 2) +20 ; //photoresistance de droite lumiere.lecture(1)
    //         lumiereGauche = (obstacle.lecture(4) >> 2 ); //photoresistance de gauche  lumiere.lecture(4)
    //         moteur.ajustementPwmNavigation(lumiereGauche, lumiereDroite );         // roue gauche = roue droite * 0.85
    //          p.afficherCaractere('D');
    //         p.afficherEntier8bit(obstacle.lecture(2));
    //         _delay_ms(500);
    //         p.afficherCaractere('-');
    //          p.afficherCaractere('G');
    //          p.afficherEntier8bit(obstacle.lecture(4));
    //            p.afficherCaractere('\n');
    //     }
    //     moteur.ajustementPwmNavigation(0, 0);   
    // }
   //   moteur.ajustementPwmNavigation(100, 100 );
   //   _delay_ms(500000);
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

     
       
       
        // while(700 >obstacle.lecture(7) >430 )
        // {

        //     lumiereDroite = (obstacle.lecture(7) >> 2); //photoresistance de droite lumiere.lecture(1)
        //     moteur.ajustementPwmNavigation(100, 85 );
        //     _delay_ms(1250);
        
        // }
        // while(obstacle.lecture(7)>700 )
        // {
        //     moteur.ajustementPwmNavigation(0, 0); 
        // }  
    
}
}

//Demi TOUR
//  while(obstacle.lecture(7)< 70 )
//        {

//          //   del.clignoter(4,LUMIERE_ROUGE);
//            //lumiereDroite = (obstacle.lecture(7) >> 2); //photoresistance de droite lumiere.lecture(1)
//            moteur.ajustementPwmNavigation(100, 140 );
          

//        }

//Avancer tout droit
//     while(obstacle.lecture(1) > 500 && obstacle.lecture(2) > 500))
//     {
//         lumiereDroite=  (obstacle.lecture(2) >> 2) + 20;
//         lumiereGauche =  (obstacle.lecture(2) >> 2) + 20;
//         moteur.ajustementPwmNavigation(lumiereDroite, lumiereGauche)
             
//     }>



    /*
     while(obstacle.lecture(1) > 100)
     {
         moteur.ajustementPwmNavigation(lumiereGauche, lumiereDroite);
         p.afficherCaractere('2');
                  p.afficherEntier8bit(lumiereGauche);
                p.afficherCaractere('\n');
                 p.afficherEntier8bit(lumiereDroite);


    }
*/
//Test mode Tourner

//moteur.ajustementPwmNavigation(100, 0);

// // if ((obstacle.lecture(7)) > 430 )
// // {
// //     del.SetCouleurLumiere(Etat::ROUGE);
// // }
// // else
// // {
// //     del.SetCouleurLumiere(Etat::VERT);
// // }

/*
    moteur.ajustementPwmNavigation(220,100);
    _delay_ms(5000);
     moteur.ajustementPwmNavigation(0,100);
     p.afficherChaineCaractere("droite ");
         p.afficherCaractere('\n');
    

    _delay_ms(5000);
     moteur.aj{
    initialisation();    

    
    whileustementPwmNavigation(100,0);
     p.afficherChaineCaractere("gauche");
      p.afficherCaractere('\n');
    

    _delay_ms(5000);
     moteur.ajustementPwmNavigation(-200,-200);
        _delay_ms(5000);
        moteur.reculer(90);

    */
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

// if(obstacle.lecture(7) > 430)    while (true)
//     {
//         if (bouton.appuiBouton(PA4)) //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//         {
//             del.clignoter(15, LUMIERE_VERTE);
//         }
//         else{
//             del.SetCouleurLumiere(Etat::ROUGE);
//         }
//         //      if (bouton.appuiBouton(PC4))  //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//         //     {
//         //         del.clignoter(15, LUMIERE_ROUGE);
//         //     }
//         //  }
//     }
// }


// {
//   //  p.afficherEntier8bit(obstacle.lecture(7)>>2);
//     del.clignoter(4,LUMIERE_VERTE);
//    moteur.ajustementPwmNavigation(100, 0);
//     _delay_ms(500);
// }

//_delay_ms(20000);

//del.SetCouleurLumiere(Etat::ROUGE);
//_delay_ms(20000);
//del.clignoter(4,LUMIERE_VERTE);

// Test BOUTON:
//     while (true)
//     {
//         if (bouton.appuiBouton(PA4)) //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//         {
//             del.clignoter(15, LUMIERE_VERTE);
//         }
//         else{
//             del.SetCouleurLumiere(Etat::ROUGE);
//         }
//         //      if (bouton.appuiBouton(PC4))  //mode reprise,   doit durer 3 secondes donc 6 clignotement avec des délais de 200 comme dans la classe
//         //     {
//         //         del.clignoter(15, LUMIERE_ROUGE);
//         //     }
//         //  }
//     }
// }


// case Etat::DEBUT_PARCOURS:
//                         while (obstacle() < DISTANCE_20CM)
//                         {
//                             moteur.ajustementPwmNavigation(AVANCER_DROIT, AVANCER_GAUCHE);
//                             memoireExterne.ecriture(count++, MAV);
//                         }