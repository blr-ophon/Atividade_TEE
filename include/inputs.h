#ifndef INPUTS_H
#define INPUTS_H

#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum{
    INPUT_X_POS = 0,
    INPUT_X_NEG = 1,
    INPUT_Y_POS = 2,
    INPUT_Y_NEG = 3,
    INPUT_Z_POS = 4,
    INPUT_Z_NEG = 5
} E_INPUTS;


typedef struct{
    uint8_t game_select;
    uint8_t buttons[6];
} GameInputs;

#endif
