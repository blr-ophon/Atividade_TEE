#include "uart.h"
#include <util/setbaud.h>


void UART_Init(void){
    /* Configure UBBR (must define BAUD) */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    /* Enable TX and RX */
    UCSR0B |= (1 << RXEN0);
    UCSR0B |= (1 << TXEN0);

    /* 8-bit Character size */
    UCSR0C |= (1 << UCSZ00);
    UCSR0C |= (1 << UCSZ01);
}


/* Send Data through UART. Polling Mode */
void UART_SendPolling(uint8_t data){
    /*
     * Bit UDREn of UCSR0A indicates transmit buffer is ready to receive
     * new data.
     */
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}


uint8_t UART_ReceivePolling(void){
    /* Bit UDREn of UCSR0A flags end of transmission (data register empty) */
    loop_until_bit_is_set(UCSR0A, RXC0);
    /* 
     * AVR uses the same address/register for receive and transmit, but treats
     * them separately
     */
    return UDR0;
}


void UART_print(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        UART_SendPolling(str[i]);
    }
}
