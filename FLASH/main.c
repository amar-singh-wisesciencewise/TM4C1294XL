

/**
 * main.c
 */

#include "Flash.h"

#define ADDRESS 0x80000

int main(void)
{
    int temp = 0;
//writing

    temp = BOOTCFG;
    if(temp & 0x10){ //0xA442 can be used as key
        temp = FlashWrite(ADDRESS,0xAAAA);
    }

// reading
    temp = *((int*)(0x80000));
    if(temp != 0xAAAA){
        return 1;
    }
//Erasing
    temp = FlashErase(0x80000);

//Reading Again

    temp = *((int*)(0x80000));
      if(temp != -1){
          return 1;
      }



	return 0;
}
