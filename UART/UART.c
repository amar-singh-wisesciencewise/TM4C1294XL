/*
 * UART.c
 *
 *  Created on: 11-Feb-2018
 *      Author: AMAR SINGH
 */
#include "UART.h"

void InitializeUART0(){

    RCGCUART = 0x1; //providing clock to UART0 module
    RCGCGPIO = 0x1; //providing clock to PORT0 as Rx and Tx of UART0 are located there
    PORT_A_AFSEL = 0x3; // pin 0 and 1 as Alternate Function pins
// does not need to program UNLOCK and COMMIT registers
    PORT_A_PCTL = (0x1 | (0x1<<4));// alternate function 1 for pin 0 & 1

//baud rate 115200; calculation for 16Mhz = 8.6805555
//so UARTIBRD = 8 and UARTFBRD = 0x2C(44)
    UARTCTL = UARTCTL&(~0x1u); // disabling the UART0
    UARTIBRD = 0x8u; // loading integer part of BAud Rate
    UARTFBRD = 0x2c;// loading Fraction part of BAud Rate
    UARTLCRH = 0x00000060; // NO PARITY; NO FIFO; NO BREAK; SINGLE STOP BIT
    UARTCC = 0x0;  // system clock
    UARTCTL = UARTCTL | (0x1u << 7)|(0x1u << 0); // loop back (Tx is loop backed to Rx for Debug) ; UART enable
//    UARTCTL = UARTCTL |(0x1u << 0); //UART enable
}



int ReadUARTDR(int* const word){
//it fills the word pointer with received data and returns the error
   *word = (int)UARTDR&0x0FF;

   int temp  = UARTRSR&0xF; //reading status
   UARTECR =  0x4; //clearing the errors; any data would do
   return (temp);  // return 0 if no error else return the error number
//error no 1 = FRAME ERROR; 2 = PARITY ERROR; 4 = BREAK ERROR; 8 = OVERRUN ERROR

}


void WriteUARTDR(const int word){
// it fills the UARTDR register with the passed data
    UARTDR = word&0xFF;

}


