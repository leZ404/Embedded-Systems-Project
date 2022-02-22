#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>

void roueTourne()

{
    PORTA = 0x01;
}

void roueArret()
{
    PORTA = 0x00;
}

int main()
{
    float periode_1 = 2.5       // période pour 400 Hz
    float periode_2 = 16.67 // période pour 60 Hz
    const float rapport = 1.25

        for (int i; i < 5; i++)
        {
            _delay_ms(2000);
            a = a * rapport;
        }

    for (int i; i < 5; i++)
    {

        _ delay_ms(2000);
        a = a * rapport;
    }
