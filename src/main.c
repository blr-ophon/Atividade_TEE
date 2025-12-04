/**
 * @file main.c
 * @brief Main game/menu loop.
 */

#include "main.h"

extern GameInputs INPUTS;


int main(void){
    //GPIO
    PORTC |= (1 << PD0);
    PORTC |= (1 << PD1);
    PORTD |= (1 << PD2);
    PORTD |= (1 << PD3);
    PORTD |= (1 << PD4);
    PORTD |= (1 << PD5);
    PORTD |= (1 << PD6);
    PORTD |= (1 << PD7);

    // Interrupts
    initPCInt(8);
    initPCInt(9);
    for(int i = 18; i <= 23; i++){
        initPCInt(i);
    }

    // UART
    UART_Init();
    
    Framebuffer fb;
    fb.clear();

    for(;;){
        fb.clear();
        fb.show();

        switch(INPUTS.game_select){
            case MENU:
                Menu();
                break;
            case CUBE_GAME:
                CubeGame(&fb);
                break;
            case TETRA_GAME:
                TetraGame(&fb);
                break;
            default:
                break;
        }
    }
    return 0;
}


/**
 * @brief Prints Menu through UART.
 */
void Menu(void){
    UART_print("\r\n\r\n\r\nO futuro chegou...\r\n");
    UART_print("\r\n==============================\r\n");
    UART_print("     PARAIBASTATION 3D     \r\n");
    UART_print("==============================\r\n");
    UART_print("\r\nSelecione uma opção:\r\n\r\n");
    UART_print("1. CUBO\r\n");
    UART_print("2. TETRAEDRO\r\n\r\n");

    while(INPUTS.game_select == MENU){
        _delay_ms(1);
    }
}
