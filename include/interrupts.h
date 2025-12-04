#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define EINT0 (1 << 0)
#define EINT1 (1 << 1)

typedef enum{
    LOW_LEVEL    = 0,
    ANY_CHANGE   = 1,
    FALLING_EDGE = 2,
    RISING_EDGE  = 3,
} E_INT_SENSE;


void initEInt(uint8_t eint, E_INT_SENSE sense);

void initPCInt(uint8_t pcint);


#endif
