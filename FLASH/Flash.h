/*
 * Flash.h
 *
 *  Created on: 17-Dec-2017
 *      Author: amar
 */

#ifndef FLASH_H_
#define FLASH_H_



#define FLASHBASE 0x400FD000u /*Base address for Flash Control Register*/
#define FMA (*(volatile unsigned int*)(FLASHBASE+0x000))/*Flash Memory Address; 4 Bytes aligned for Programming and 16KB aligned for erasure*/
#define FMD (*(volatile unsigned int*)(FLASHBASE+0x004))/*Flash Memory Data -  holds data to be written*/
#define FMC (*(volatile unsigned int*)(FLASHBASE+0x008))/*Flash Memory Control- upper 2 bytes: WRITEKEY; Lower nibble: COMT MERASE ERASE WRITE*/
#define FCRIS (*(volatile unsigned int*)(FLASHBASE+0x00C))/*Flash Controller Raw Interrupt Status*/
#define FCIM (*(volatile unsigned int*)(FLASHBASE+0x010))/*Flash Controller Interrupt Mask*/
#define FCMISC (*(volatile unsigned int*)(FLASHBASE+0x014))/*Flash Controller Masked Interrupt Status and Clear*/
#define FMC2 (*(volatile unsigned int*)(FLASHBASE+0x020))/*Flash Memory Control 2 - upper two bytes WRKEY; bit 0 WRBUF*/
#define FWBVAL (*(volatile unsigned int*)(FLASHBASE+0x030))/*FWBVAL -Flash Write Buffer Valid*/
#define FLPEKEY (*(volatile unsigned int*)(FLASHBASE+0x03C))/*Flash Program/Erase Key (FLPEKEY) */
#define FLASHPP (*(volatile unsigned int*)(FLASHBASE+0xFC0))/*Flash Peripheral Properties (FLASHPP)*/
#define FLASHCONF (*(volatile unsigned int*)(FLASHBASE+0xFC8))/*Flash Configuration Register*/
#define FLASHDMASZ (*(volatile unsigned int*)(FLASHBASE+0xFD0))/*Flash DMA Address Size*/
#define FLASHDMAST (*(volatile unsigned int*)(FLASHBASE+0xFD4))/*Flash DMA Starting Address -- shift the address by 11*/

#define BOOTCFG (*(volatile unsigned int*)(0x400FE000+0x1D0)); /*Boot Configuration Register - would be used for KEY*/


extern int FlashWrite(int Address, int Data);
extern int FlashErase(int Address);
extern int FlashSize();
extern int FlashReadDMA(int Address,int Size, int* Data);



#endif /* FLASH_H_ */
