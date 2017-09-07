

/*
 * THIS CODE IS TO TEST THE TIMER FUNCTIONALITY ON THE TM4C1294XL
 * AUTHOR: AMAR SINGH
 * 25 AUGUST 2017
 *
 * BLINK THE LED WITH TIMER0
 *
 * */

/*LED REGISTERS PORT N*/
#define LED_ONE 0x1u
#define LED_TWO 0x2u
#define CLOCK_GATE_ENABLE  (*((volatile unsigned int*)0x400fe608))
#define GPIO_N_DIR  (*((volatile unsigned int*) 0x40064400))/*THIS IS USED TO SET THE DIRECTION OF GPIO PORTS*/
#define GPIO_N_DEN  (*((volatile unsigned int*) 0x4006451c))/*THIS IS TO MAKE OUTPUT OF GPIO PORT DIGITAL*/
#define GPIO_N_DATA_BASE  ((volatile unsigned int*)0x40064000)/*THIS IS BASE ADDRESS OF GPIO DATA REGISTER
THIS CAN BE USED AS ARRAY AS ALL GPIO PORTS ARE ALSO CONNECTED TO ADDRESS LINE   */

/*TIMER REGISTERS*/
#define RCGCTIMER (*(volatile unsigned int*)(0x400fe604))/*clock gating*/
#define T0_CFG (*(volatile unsigned int*)(0x40030000))/*configuration*/
#define T0TA_MR (*(volatile unsigned int*)(0x40030004))/*mode register*/
#define T0_CTL (*(volatile unsigned int*)(0x4003000c))/*control */
#define T0_IM (*(volatile unsigned int*)(0x400030018))/*Interrupt MAsk*/
#define T0_RIS (*(volatile unsigned int*)(0x4003001c))/*RAW interrupt STATUS*/
#define T0_MIS (*(volatile unsigned int*)(0x40030020))/*MASKED INTERRUPT STATUS*/
#define T0_IC (*(volatile unsigned int*)(0x40030024)) /*INTERRUPT CLEAR*/
#define T0TA_IL (*(volatile unsigned int*)(0x40030028))/*INTERVAL load*/


void some_delay(int);

int main(void)
{

    /*INITIALIZING PORT N */
    CLOCK_GATE_ENABLE |= (0x1u << 12 );
    RCGCTIMER |= (0x1u << 0);/*Powering UP TIMER 0*/
    some_delay(0); /*Inserting some delay for hardware initialization*/

    /*LED INITIALIZATION*/
    GPIO_N_DIR |= (LED_ONE|LED_TWO);
    GPIO_N_DEN |= (LED_ONE|LED_TWO);

    /*TIMER INITIALIZATION*/
    T0_CTL &= ~(0x1u << 0);/*step 1:  DISABLING The Timer A */
    T0_CFG &= ~(0x7u);/*Step 2 :  Configuring Timer A for 32 Bit Timer*/
    T0TA_MR |= (0x2u );/*Step 3: Configuring the T0 Timer A mode for Periodic*/
    T0TA_MR |= (0x1u << 4);/*step 4: configuring UP Counter*/
    T0TA_IL = (0xFFFFFF); /*step 5: Load The interval count*/
    /*step 6: INterrupt MASK*/





    GPIO_N_DATA_BASE[LED_ONE] = LED_ONE;
    GPIO_N_DATA_BASE[LED_TWO] = LED_TWO;

    T0_CTL |= (0x1u << 0);/*Enabling the Timer*/

    while(1){

        if((T0_RIS & 0x1u)){/*POLLING*/
            GPIO_N_DATA_BASE[LED_ONE] ^= LED_ONE;
            T0_IC |= (0x1u << 0);/*clearing the bit set after the counter runoff*/
        }



    }
    return 0;
}

void some_delay(int count){

    if (count == 0)
        return;

    do{
        count--;
    }while(count != 0);
}

