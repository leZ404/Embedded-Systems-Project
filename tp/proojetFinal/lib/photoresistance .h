#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include <can.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <MoteurRoueDroite.h>
#include <MoteurRoueGauche.h>

class PhotoResistance {
public:

uint8_t getDroit(uint8_t pos);
uint8_t getGauche(uint8_t pos);

private:

} 