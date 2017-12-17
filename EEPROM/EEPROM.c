/*
 * EEPROM.c
 *
 *  Created on: 07-Nov-2017
 *      Author: amar
 */

#include "EEPROM.h"


int EEPROM32BitWordSize (){
/*This function returns the number of 32 bits words in the EEPROM*/
    return  EESIZE&0xFFFF;

}

int EEPROM16WordBlockSize(){
/*This function returns the number of 16 word blocks in the EEPROM*/

    return EESIZE&0x07FF0000u;
}

int ReadEEBLOCK (){
/*This function returns the BLOCK field of EEBLOCK register.
**The BLOCK field decides to which block read, write and protection would apply to.
*/
    return EEBLOCK&0xFFFF;
}

void WriteEEBLOCK (int BlockNumber){
/*This function updates the BLOCK field of EEBLOCK register.
**The BLOCK field decides to which block read, write and protection would apply to.
*/
    EEBLOCK = BlockNumber&0xFFFF;
}

int ReadEEOFFSET (){
/*This function returns the OFFSET field of EEOFFSET register.
**The OFFSET field decides to which word in a block read and write would apply to.
*/
    return EEOFFSET&0xF;
}

void WriteEEOFFSET (int OffsetNumber){
/*This function returns the OFFSET field of EEOFFSET register.
**The OFFSET field decides to which word in a block read and write would apply to.
*/
    EEOFFSET = OffsetNumber&0xF;
}

int ReadEEPROM(unsigned int Block,unsigned int Offset, int* Buffer, int Length){
/*This function reads the Length number of words starting from the block specified by Block and offset specified by Offset
**and stores them in Buffer. It auto increments the Block to satisfy the Length.
**If access is not valid it returns 1 else 0.
*/
    if((Offset > 15) || (Length == 0)) // offset can go maximum up to 15.
            return 1;

    int i = 0 ;

    while(i<Length){
        WriteEEBLOCK(Block);
        WriteEEOFFSET(Offset);
       // SomeDelay2(100);
        Buffer[i] = EERDWR;
        if(Offset == 15){
            Offset = 0;
            Block++;
        }else
            Offset++;
        i++;
    }

return 0;
}


int WriteEEPROM(unsigned int Block,unsigned int Offset, int* Buffer, int Length){
/*This function writes the Length numbers of words starting from the block specified by Block and offset(word) specified by Offset
**It returns 0 for success and 1 for failure.
*/
    if((Offset > 15) || (Length == 0))
        return 1;

    if(EEDONE&0x3D){
                return 1;/*failure*/
            }

    int i = 0;
    while(i<Length){
        WriteEEBLOCK(Block);
        WriteEEOFFSET(Offset);

        EERDWR = Buffer[i];
        SomeDelay2(1000);//Delay as Write takes some time.
//TODO: try to implement it in more better way...i mean remove the above delay
        if(EEDONE&0x3D){
            return 1;/*failure*/
        }

        if(Offset == 15)
        {
            Offset = 0;
            Block++;
        }else
            Offset++;

        i++;
    }
return 0;/*success*/
}

int InitializeEEPROM(){
/*This function initializes the EEPROM module so that we could start our reading and writting.
**This function returns 0 for success and integer for failure (integer would depend on STEP number)
*/
/*STEP 1: Providing Clock to EEPROM module*/
    RCGCEEPROM = 0x1;
    SomeDelay2(2000);

/*STEP 2: Polling the WORKING bit of EEDONE Register*/
    if(EEDONE&0x1)
        return 2;
/*STEP 3: Checking for Programming and Erase Errors from previous access*/
    if(EESUPP&0xC)
        return 3;

/*STEP 4: SOftware Resting the EEPROM*/
    SoftwareResetEEPROM();
    SomeDelay2(2000);

/*STEP 5: Checking WORKING bit in EEDONE Register*/
    if(EEDONE&0x1)
        return 5;

/*STEP 6: Checking for Programming and Erase Errors from previous access*/
    if(EESUPP&0xC)
        return 6;

return 0;

}

void SoftwareResetEEPROM(){
    SREEPROM = 0x1u;
    SomeDelay2(1000);
    SREEPROM = 0;
    while(!(PREEPROM&0x1u));
}

int ReadFlashMEMTIM0(){
    return MEMTIM0&0x03EF;
}

int ReadEEPROMMEMTIM0(){
    return MEMTIM0&0x03EF0000;
}

int MassEraseEEPROM(){
    //reseting the EEPROM
    SoftwareResetEEPROM();
    SomeDelay2(100);

    while(EEDONE&0x1);//checking WORKING bit

    EEDBGME = 0xE37B0001;

    while(EEDBGME&0x1);//still getting erased

    SoftwareResetEEPROM();

    SomeDelay2(1000);

return 0;
}

int SomeDelay2(int Delay){

    if(Delay <= 0){
        return 0;
    }
    do{
        Delay--;
    }while(Delay);

    return 1;
}


int CheckingClockSettings(){
    //here we are checking whether lower and upper bytes in MEMTIM0 register are equal
    if((MEMTIM0&0x3ef)==((MEMTIM0 >> 16)&0x3ef))
        return 0;
    else return 1;

}
