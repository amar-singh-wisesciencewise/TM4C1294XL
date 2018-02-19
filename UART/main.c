
/**
 * main.c ; AMAR SINGH
 *
 * This code tests the UART0 working
 * Here we are initializing the UART0; and we are also enabling the loop-back feature
 * Then we transmit a character and wait for it to be received back.
 *
 *
 * UART0 Characteristics : Baud Rate 115200; NO PARITY;1 STOP BIT; NO BREAK; NO FIFO; NO INTERRUPT;
 *
 */


#include "UART.h"

int main(void)
{
    int temp1 = 0; // success status
    int* temp2 = &temp1; // using pointer aliasing to avoid optimization
    int temp3 = 0 ; // to receive the data


    InitializeUART0();
    if(!(UARTFR & (0x1u << 3)))
        WriteUARTDR('A');  //sending a character 'A'; since loop back is enabled same character would get received
    while((UARTFR & (0x1u << 3)));//wait till BUSY bit clears

    temp1 = ReadUARTDR(&temp3);// read the data register

    if(!temp1){// no error in the received data
        if(temp3 == 'A')// check whether received data is same as the sent one
            *temp2 = 1;//success
    }

	return 0;
}


