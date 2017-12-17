/*
 * EEPROM.h
 *
 *  Created on: 08-Nov-2017
 *      Author: amar
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#define RCGCEEPROM (*(volatile unsigned int*)(0x400FE658))/*EEPROM Run Mode Clock Gating Control*/
#define SREEPROM (*(volatile unsigned int*)(0x400FE558)) /*EEPROM SOFTWARE RESET*/
#define PREEPROM (*(volatile unsigned int*)(0x400FEA58)) /*EEPROM Peripheral Ready*/

#define MEMTIM0 (*(volatile unsigned int*)(0x400FE0C0)) /*Memory Timing Parameter Register 0 for Main Flash and EEPROM*/

#define EEPROMBASE 0x400AF000u

#define EESIZE (*(volatile unsigned int*)(EEPROMBASE+0x000))
#define EEBLOCK (*(volatile unsigned int*)(EEPROMBASE+0x004))
#define EEOFFSET (*(volatile unsigned int*)(EEPROMBASE+0x008))
#define EERDWR (*(volatile unsigned int*)(EEPROMBASE+0x010)) /*EEPROM READ WRITE*/
#define EEDONE (*(volatile unsigned int*)(EEPROMBASE+0x018))/*EEEPROM DONE STATUS*/
#define EESUPP (*(volatile unsigned int*)(EEPROMBASE+0x01c))/*EEPROM STATUS AND SUPPORT*/
#define EEDBGME (*(volatile unsigned int*)(EEPROMBASE+0x080))/*EEPROM DEBUG MASS ERASE*/

extern int EEPROM32BitWordSize();
extern int EEPROM16WordBlockSize();
extern int ReadEEBLOCK();
extern void WriteEEBLOCK(int BlockNumber);
extern int ReadEEOFFSET();
extern void WriteEEOFFSET (int OffsetNumber);
extern int ReadEEPROM(unsigned int Block,unsigned int Offset,int* Buffer, int Length);
extern int WriteEEPROM(unsigned int Block,unsigned int Offset, int* Buffer, int Length);
extern int InitializeEEPROM();
extern void SoftwareResetEEPROM();
extern int ReadFlashMEMTIM0();
extern int ReadEEPROMMEMTIM0();
extern int MassEraseEEPROM();
extern int CheckingClockSettings();


int SomeDelay2(int);





#endif /* EEPROM_H_ */
