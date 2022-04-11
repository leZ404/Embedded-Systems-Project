#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"
#include "infrarouge.h"

Infrarouge::getVoltage(uint8_t pos)
{
    return ((can.lecture(pos) * 5) / 1024);
}

Infrarouge ::getDistanceCm(uint8_t pos)
{
    return ((5 * can.lecture(pos)) / 1024);
}
