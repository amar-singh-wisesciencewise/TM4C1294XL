/*
 * UART.h
 *
 *  Created on: 11-Feb-2018
 *      Author: AMAR SINGH
 */

#ifndef UART_H_
#define UART_H_


#define RCGCUART (*(volatile unsigned int*)0x400FE618)
#define RCGCGPIO (*(volatile unsigned int*)0x400FE608)
#define PORT_A_BASE 0x40058000u
#define PORT_A_AFSEL (*(volatile unsigned int*)(PORT_A_BASE+0x420))
#define PORT_A_PCTL (*(volatile unsigned int*)(PORT_A_BASE+0x52C))
#define UART_0_BASE 0x4000C000u
#define UARTDR (*(volatile unsigned int*)(UART_0_BASE + 0)) //DATA REGISTER for UART0
//UARTDR is used for both read and write
#define UARTRSR (*(volatile const unsigned int*)(UART_0_BASE + 0x004)) //UART STAUS: lower nibble read gives the error - read only
#define UARTECR (*(volatile unsigned int*)(UART_0_BASE + 0x004)) //UART ERROR CLEAR: write to LSB, with data would clear the register and lower nibble read gives the error
#define UARTFR (*(volatile const unsigned int*)(UART_0_BASE + 0x018))
#define UARTIBRD (*(volatile unsigned int*)(UART_0_BASE + 0x024)) // integer baud rate divisor register
#define UARTFBRD (*(volatile unsigned int*)(UART_0_BASE + 0x028)) //UART fractional Baud Rate divisor
#define UARTLCRH (*(volatile unsigned int*)(UART_0_BASE + 0x02C)) // UART Line Control
#define UARTCTL (*(volatile unsigned int*)(UART_0_BASE + 0x030)) //UART CONTROL
#define UARTCC  (*(volatile unsigned int*)(UART_0_BASE + 0xFC8))



#define CLOCK 16000000


extern void InitializeUART0();
extern int ReadUARTDR(int* const word);
extern void WriteUARTDR(const int word);

#endif /* UART_H_ */
