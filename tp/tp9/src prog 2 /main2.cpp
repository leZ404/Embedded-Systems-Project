/**
Travail : TRAVAIL_PRATIQUE 9
Section # : 02
Équipe # : EQUIPE_NO 3544
Auteurs : Ryan Lahbabi , Zied Kaabi, Ashveer Golam, Omar Bamrim 
Correcteur : Jerome Collin 

Notre coregraphie ne fonctionne pas parfaitement malheureusement malgre que nos fonctions marchent toutes lorsqu on les testent individuellement
et meme apres avoir essayer beaucoup de methodes, les charges non plus n'ont pas reussis a nous aider davantage.
 Merci de votre comprehension.

| Instruction binaire | mnémonique | Description                  |
|---------------------|------------|------------------------------|
| 0000 0001           | dbt        | début                        |
| 0000 0010           | att        | attendre                     |
| 1 000 100           | dal        | allumer la DEL               |
| 1 000 101           | det        | éteindre la DEL              |
| 1 001 000           | sgo        | jouer une sonorité           |
| 0000 1001           | sar        | arrêter de jouer la sonorité |
| 1 100 000           | mar        | arrêter les moteurs          |
| 1 100 001           | mar        | arrêter les moteurs          |
| 1 100 010           | mav        | avancer                      |
| 1 100 011           | mre        | reculer                      |
| 1 100 100           | trd        | tourner à droite             |
| 1 100 101           | trg        | tourner à gauche             |
| 11 000 000          | dbc        | début de boucle              |
| 11 000 001          | fbc        | fin de boucle                |
| 11 111 111          | fin        | fin                          |

*/
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

//referer les instructions a des adresses

uint16_t addresseInitiale = 0x00;
const uint16_t DBT = 0x01;
const uint16_t ATT = 0x44;
const uint16_t DAL = 0x02;
const uint16_t DET = 0x45;
const uint16_t SGO = 0x48;
const uint16_t SAR = 0x09;
const uint16_t MAR = 0x60;
const uint16_t MAR_AUTRE = 0x61;
const uint16_t MAV = 0x62;
const uint16_t MRE = 0x63;
const uint16_t TRD = 0x64;
const uint16_t TRG = 0x65;
const uint16_t DBC = 0xC0;
const uint16_t FBC = 0xC1;
const uint16_t FIN = 0xFF;

int main()
{
    DDRB = 0xff; // PORTB pour la sortie du Moteur
    DDRD= 0xff;  // PORTD pour la sortie du son
    DDRC= 0xff; // PORTC pour la sortie de la DEL
    

    Memoire24CXXX m;
    Print p;
    Del del;
    Moteur moteur(PB5, PB6);
    Sonorite son;
    // Appel des variables
    uint8_t instruction = 0;
    uint8_t operande;
    uint8_t iterations = 0;
    uint8_t adresseParcours = 0x00;
    bool debut  = false;
    uint16_t addresseBoucle =0x00;

    // Lecture de la memoire sans executer les actions tant que DBT n'est pas detecte
    while (instruction != DBT)
    { // si ca ne marche pas on ajoute un delay
        m.lecture(adresseParcours, &instruction);
        _delay_ms(5);
        adresseParcours++;
        m.lecture(adresseParcours, &operande);
        _delay_ms(5);
        adresseParcours++;

    }

    // Routine de debut : clignoter la del 5 fois au rythme de 2 fois par sec (lumiere Verte)
    
    debut = true;
    del.clignoter(5, LUMIERE_VERTE);
    

    while (debut == true)
    {
        m.lecture(adresseParcours, &instruction);
        _delay_ms(5);
        
        m.lecture(adresseParcours+1, &operande);
            _delay_ms(5);
       
        
   switch (instruction)
        {
            
        case DAL:       //allumer Del en vert 

            del.SetCouleurLumiere(Etat::ROUGE);
            p.afficherChaineCaractere("DAL ");
            break;

        case DET:       //eteindre la Del

            del.SetCouleurLumiere(Etat::ETEINT);
          p.afficherChaineCaractere("DET ");

            break;

    
        case SGO:       // jouer sonorite

            if ( (operande < 45) || (operande > 81) )
            {
                adresseParcours++;
                break;
            }
            son.jouerNote(operande);
            p.afficherChaineCaractere("SGO ");
            break;

        case SAR:       //Arreter sonorite

            son.arret();
            p.afficherChaineCaractere("SAR ");

            break;

        case MAR_AUTRE:

            moteur.arret();
            p.afficherChaineCaractere("MAR1 ");
            break;  

        case MAR:       //Arreter le moteur

            moteur.arret();
            p.afficherChaineCaractere("MAR ");
            break;

        case MAV:     //Avancer le robot

            moteur.avancer(operande);
             p.afficherChaineCaractere("MAV ");

            break;

        case MRE:    //Reculer le robot

            moteur.reculer(operande);
            p.afficherChaineCaractere("MRE ");
            break;

        case TRD:    //Tourner a droite

            moteur.ajustementPwmNavigation(50, 0);
            p.afficherChaineCaractere("TRD ");
            break;

        case TRG:    //Tourner a gauche

            moteur.ajustementPwmNavigation(0, 50);
            p.afficherChaineCaractere("TRG ");

            break;

        case ATT:    //attendre pendant un certain temps ( op * 25 ms)

            for (int i = 0; i < operande; i++)
                _delay_ms(25);
                p.afficherChaineCaractere("att ");
            break;

        case DBC:    // Debut de boucle avec op = nb d iterations 

            addresseBoucle = adresseParcours;
            iterations = operande;
            p.afficherChaineCaractere("dbc ");
            break;

        case FBC:    //fin de boucle 
            iterations--;
            p.afficherEntier8bit(iterations);
            if (iterations > 0)
            {
                adresseParcours = addresseBoucle;
            }
            p.afficherChaineCaractere("fbc ");
            break;

        case FIN:    //Fin du programme, mettre debut a false pour sortir du while

            moteur.arret();
            son.arret();
            del.SetCouleurLumiere(Etat::ETEINT);
            debut = false;
            p.afficherChaineCaractere("FIN");
            break;
        }

    adresseParcours += 2;
    }

    
    
}
