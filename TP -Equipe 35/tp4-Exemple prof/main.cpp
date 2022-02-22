/**
 * Description du programme:
 * 
 * 1. L'interruption INT0 est utilisé pour alterner la couleur de la DEL bicolore. (Intéragir avec le bouton poussoir)
 * 2. Le timer 1 est utilisé pour pour alterner la couleur de la DEL bicolor. (Pas besoin d'intéraction)
 * 3. Le timer 0 est utilisé pour controller les moteurs à l'aide d'un Pont en H. (Pas besoin d'intéraction)
 * 
 * Documentation: 
 * http://ww1.microchip.com/downloads/en/devicedoc/atmel-8272-8-bit-avr-microcontroller-atmega164a_pa-324a_pa-644a_pa-1284_p_datasheet.pdf
 * 
 *  Page de la documentation Atmel consulté:
 *  - Interruption avec INT0: p.67 à 68
 *  - Timer 1: p.128 à 134
 *  - Timer 0: p.101 à 106
 *  
 * */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile bool toggleButton = false;
volatile bool toggleTimer = false;

ISR(INT0_vect)
{
    _delay_ms(10);
    // In SimulIde the next line must be commented to work, but with the robot must be uncommented
    //if (PIND & (1 << PD2)) // Comment this line in SimulIde
    {
        PORTA &= ~((1 << PA0) | (1 << PA1));
        PORTA |= toggleButton ? (1 << PA0) : (1 << PA1);
        toggleButton = !toggleButton;
    }

    EIFR |= (1 << INTF0);
}

ISR(TIMER1_CAPT_vect)
{
    PORTA &= ~((1 << PA2) | (1 << PA3));
    PORTA |= toggleTimer ? (1 << PA2) : (1 << PA3);
    toggleTimer = !toggleTimer;

    TIFR1 |= (1 << OCF1A);
}

void initialisationInt0()
{

    cli();
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC11);

    sei();
}

void initialisationTimer()
{
    cli();
    DDRA |= (1 << PA2) | (1 << PA3);

    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TIMSK1 = (1 << OCIE1A);
    OCR1A = 14000;
    sei();
}

void initialisationTimerPwm()
{
    cli();
    DDRB |= (1 << PB2) | (1 << PB3);
    TCNT0 = 0;

    // In SimulIde use the Fast PWM, but with the robot you must use the PWM Phase Correct 8-bit
    TCCR0A =
        (1 << WGM00) |
        (1 << WGM01) | // Comment this line when you are in the robot to obtain the PWM Phase Correct 8-bit
        (1 << COM0A1);
    TCCR0B = (1 << CS01);
    sei();
}

void setDutyCycle(uint8_t dutyCycle)
{
    OCR0A = dutyCycle;
}

int main()
{
    initialisationInt0();
    initialisationTimer();
    initialisationTimerPwm();
    uint8_t dutyCycle = 0;
    while (true)
    {
        setDutyCycle(++dutyCycle);
        _delay_ms(50);

        if (dutyCycle % (UINT8_MAX / 2) == 0) // Change direction at half speed
        {
            // First iteration
            // 0b1111 0000      (PORTB)
            // 0b0000 1000 ^    (1 << PB2)
            // --------------
            // 0b1111 1000      (PORTB Final value for the first iteration)

            // Second  iteration
            // 0b1111 1000      (PORTB of the first iteration)
            // 0b0000 1000 ^    (1 << PB2)
            // --------------
            // 0b1111 0000      (PORTB Final value)
            PORTB ^= (1 << PB2);
        }
    }

    return 0;
}