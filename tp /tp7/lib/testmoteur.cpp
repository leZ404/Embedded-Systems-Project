#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void avancer()

{
    PORTB =  (1 << PB4) | (1 << PB5);
};


void stop()
{
    PORTB = 0x00;
};



void ajustementPwmNavigation ( uint8_t pourcentageDroite , uint8_t pourcentageGauche) 
{

OCR0A = 40;//pourcentageDroite * 255 / 100;
OCR0B = 20;//pourcentageGauche * 255 / 100;

TCNT0 = 0;
 TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
 TCCR0B = (1 << CS01);

};

int main()
{
    DDRB = 0xff;
    DDRD= 0x00;


    while (true)
    {
        avancer();
    ajustementPwmNavigation(50,100);
    _delay_ms(1000);
        //stop();
    ajustementPwmNavigation(0,0);
     _delay_ms(1000);


    }
   }   