#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define ALL_IN 0xff
#define ALL_OUT 0x00

/**
 * Travail : TRAVAIL_PRATIQUE 02
 * Section # : SECTION 2 
 * Équipe # : EQUIPE_NO_44
 * Correcteur : 
 * Le programme qui suit répond au problème 1 et retranscrit sur le microprocesseur la table des états qui suivra grâce à un enum class et l’emploi du switch case. Le programme fait en sorte que la DEL liée au microprocesseur est éteinte à l'état initia.l 
 * Les Data Direction Register du  port D (DDRD) sont initialisés à 1 de manière à ce que le premier bouton poussoir soit lié au PIND2 et que le deuxieme soit lié au PIND3
 * Les Data Direction Register du  port A (DDRA) sont initialisés à 0 de manière à ce que les PORTA0 et PORTA1 sont lié a la LED bicolore si le courant passe par PORTA0 la LED est rouge et est verte quand celui-ci passe par le PORTA1
 * 
 * 
 +---------------+----+----+--------------+------------+
| Etat présent  | D2 | D3 | Etat suivant | Sortie DEL |
+---------------+----+----+--------------+------------+
| INIT          | 0  | 0  | INIT         | ÉTEINT     |
+---------------+----+----+--------------+------------+
| INIT          | x  | 1  | INIT         | ÉTEINT     |
+---------------+----+----+--------------+------------+
| INIT          | 1  | 0  | ETAT1        | ÉTEINT     |
+---------------+----+----+--------------+------------+
| ETEINT1       | x  | 1  | INIT         | ÉTEINT     |
+---------------+----+----+--------------+------------+
| ETEINT1       | 1  | 0  | ETAT2        | ÉTEINT     |
+---------------+----+----+--------------+------------+
| ETEINT2       | x  | 1  | INIT         | ÉTEINT     |
+---------------+----+----+--------------+------------+
| ETEINT2       | 1  | 0  | ETAT_ROUGE   | ÉTEINT     |
+---------------+----+----+--------------+------------+
| ETAT_ROUGE    | x  | 1  | INIT         | ROUGE      |
+---------------+----+----+--------------+------------+
| ETAT_ROUGE    | 0  | 0  | INIT         | ROUGE      |
+---------------+----+----+--------------+------------+
 * */

enum class Etat
{
    INIT,
    ETEINT1,
    ETEINT2,
    ETAT_ROUGE
};

bool buttonPressed(const int pin)
{
    const uint8_t debounceTime = 10;

    const bool pinPressed = PIND & (1 << pin);

    if (pinPressed)
    {
        _delay_ms(debounceTime);

        if (PIND & (1 << pin))
        {
            return true;
        }
    }
    return false;
}

bool buttonReleased(Etat &state, Etat &oldState, const int pin)
{
    if (state == oldState)
    {
        return true;
    }

    if (buttonPressed(pin) == false)
    {
        oldState = state;
        return false;
    }

    return false;
}

const int LIGHT_OFF = 0x00;
const int RED_LIGHT = (1 << PA1);
int main()
{
    DDRA = ALL_IN;
    DDRD = ALL_OUT;

    Etat state = Etat::INIT;
    Etat oldState = Etat::INIT;



    while (true)
    {

        switch (state)
        {
        case Etat::INIT:
            PORTA = LIGHT_OFF;
            if (buttonReleased(state, oldState, PIND2) && buttonPressed(PIND2))
            {
                state = Etat::ETEINT1;
            }

            else if (buttonPressed(PIND3) && buttonReleased(state, oldState, PIND3))
            {
                state = Etat::INIT;
            }
            break;
        case Etat::ETEINT1:
            PORTA = LIGHT_OFF;
            if (buttonReleased(state, oldState, PIND2) && buttonPressed(PIND2))
            {
                state = Etat::ETEINT2;
            }
            else if (buttonPressed(PIND3) && buttonReleased(state, oldState, PIND3))
            {
                state = Etat::INIT;
            }
            break;
        case Etat::ETEINT2:
            PORTA = LIGHT_OFF;
            if (buttonReleased(state, oldState, PIND2) && buttonPressed(PIND2))
            {
                state = Etat::ETAT_ROUGE;
            }
            else if (buttonPressed(PIND3) && buttonReleased(state, oldState, PIND3))
            {
                state = Etat::INIT;
            }
            break;
        case Etat::ETAT_ROUGE:
            PORTA = RED_LIGHT;
            if (buttonReleased(state, oldState, PIND2) && buttonPressed(PIND2))
            {
                state = Etat::INIT;
            }
            else if (buttonPressed(PIND3) && buttonReleased(state, oldState, PIND3))
            {
                state = Etat::INIT;
            }
            break;
        }
    }

    return 0;
}