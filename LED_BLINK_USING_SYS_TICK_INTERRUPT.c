

/*
 * THIS CODE WAS WRITTEN TO BLINK BOTH LEDs ONE AT A TIME
 * IT USES ARRAY ARITHMETIC AND BIT MANIPULATION FOR GPIO PORT
 * ALL GPIO PORT ARE CONNECTED TO ADDRESS LINE AS WELL; THIS GIVE DEDICATED ADDRESS FOR
 * EVERY PORT PIN
 *
 *IN THIS CODE I AM GONNA TRY TIMER INTERRUPTS
 *WE WILL BE USING SYS-TICK TIMMER
 *REGISTERED IT(SYS TICK) IN STARTUP CODE.
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
#define GPIO_N_DATA_BASE  ((volatile unsigned int*)0x40064000)/*THIS IS BASE ADDRESS OF GPIO DATA REGISTER

THIS CAN BE USED AS ARRAY AS ALL GPIO PORTS ARE ALSO CONNECTED TO ADDRESS LINES.
 */
#define SYS_TICK_BASE 0xE000E000 /*base address of systick registers*/
#define STCTRL (*(volatile unsigned int*)(SYS_TICK_BASE + 0x010))
#define STRELOAD (*(volatile unsigned int*)(SYS_TICK_BASE + 0x014))
#define STCURRENT (*(volatile unsigned int*)(SYS_TICK_BASE + 0x018))


//prototypes
void some_delay(void);

int main(void)
{

    (CLOCK_GATE_ENABLE) |= 0x1000 ;
    some_delay(); /*it takes 2 cycle for initialization*/

    GPIO_N_DIR |= (LED_ONE |LED_TWO);
    GPIO_N_DEN |= (LED_ONE| LED_TWO);

    STRELOAD = 0x7FFFFFu;/*max value*/
    STCURRENT = 0u;
    STCTRL |= 0x7; /*CLK_SRC =1(system clock); INTEN = 1(int enable ); ENABLE = 1(start counter)*/

    /*register the SysTickHandler in startup code */

    while (1){

       //GPIO_N_DATA_BASE[LED_ONE] = LED_ONE; /*This instruction is atomic so no race condition*/
      //some_delay();
      // GPIO_N_DATA_BASE[LED_ONE] = ~LED_ONE;
      // some_delay();
       GPIO_N_DATA_BASE[LED_TWO] = LED_TWO;
       some_delay();
       GPIO_N_DATA_BASE[LED_TWO] = ~LED_TWO;
       some_delay();

    }


    return 0;
}


void some_delay (){

    volatile int i;
    for(i = 0; i<8000000;i++){
    }

}


void SysTickHandler(void){ /*register this function in STARTUP CODE*/

    GPIO_N_DATA_BASE[LED_ONE] ^= LED_ONE;

}
