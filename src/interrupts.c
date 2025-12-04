/**
 * @file interrupts.c
 * @brief Functions to initialize and configure interrupts.
 */


#include "interrupts.h"


/**
 * @brief Initialize External Interrupts.
 * @note Can initialize both at the same time with | operator.
 * @param eint External Interrupt number
 * @param sense Trigger Mode for Interrupts.
 */
void initEInt(uint8_t eint, E_INT_SENSE sense){
    uint8_t eint_0 = eint & EINT0? 1 : 0;
    uint8_t eint_1 = eint & EINT1? 1 : 0;

    EIMSK |= ((eint_0) << INT0);
    EIMSK |= ((eint_1) << INT1);

    if(eint_0){
        EICRA |= (sense & (1 << 0)) << ISC00;
        EICRA |= (sense & (1 << 1)) << ISC01;
    }

    if(eint_1){
        EICRA |= (sense & (1 << 0)) << ISC11;
        EICRA |= (sense & (1 << 1)) << ISC10;
    }

    sei();
}


/**
 * @brief Initialize Pin Change Interrupts.
 * @param pcint Pin Change Interrupt number
 */
void initPCInt(uint8_t pcint){
    if(pcint <= 7){
        PCICR |= (1 << PCIE0);
        PCMSK0 |= (1 << pcint);

    }else if(pcint <= 14){
        PCICR |= (1 << PCIE1);
        PCMSK1 |= (1 << pcint - 8);

    }else if(pcint <= 23 && pcint >= 16){
        PCICR |= (1 << PCIE2);
        PCMSK2 |= (1 << pcint - 16);
    }

    sei();
}
