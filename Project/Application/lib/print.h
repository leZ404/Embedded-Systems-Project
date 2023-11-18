#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <memoire_24.h>

class Print
{
public:
    Print();  // constructeur 
 //  ~Print(); // ne pas commenter les destructeurs non implementes ne fait pas fonctionner les test (erreur au niveau du make)
   
   // initialisation de USART
 void USART_Init();

    // fonction pour afficher un caractere 
    void afficherCaractere( const char donnees);

    // fonction pour afficher un  uint8_t

    void afficherEntier8bit (uint8_t donnees);

    // fonction pour afficher un uint16_t 

    void afficherEntier16bit (uint16_t donnees);


// fonction qui utilise la fonction precedente pour afficher une chaine de caractere 

    void afficherChaineCaractere(const char *donnees);


unsigned char USART_Receive( void );

void USART_Transmit( unsigned char data );

};
