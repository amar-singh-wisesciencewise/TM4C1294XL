

/*
 * THIS CODE WAS WRITTEN TO BLINK BOTH LEDs ONE AT A TIME
 * IT USES ARRAY ARITHMETIC AND BIT MANIPULATION FOR GPIO PORT
 * ALL GPIO PORT ARE CONNECTED TO ADDRESS LINE AS WELL; THIS GIVE DEDICATED ADDRESS FOR
 * EVERY PORT
 *
 * IN THIS WE ARE GONNA USE SYS-TICK WITHOUT INTERRUPT
 *
 *
 * DATE: 19 AUGUST 2017
 * AMAR SINGH
 *
 */


#define LED_ONE 0x1u
#define LED_TWO 0x2u
#define CLOCK_GATE_ENABLE  (*((volatile unsigned int*)0x400fe608))/*THIS ENABLE THE GPIO ADDRESSS SECTION FOR PORT N*/
#define GPIO_N_DIR  (*((volatile unsigned int*) 0x40064400))/*THIS IS USED TO SET THE DIRECTION OF GPIO PORTS*/
#define GPIO_N_DEN  (*((volatile unsigned int*) 0x4006451c))/*THIS IS TO MAKE OUTPUT OF GPIO PORT DIGITAL*/
#define GPIO_N_DATA_BASE  ((volatile unsigned int*)0x40064000)/*THIS IS BASE ADDRESS OF GPIO DATA REGISTER*/

#define SYS_TICK_BASE 0xE000E000 /*base address of systick registers*/
#define STCTRL (*(volatile unsigned int*)(SYS_TICK_BASE + 0x010))
#define STRELOAD (*(volatile unsigned int*)(SYS_TICK_BASE + 0x014))
#define STCURRENT (*(volatile unsigned int*)(SYS_TICK_BASE + 0x018))


void some_delay();

int main(void)
{

    (CLOCK_GATE_ENABLE) |= 0x1000 ;
    some_delay(); /*HARDWARE takes 2 cycle for initialization*/

    GPIO_N_DIR |= (LED_ONE |LED_TWO);
    GPIO_N_DEN |= (LED_ONE| LED_TWO);

    STRELOAD = 0x4FFFFFu;/*max value*/
    STCURRENT = 0u;
    STCTRL |= 0x5; /*CLK_SRC =1(system clock); INTEN = 0(int disable ); ENABLE = 1(start counter)*/


    while (1){

       if(STCTRL & (0x1u << 16)){/*POLLING*/

           GPIO_N_DATA_BASE[LED_TWO] ^= LED_TWO;

           GPIO_N_DATA_BASE[LED_ONE] ^= LED_ONE;

       }
    }


    return 0;
}


void some_delay(){

    int i = 10;
    do{
        i--;
    }while(i!=0);
}

