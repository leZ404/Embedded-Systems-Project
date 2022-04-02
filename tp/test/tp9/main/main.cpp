
#define F_CPU 8000000UL
#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>
#include <Moteur.h>
#include <DEL.h>
#include <sonorite.h>
#include <bouton.h>

/*Boucle de démarrage:
Bouton Interrupt pour le mode parcours, bouton blanc pour le mode reprise. Lorsqu'un bouton est appuyé, 
le choix est confirmé à l'aide de la DEL libre. Elle devra clignoter à 5 Hz pendant 3 secondes. 
En vert pour le mode suivi, en rouge pour le mode reprise.
Le robot ne fait rien d'autre pendant le clignotement. Une fois ce dernier terminé, le robot passe au mode d'opération choisi.
*/



/*Fin Boucle de démarrage:*/

/*avancement des roues en fonction des photoresistance*/
Del del;
Moteur moteur(PB5, PB6);
Bouton bouton;
// Infrarouge infrarouge;
// Can lumiere= can();
// Photoresistance photoresistance= can();

// pourcentageLumiereDroite = lumiere.lecture(1)/1024 * 100;  //photoresistance de droite
// pourcentageLumiereGauche = lumiere.lecture(4)/1024 * 100; //photoresistance de gauche

// moteur.ajustementPwmNavigation(uint8_t pourcentageLumiereDroite, uint8_t pourcentageLumiereGauche);



//Appuyer sur un bouton 
int main()
{

DDRA |= 0x00;
DDRC |= 0xff;
if (bouton.appuiBouton(PA4))
{
    PORTC = (1 << PC2);
}

// if (boutonInterrupt)  //mode suivi
// {
//     del.clignoter(15, LUMIERE_VERTE);   
// }

// pourcentageLumiereDroite = lumiere.lecture(1)/1024 * 100;  //photoresistance de droite
// pourcentageLumiereGauche = lumiere.lecture(4)/1024 * 100; //photoresistance de gauche

// moteur.ajustementPwmNavigation(uint8_t pourcentageLumiereDroite, uint8_t pourcentageLumiereGauche);

}