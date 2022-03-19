#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

class Print
{
public:
    Print();  // constructeur 
   // ~Print(); / ne pas commenter les destructeurs non implementes ne fait pas fonctionner les test (erreur au niveau du make)
   
   // initialisation de USART
 void USART_Init();

    // fonction pour afficher un caractere 
    void afficherCaractere( const char donnees);

// fonction qui utilise la fonction precedente pour afficher une chaine de caractere 

    void afficherChaineCaractere(const char *donnees);


unsigned char USART_Receive( void );


};