#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>


double variancePwm(float x, float y){
    return x*y/y;
}

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
    float periode_1 = 2.5;       // période pour 400 Hz
    float periode_2 = 16.67; // période pour 60 Hz
    float a0 = 0;
    float a1 = 0.25;
     float a2 = 0.5; 
    float a3 = 0.75;
    float a4 =1;


    variancePwm(a0,periode_1);
    roueTourne();
    _delay_ms(2000);
      variancePwm(a1,periode_1);
        _delay_ms(2000);
        variancePwm(a2,periode_1);
        _delay_ms(2000);
        variancePwm(a3,periode_1);
        _delay_ms(2000);
        variancePwm(a4,periode_1);
        _delay_ms(2000);
        variancePwm(a0,periode_2);
        _delay_ms(2000);
        variancePwm(a1,periode_2);
        _delay_ms(2000);
        variancePwm(a2,periode_2);
        _delay_ms(2000);
        variancePwm(a3,periode_2);
        _delay_ms(2000);
        variancePwm(a4,periode_2);
        _delay_ms(2000);
        roueArret();

}
