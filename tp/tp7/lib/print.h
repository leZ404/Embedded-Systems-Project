#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

class Print
{
public:
    Print();
    ~Print();
    void USART_Init(const int baud);
    void afficherCaractere(unsigned char donnees);
    void afficherChaineCaractere(const char *donnees, int longueur);
    void afficherChaineCaractere2(const char *donnees);


};