#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include <can.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <photoresistance.h>
#include <MoteurRoueDroite.h>
#include <MoteurRoueGauche.h>

class PhotoResistance {
public:
PhotoResistance (uint8_t pinPhotoDroite ,uint8_t pinPhotoGauche );

getDroit();



private:




} 