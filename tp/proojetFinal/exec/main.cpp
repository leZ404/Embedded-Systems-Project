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
<<<<<<< HEAD
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

    uint16_t lumiereDroite = obstacle.lecture(2) >> 2; //photoresistance de droite lumiere.lecture(1)
    uint16_t lumiereGauche = obstacle.lecture(1) >> 2; //photoresistance de gauche  lumiere.lecture(4)

    //TEST PHOTORESISTANCE ET OBSTACLE

    while (true)
    {
        // Fonction suivi lu;iere
        //  moteur.ajustementPwmNavigation(170,200);         // roue gauche = roue droite * 0.85
        //     _delay_ms(5000);
        //   moteur.ajustementPwmNavigation(150,0);
        //      _delay_ms(1500);
        // p.afficherEntier8bit(obstacle.lecture(2)>>2);
        // _delay_ms(500);
        // p.afficherCaractere('\n');

        //      //Test Suivi Lumiere

        //   uint16_t lumiereDroite; //photoresistance de droite lumiere.lecture(1)
        //  uint16_t lumiereGauche;//photoresistance de gauche  lumiere.lecture(4)
        //moteur.avancer(150);
        moteur.ajustementPwmNavigation(200, 200);
        _delay_ms(50000);
    }
}
//Avancer tout droit
//     while(obstacle.lecture(1) > 500 && obstacle.lecture(2) > 500))
//     {
//         lumiereDroite=  (obstacle.lecture(2) >> 2) + 20;
//         lumiereGauche =  (obstacle.lecture(2) >> 2) + 20;
//         moteur.ajustementPwmNavigation(lumiereDroite, lumiereGauche)

//     }>
// //Virage leger a droite

//         while(obstacle.lecture(0) < 400)
//           {
//             lumiereGauche =  (obstacle.lecture(1) >> 2) + 20;
//             lumiereDroite=  (obstacle.lecture(2) >> 2) + 20;
//               p.afficherCaractere('X');
//                p.afficherEntier8bit(lumiereGauche);
//              p.afficherCaractere('-');
//             p.afficherEntier8bit(lumiereDroite);
//             p.afficherCaractere('X');
//              p.afficherCaractere('\n');
//              _delay_ms(500);
//          }
//     }
// }

//    while(obstacle.lecture(1) > 500 && obstacle.lecture(2) > 500))
//       {
//         lumiereDroite=  (obstacle.lecture(2) >> 2) + 20;
//         lumiereGauche =  (obstacle.lecture(2) >> 2) + 20;
//         moteur.ajustementPwmNavigation(lumiereDroite, lumiereGauche);
//              p.afficherEntier8bit(lumiereGauche);
//              p.afficherCaractere('-');
//             p.afficherEntier8bit(lumiereDroite);

//              _delay_ms(500);
//             // p.afficherCaractere('\n');
//             // p.afficherEntier8bit(obstacle.lecture(2));
//             // _delay_ms(500);
//              p.afficherCaractere('\n');

//         }

