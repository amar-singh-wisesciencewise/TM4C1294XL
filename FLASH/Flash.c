/*
 * Flash.c
 *
 *  Created on: 17-Dec-2017
 *      Author: amar
 */

#include "Flash.h"

int FlashWrite(int Address, int Data){
// Writes a 32 bit word(Data) at the address specified by Address.

    FMA = Address&0x0FFFFC; // programming FMA - 32 bit aligned address
    FMD = Data; //Filling the data
    FMC = 0x01u + 0xA4420000 ;//writing onto Flash
    while(FMC&0x1u); //waiting for completion

return 0;
}

int FlashErase(int Address){
//function Erase a complete Block of 16KB.

    FMA = Address&0x0F2000; //16KB aligned Address
    FMC= 0x02u + 0xA4420000; //Erasing
    while(FMC&0x02u);//waiting for Erase to complete.

return 0;
}

int FlashSize(){
    return FLASHPP&0x0FFFF;
}


int FlashReadDMA(int Address,int Size, int* Data){
//Address is location from where to read
//Size is how many bytes to read
//Data is the location where to store the read data
return 0;
}






