#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>


void ledEteinte()

{
    PORTA = 0x00;
}

void ledRouge()
{
    PORTA = 0x01;
}

int main()
{

    ledRouge();
    DDRA = 0xFF;
    uint16_t a = 1500;
    uint16_t c = 0;
    uint16_t b = c + a;
    const uint8_t delaidzp = 1;

    for (int i = 0; i < 3; ++i) 
    {
        for (int i = 0; i<1000; i++)
        {
               if (a <= 0)
        {
            ledEteinte();
        }

            for (int i = 0; i < a; i++)
            {

                _delay_us(delaidzp);

            }
            a = a - 1;
            
            ledEteinte();

            for (int i = 0; i < c; i++)
            {

                _delay_us(delaidzp);

            }
            c = c + 1;
            ledRouge();
         





        }
    }

    return 0;
}