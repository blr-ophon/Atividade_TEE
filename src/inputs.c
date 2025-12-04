#include "inputs.h"

volatile GameInputs INPUTS = {0, {0}};

ISR(PCINT2_vect){
    INPUTS.buttons[INPUT_Z_POS] = bit_is_clear(PIND, PD2)? 1 : 0;
    INPUTS.buttons[INPUT_Z_NEG] = bit_is_clear(PIND, PD3)? 1 : 0;
    INPUTS.buttons[INPUT_X_NEG] = bit_is_clear(PIND, PD4)? 1 : 0;
    INPUTS.buttons[INPUT_X_POS] = bit_is_clear(PIND, PD5)? 1 : 0;
    INPUTS.buttons[INPUT_Y_NEG] = bit_is_clear(PIND, PD6)? 1 : 0;
    INPUTS.buttons[INPUT_Y_POS] = bit_is_clear(PIND, PD7)? 1 : 0;
}

ISR(PCINT1_vect){
    if(bit_is_clear(PINC, PC1)){
        INPUTS.game_select |= (1 << 0);
    }else{
        INPUTS.game_select &= ~(1 << 0);
    }

    if(bit_is_clear(PINC, PC0)){
        INPUTS.game_select |= (1 << 1);
    }else{
        INPUTS.game_select &= ~(1 << 1);
    }
}
