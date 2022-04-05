#define F_CPU 8000000U
#include <avr/io.h>
#include <util/delay.h>
#include <photoresistance.h>
#include <MoteurRoueDroite.h>
#include <MoteurRoueGauche.h>
#include <photoresistance.h>
#include <can.h>


Photoresistance :: getDroit(uint8_t pos)
{
    return((can.lecture(pos)*100)/1024)
}
Photoresistance :: getGauche(uint8_t pos)
{
    return((can.lecture(pos)*100)/1024)
}


