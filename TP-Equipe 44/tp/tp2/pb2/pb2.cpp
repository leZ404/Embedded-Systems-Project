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
 * Table d'etat:
 * +---------------+----+----+--------------+------------+
 * | Etat présent  | D2 | D3 | Etat suivant | Sortie DEL |
 * +---------------+----+----+--------------+------------+
 * | ETAT_ROUGE    | 0  | 0  | ETAT_ROUGE   | ROUGE      |
 * +---------------+----+----+--------------+------------+
 * | ETAT_ROUGE    | 1  | x  | ETAT_VERT    | ROUGE      |
 * +---------------+----+----+--------------+------------+
 * | ETAT_ROUGE    | x  | 1  | ETAT_VERT    | ROUGE      |
 * +---------------+----+----+--------------+------------+
 * | ETAT_VERT     | 1  | 0  | ETAT_ROUGE   | VERT       |
 * +---------------+----+----+--------------+------------+
 * | ETAT_VERT     | 0  | 1  | ETAT_ETEINT  | VERT       |
 * +---------------+----+----+--------------+------------+
 * | ETAT_ETEINT   | 1  | 0  | ETAT_VERT    | ÉTEINT     |
 * +---------------+----+----+--------------+------------+
 * | ETAT_ETEINT   | 0  | 1  | ETAT_ROUGE   | ÉTEINT     |
 * +---------------+----+----+--------------+------------+
 * */
enum class Etat
{
    ETAT_ROUGE,
    ETAT_VERT,
    ETAT_ETEINT
};

bool buttonPressed(const int pin)
{
    const uint8_t DEBOUNCE_TIME = 10;

    const bool PIN_PRESSED = PIND & (1 << pin);

    if (PIN_PRESSED)
    {
        _delay_ms(DEBOUNCE_TIME);

        if (PIND & (1 << pin))
        {
            return true;
        }
    }
    return false;
}

void buttonReleased(const int pin)
{
    while buttonPressed()
    {}
}

const int LIGHT_OFF = 0x00;
const int RED_LIGHT = (1 << PA1);
const int GREEN_LIGHT = (1 << PA0);
int main()
{
    DDRA = ALL_IN;
    DDRD = ALL_OUT;

    Etat state = Etat::ETAT_ROUGE;

    bool flag = true;
    int pin = -1;

    while (true)
    {
      
            switch (state)
            {
            case Etat::ETAT_ROUGE:

                PORTA = RED_LIGHT;

                if (buttonPressed(PIND2) || buttonPressed(PIND3))
                {
                    state = Etat::ETAT_VERT;
                }

                if (buttonPressed(PIND2))
                {
                    pin = PIND2;
                }
                else if (buttonPressed(PIND3))
                {
                    pin = PIND3;
                }
            }
            break;
            case Etat::ETAT_VERT:
                PORTA = GREEN_LIGHT;
                if (buttonPressed(PIND2) && flag)
                {   
                    state = Etat::ETAT_ROUGE;
               
                    pin = PIND2;
                }
                else if (buttonPressed(PIND3) && flag)
                {
                    state = Etat::ETAT_ETEINT;
               
                    pin = PIND3;
                }

                break;
            case Etat::ETAT_ETEINT:;
            PORTA = LIGHT_OFF;
            if (buttonPressed(PIND2) && flag)
            {
                state = Etat::ETAT_VERT;
                
                pin = PIND2;
            }
            else if (buttonPressed(PIND3))
            {
                state = Etat::ETAT_ROUGE;
                
                pin = PIND3;
            }
            break;
       
    }
}
return 0;
}