/*
     while(obstacle.lecture(1) > 100)
     {
         moteur.ajustementPwmNavigation(lumiereGauche, lumiereDroite);
         p.afficherCaractere('2');
                  p.afficherEntier8bit(lumiereGauche);
                p.afficherCaractere('\n');
                 p.afficherEntier8bit(lumiereDroite);
=======
    for (int i = 0; i < nbFois; i++)
    {
        PORTB = lumiere;
        _delay_ms(250);
        PORTB = 0x00;
        _delay_ms(250);
    }
}

>>>>>>> 2975e3bf94c8935d76972ebed41edeca9d72118a


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

can obstacle;
 uint16_t lumiereDroite()
 {return ((obstacle.lecture(3) >> 2)+20); } //photoresistance de droite lumiere.lecture(1) 
 uint16_t lumiereGauche()
 {return  obstacle.lecture(5) >> 2;} //photoresistance de gauche  lumiere.lecture(4)}

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


 Del del ;
 Print p; 
 Memoire24CXXX m;
 Bouton b; 



 
//TEST PHOTORESISTANCE ET OBSTACLE
bool mur = true;
 while(mur)

 {     
        while( obstacle.lecture(7) > 220 &&  obstacle.lecture(7) < 270  )
        {
            moteur.ajustementPwmNavigation(100, 100 );
            del.clignoter(4,LUMIERE_ROUGE);
        }
        
        while( obstacle.lecture(7) < 220 )// &&  obstacle.lecture(7) > 120 )
        {
            moteur.ajustementPwmNavigation(100, 130 );
            del.SetCouleurLumiere(Etat::VERT);
        }
           
        while( obstacle.lecture(7) > 270 )
        {
            moteur.ajustementPwmNavigation(150, 100 );
            del.SetCouleurLumiere(Etat::ROUGE);
        }
        
        // if (obstacle.lecture(7) < 120) 
        // {
        //     mur = !mur;
        //     moteur.ajustementPwmNavigation(0, 0 );
        //     del.clignoter(15,LUMIERE_VERTE);
        //     _delay_ms(10000);
        // }

//   p.afficherCaractere('D');  
//             p.afficherEntier8bit(lumiereDroite());  
//             _delay_ms(500); 
//             p.afficherCaractere('-');   
//              p.afficherCaractere('G');  
//              p.afficherEntier8bit(lumiereGauche()); 
//                p.afficherCaractere('\n');
// //  moteur.ajustementPwmNavigation(lumiereGauche() , lumiereDroite() +50 );         // roue gauche = roue droite * 0.85  
//              p.afficherCaractere('D');  
//             p.afficherEntier8bit(lumiereDroite());  
//            _delay_ms(500); 
//             p.afficherCaractere('-');   
//              p.afficherCaractere('G');  
//              p.afficherEntier8bit(lumiereGauche()); 
//                p.afficherCaractere('\n');

//                 while (lumiereGauche()>130)
//             {

//                 moteur.ajustementPwmNavigation(lumiereGauche() +70, lumiereDroite()-40);    
//                    p.afficherCaractere('D');  
//             p.afficherEntier8bit(lumiereDroite());  
//            _delay_ms(500); 
//             p.afficherCaractere('-');   
//              p.afficherCaractere('G');  
//              p.afficherEntier8bit(lumiereGauche()); 
//                p.afficherCaractere('\n');
//             }

//          while((lumiereDroite() > 150) && lumiereGauche() > 120)
//          {
//                 p.afficherCaractere('D');  
//             p.afficherEntier8bit(lumiereDroite());  
//             moteur.ajustementPwmNavigation(lumiereGauche() +20, lumiereDroite()); 
//            _delay_ms(500); 
//             p.afficherCaractere('-');   
//              p.afficherCaractere('G');  
//              p.afficherEntier8bit(lumiereGauche()); 
//                p.afficherCaractere('\n');

//            // lumiereDroite = ((obstacle.lecture(3) >> 2) + 20); //photoresistance de droite lumiere.lecture(1) 
            
//             //umiereGauche = (obstacle.lecture(5) >> 2 ); //photoresistance de gauche  lumiere.lecture(4)    
//             while (lumiereDroite()>200 && lumiereDroite()> 180 )
//             {

//                 moteur.ajustementPwmNavigation(lumiereGauche() -50, lumiereDroite());    
//                    p.afficherCaractere('D');  
//             p.afficherEntier8bit(lumiereDroite());  
//           //  _delay_ms(500); 
//             p.afficherCaractere('-');   
//              p.afficherCaractere('G');  
//              p.afficherEntier8bit(lumiereGauche()); 
//                p.afficherCaractere('\n');
//             }

            

//                 // roue gauche = roue droite * 0.85  
//              p.afficherCaractere('D');  
//             p.afficherEntier8bit(lumiereDroite());  
//          _delay_ms(500); 
//             p.afficherCaractere('-');   
//              p.afficherCaractere('G');  
//              p.afficherEntier8bit(lumiereGauche()); 
//                p.afficherCaractere('\n');


        //  }
        //   moteur.ajustementPwmNavigation(0, 0 );    
            
//  moteur.ajustementPwmNavigation(0,0);       
    // p.afficherEntier8bit(obstacle.lecture(2)>>2);
    // _delay_ms(500);
    // p.afficherCaractere('\n');
    
     //Test Suivi Lumiere

    //  while(obstacle.lecture(0)) < 100)
    //  {
    //      moteur.ajustementPWM(lumiereGauche, lumiereDroite);

    //  }
    //  while(obstacle.lecture(1)) < 100)
    //  {
    //      moteur.ajustementPWM(lumiereGauche, lumiereDroite);

    //  }

     //Test mode Tourner
    // if (obstacle.lecture(7) < 120)
    //         {
    //             mur = !mur;
    //             moteur.ajustementPwmNavigation(0,0);
    //             _delay_ms(10000);
    //             break;
    //         }
    // while(obstacle.lecture(7) > 220 && obstacle.lecture(7) < 270  )
    //    {
    //         moteur.ajustementPwmNavigation(100, 100 );
    //         del.clignoter(4,LUMIERE_ROUGE);
    //    }
    //     while(obstacle.lecture(7) < 220 )
    //    {
    //         moteur.ajustementPwmNavigation(100, 150 );
    //         del.SetCouleurLumiere(Etat::VERT);
    //    }

    //    while(obstacle.lecture(7) > 270 )
    //    {
    //         moteur.ajustementPwmNavigation(140, 100 );
    //         del.SetCouleurLumiere(Etat::ROUGE);
    //    }
    
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

<<<<<<< HEAD
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
=======
// if(obstacle.lecture(7) > 430)
>>>>>>> 2975e3bf94c8935d76972ebed41edeca9d72118a

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