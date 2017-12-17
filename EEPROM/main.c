

#include <stdint.h>
#include "EEPROM.h"

int SomeDelay(int Delay);

int main(void)
{
    volatile int temp;
    int temp2;
    int i=32;

    int Buffer1[32]; //for writing
    int Buffer2[32]; //for reading

    for(i = 0; i<32;i++){
        Buffer1[i] = i;
        Buffer2[i] = 0;
    }

   // RCGCEEPROM = 0x1;
   //SomeDelay(6);

   //temp= EEPROM32BitWordSize();
   // temp = EEPROM16WordBlockSize();

    temp = InitializeEEPROM();
    while(temp)
        temp = InitializeEEPROM();


    //temp = CheckingClockSettings();
  //  temp = MassEraseEEPROM();

  // temp = WriteEEPROM(1,0,Buffer1,32);

    temp = ReadEEPROM(1,0,Buffer2,32);

    temp = 0;
    for(i=0;i<32;temp+=Buffer2[i++]);//adding all the values

    temp = ReadEEPROM(3,0,Buffer2,32);

    temp = 0;
    for(i=0;i<32;temp+=Buffer2[i++]);//adding all the values

    if(temp!= 1488)
        return 1;

return 0;
}

int SomeDelay(int Delay){

    if(Delay <= 0){
        return 0;
    }
    do{
        Delay--;
    }while(Delay);

return 1;
}
