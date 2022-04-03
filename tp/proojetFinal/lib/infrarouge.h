#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

class Infrarouge
{
public:
uint8_t getVoltage(uint8_t pos);
uint8_t getDistanceCm();




}