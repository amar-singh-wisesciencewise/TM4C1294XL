/**
 *
 * This code test the feature of Vector-Table-Offset
 * With this feature we can move our Vector-Table elsewhere
 * Here we will create an array and move the vector-table there;
 * to see the working we shell simulate SVC interrupt from the array
 *
 * main.c
 */
#define NO_OF_ENTRIES_IN_TABLE (128+130)
/**there are 130 entries in our Vector Table....but we need to store it on 1024 byte boundary
* that is why 128 has been added here.....128 * sizeof(int) = 1024 byte
*/
unsigned int VectorTable[NO_OF_ENTRIES_IN_TABLE]; //our new Vector Table

#define VECTOR_TABLE_OFFSET (*(volatile unsigned int*)0xE000ED08) // Address of Vector Table Offset

volatile unsigned int d=0; // variable that gets updated from inside of interrupt


void SVC_Handler();  // interrupt handler

int main(void)
{
    unsigned int i=0;

    volatile unsigned int flag=0; //initially, we will search for 1024 byte boundary inside our array ...go to flag's first usecase
    unsigned int index=0; // store the index inside array which meets 1024 byte boundary
    unsigned int counter=0; // to copy the entries from initial vector table
    volatile unsigned int a=1;

    for (i=0;i<NO_OF_ENTRIES_IN_TABLE;i++)
    {
        if(!flag){ //in here, we will search for index in our array whose address is on 1024 byte boundary
            if ( 0 == ((unsigned int)(&VectorTable[i]) & 0x3FFU) ) //if we see one store its index and mark the flag
            {
                flag=1;
                index=i;

            }
        }else // in here, we will use the same loop and make a copy of Vector Table in our array
        {
            VectorTable[index+counter]= (*((unsigned int*)0x00000000U + counter));
            counter++;
            if (counter == NO_OF_ENTRIES_IN_TABLE) //exit once all the interrupt entries at 0x00000000U are copied
                break;
        }
    }//for loop

    VECTOR_TABLE_OFFSET = (unsigned int)&VectorTable[index]; // update at VECTOR TABLE OFFSET Address
    __asm(" ISB"); //Instruction needed to synchronize the addresses

    if (a)
    {
        a = VECTOR_TABLE_OFFSET;
    }

    VectorTable[index+11]=(unsigned int)SVC_Handler;  // change the new vector table entry for SVC interrupt call

    __asm(" SVC   #1"); //will cause the SVC Interrupt and calls the SVC_Handler function that we updated in new VT.

    while(1){ // if we are here then things did not work; our way.
        __asm(" NOP");
    }

	return 0;
}

void SVC_Handler(){

    d = 123;
    while(d){ // and if we here then Hurray! it worked.
        __asm(" NOP");
    }
}
