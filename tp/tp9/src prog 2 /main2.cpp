/*
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

#include <stdlib.h>
#include <print.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>

// referer les instructions a des adresses

int addresseDebut = 0x00;
const uint8_t DBT = 0x01;
const uint8_t ATT = 0x02;
const uint8_t DAL = 0x44;
const uint8_t DET = 0x45;
const uint8_t SGO = 0x48;
const uint8_t SAR = 0x09;
const uint8_t MAR = 0x60;
const uint8_t MAR_AUTRE = 0x61;
const uint8_t MAV = 0x62;
const uint8_t MRE = 0x63;
const uint8_t TRD = 0x64;
const uint8_t TRG = 0x65;
const uint8_t DBC = 0xC0;
const uint8_t FBC = 0xC1;
const uint8_t FIN = 0xFF;




int main()
{
  DDRB= 0xff; // PORTB pour la sortie de la DEL et Moteur 
  //DDRD= 0xff; // PORTD pour la sortie du son 
  Memoire24CXXX m;
  Print p; 
  Del del; 
  Moteur moteur(PB5,PB6);

  
  // Appel des variables
    uint8_t instruction;
    uint8_t op;
    bool debut = false;
    bool boucle = false;
    uint8_t nbLoop = 0;
    uint8_t adresseParcours = addresseDebut + 2; 
    uint8_t adresseDonne; //  adresse dbc


// Lecture de la m�moire sans executer les actions tant que DBT n'est pas d�tect�
while(instruction != DBT){ // si ca ne marche pas on ajoute un delay 
   m.lecture(adresseParcours, &insctruction);
   p.USART_Transmit(action);
   adresseParcours++;
    }   


if(instruction == DBT) 
  { 
    debut = true;
    del.clignoter(5, LUMIERE_VERTE);
  }

while (debut==true){
  switch (instruction){
    case DAL: //allumer Del en vert 
      del.SetCouleurLumiere(LUMIERE_VERTE);
      break;

   case DET:  //eteindre la Del 
     del.SetCouleurLumiere(LUMIERE_ETEINTE);
     break;


/*
   case SGO: // jouer sonorite
    m.lecture(adresseParcours, &op);
    p.USART_Transmit(op);
    adresseParcours++;

   case SAR: //Arreter sonorite
    son.arretNote();
     break;
*/


  case MAR: //Arreter le moteur
    moteur.arret();
    break;

  case MAR_AUTRE: //Arreter le moteur (2)
      moteur.arret();
      break; 

  case MAV: //Avancer le robot 
    m.lecture(addresseParcours, &op);
    p.USART_Transmit(op);
    addresseParcours++;
    moteur.avancer(op);
    break;

  case MRE: //Reculer le robot
  m.lecture(addresseParcours, &op);
  p.USART_Transmit(op);
  addresseParcours++;
  moteur.reculer(op);
    break;

  case TRD: //Tourner a droite
  moteur.ajustementPwmNavigation(50,0);
  break;

  case TRG: //Tourner a gauche
  moteur.ajustementPwmNavigation(0,50);
    break;

case ATT:
 memoire.lecture(adresseParcours, &op);
 uart.transmissionUART(op);
 adresseParcours++;
  for (int i = 0; i < op; i++)	
  _delay_ms(25);
  break;
  
  
case DBC:
 Debut = adresseParcours;
 Iterations = &op + 1;
 break;
case FBC:
 Iterations--;
 if(Iterations > 0) 
 {
  adresseParcours = Debut
 };
 break;

case FIN: //Fin du programme, mettre debut � false pour sortir du while
     
 moteur.arreter();
 son.arretNote();
 del.SetCouleurLumiere(LUMIERE_ETEINTE);           
 debut= false;
 break;            
}

}

