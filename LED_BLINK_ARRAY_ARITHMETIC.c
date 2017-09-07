

/*
 * THIS CODE WAS WRITTEN TO BLINK BOTH LEDs ONE AT A TIME
 * IT USES ARRAY ARITHMETIC AND BIT MANIPULATION FOR GPIO PORT
 * ALL GPIO PORT ARE CONNECTED TO ADDRESS LINE AS WELL THIS GIVE DEDICATED ADDRESS FOR
 * EVERY PORT
 *
 * DATE: 12 AUGUST 2017
 * AMAR SINGH
 *
 */


#define LED_ONE 0x1u
#define LED_TWO 0x2u
#define CLOCK_GATE_ENABLE  (*((volatile unsigned int*)0x400fe608))/*THIS ENABLE THE GPIO ADDRESSS SECTION*/
#define GPIO_N_DIR  (*((volatile unsigned int*) 0x40064400))/*THIS IS USED TO SET THE DIRECTION OF GPIO PORTS*/
#define GPIO_N_DEN  (*((volatile unsigned int*) 0x4006451c))/*THIS IS TO MAKE OUTPUT OF GPIO PORT DIGITAL*/
#define GPIO_N_DATA_BASE  ((volatile unsigned int*)0x40064000)/*THIS IS BASE ADDRESS OF GPIO DATA REGISTER

THIS CAN BE USED AS ARRAY AS ALL ADDRESS LINE ARE ALSO CONNECTED TO GPIO PORTS
 */



void some_delay(void);

int main(void)
{

    (CLOCK_GATE_ENABLE) |= 0x1000 ;
    some_delay();

    GPIO_N_DIR |= (LED_ONE |LED_TWO);
    GPIO_N_DEN |= (LED_ONE| LED_TWO);


    while (1){

       GPIO_N_DATA_BASE[LED_ONE] = LED_ONE;/*ATOMIC ACCESS TO GPIO PORT*/
	/*THIS METHOD MUST ONLY BE USED IF ANY ISR ALSO USES A GPIO PORT*/
       some_delay();
       GPIO_N_DATA_BASE[LED_ONE] = ~LED_ONE;
       some_delay();
       GPIO_N_DATA_BASE[LED_TWO] = LED_TWO;
       some_delay();
       GPIO_N_DATA_BASE[LED_TWO] = ~LED_TWO;
       some_delay();

    }


    return 0;
}


void some_delay (){

    volatile int i;
    for(i = 0; i<200000;i++){
    }

}
