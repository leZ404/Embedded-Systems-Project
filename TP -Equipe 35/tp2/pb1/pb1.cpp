// Travail : TRAVAIL_PRATIQUE 2
//Section # : 02
//Équipe # : EQUIPE_NO 35
// Correcteur : Marianne

// Description du programme: Le programme ci-dessous répond au problème 1.
//Ce porgramme permet compiler sur un microprocesseur atmega 324 une machine à état(voir ci-dessous)
//imposer par l'énoncé qui passe la couleur d'une LED entre rouge et noir en fonction du bouton où l'on appuie entre les boutons D2 et D3.
//Le programme prend en compte l'état courant afin de savoir quel sera l'état prochain.
//On remarquera que à l'état initial la DEl est éteinte. Afin de traiter le problème de debounce,
//nous avons utilisé une fonction appuiBouton et l'on a inclus un délais anti_rebond de 10 ms.
// Aussi nous avons déclarer nos 4 états ETEINT, INTERM1, INTERM2, ROUGE afin de pouvoir les réferer à notre switch (etatCourant)

//Identifications matérielles (Broches I/O):
//
//INT 0/1: PIND2; PIND3; DDRD --> Ces input prennent comme valeur 0 ou 1 afin de savoir si le courant passe ou non.
//Analog Digital Converter: PA1; DDRA --> Cet Output ressort le courant conduit par les boutons poussoirs
// et qui a été traité par le microprocesseur atmega afin d'allumer la LED en rouge ou pas.
//On réfère PIND2 au bouton poussoir D2 (bouton du haut voir simulIDE) et PIND3 au bouton poussoir D3 (bouton du bas voir simulIDE).
//Notre circuit est composé d'Une alimentation de 5 volts, 1 resistor à 1 MOhm et 1 résistor à 10kOhm pour chaque bouton poussoir
// Il y a aussi une résistance de 1.5 Kohm au niveau de la portion DDRA branché en série avec la DEL bicolore.

// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | Problème1 |                |                |  |  | Problème2 |                |                |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | ROUGE,   INTERM1, INTERM2, ETEINT             |  |  | ROUGE, VERT, ETEINT        |                |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// |           |                |                |  |  |           |                |                |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | Entrées   | Etats prochain | Etats présents |  |  | Entrées   | Etats prochain | Etats présents |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D3        | ETEINT         | ETEINT         |  |  | D3        | VERT           | ROUGE          |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D2        | INTERMF1         | ETEINT         |  |  | D2        | VERT           | ROUGE          |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D3        | ETEINT         | INTERM1         |  |  | D3        | ETEINT         | VERT           |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D2        | INDTERM2         | INTERM1         |  |  | D2        | ROUGE          | VERT           |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D3        | ETEINT         | INTERM2         |  |  | D3        | VERT           | ETEINT         |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D2        | ROUGE          | INTERM2         |  |  | D2        | ROUGE          | ETEINT         |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D3        | ETEINT         | ROUGE          |  |  |           |                |                |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+
// | D2        | ETEINT         | ROUGE          |  |  |           |                |                |
// +-----------+----------------+----------------+--+--+-----------+----------------+----------------+

// Nous avons essayé de faire en sorte que le changement de couleur de la DEL bicolore
//se fasse lors de l'appui du bouton poussoir et non du relâchement mais en vain. Après avoir essayé plusieurs méthodes différentes
//nous n'avons pas réussis à atteindre cet objectif, les codes du pb1 et pb2 fonctionnent correctement
// mais le changement de couleur de fait au niveau du relâchement.

#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>

bool appuiBouton(uint8_t pinBouton)
{

    const uint8_t DELAIS_ANTIREBOND = 10;

    if (PIND & (1 << pinBouton))
    {
        _delay_ms(DELAIS_ANTIREBOND);
        if (PIND & (1 << pinBouton))
        { // traitement de l'anti-rebond dans la fonction.
            return true;
        }
        return false;
    }
}

enum class Etat
{
    ETEINT,
    INTERM1,
    INTERM2,
    ROUGE
};

int main()
{

    DDRA = 0xff;
    DDRD = 0x00;

    const int LUMIERE_ETEINTE = 0x00;
    const int LUMIERE_ROUGE = (1 << PA1);

    bool boutonEtaitAppuyeD2 = false;
    bool boutonEtaitAppuyeD3 = false;

    Etat etatCourant = Etat::ETEINT;

    for (;;)
    {

        if ((!boutonEtaitAppuyeD2) && (!boutonEtaitAppuyeD3))
        {
            switch (etatCourant)
            {
            case Etat::ETEINT:
                PORTA = LUMIERE_ETEINTE;

                if (appuiBouton(PIND2))
                {
                    etatCourant = Etat::INTERM1;
                    boutonEtaitAppuyeD2 = true;
                }

                else if (appuiBouton(PIND3))
                {
                    etatCourant = Etat::ETEINT;
                    boutonEtaitAppuyeD3 = true;
                }

                break;

            case Etat::INTERM1:
                PORTA = LUMIERE_ETEINTE;

                if (appuiBouton(PIND2))
                {
                    etatCourant = Etat::INTERM2;
                    boutonEtaitAppuyeD2 = true;
                }
                else if (appuiBouton(PIND3))
                {
                    etatCourant = Etat::ETEINT;
                    boutonEtaitAppuyeD3 = true;
                }

                break;

            case Etat::INTERM2:
                PORTA = LUMIERE_ETEINTE;

                if (appuiBouton(PIND2))
                {
                    etatCourant = Etat::ROUGE;
                    boutonEtaitAppuyeD2 = true;
                }

                else if (appuiBouton(PIND3))
                {
                    etatCourant = Etat::ETEINT;
                    boutonEtaitAppuyeD3 = true;
                }

                break;

            case Etat::ROUGE:
                PORTA = LUMIERE_ROUGE;

                if (appuiBouton(PIND2))
                {
                    etatCourant = Etat::ETEINT;
                    boutonEtaitAppuyeD2 = true;
                }

                else if (appuiBouton(PIND3))
                {
                    etatCourant = Etat::ETEINT;
                    boutonEtaitAppuyeD3 = true;
                }

                break;
            }
        }

        if (appuiBouton(PIND2) == false)
        {
            boutonEtaitAppuyeD2 = false;
        }

        if (appuiBouton(PIND3) == false)
        {
            boutonEtaitAppuyeD3 = false;
        }
    }
}
