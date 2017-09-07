

/*
 * THIS CODE IS TO TEST THE INPUT BUTTONS ON TM4C1294XL
 * AUTHOR: AMAR SINGH
 * 20 AUGUST 2017
 *
 * ONE BUTTON WILL SWITCH ON ONE LED
 * ANOTHER BUTTON WILL SWITCTH ON ANOTHER LED
 *
 * */

/*LED REGISTERS PORT N*/
#define LED_ONE 0x1u
#define LED_TWO 0x2u
#define CLOCK_GATE_ENABLE  (*((volatile unsigned int*)0x400fe608))
#define GPIO_N_DIR  (*((volatile unsigned int*) 0x40064400))/*THIS IS USED TO SET THE DIRECTION OF GPIO PORTS*/
#define GPIO_N_DEN  (*((volatile unsigned int*) 0x4006451c))/*THIS IS TO MAKE OUTPUT OF GPIO PORT DIGITAL*/
#define GPIO_N_DATA_BASE  ((volatile unsigned int*)0x40064000)/*THIS IS BASE ADDRESS OF GPIO DATA REGISTER
THIS CAN BE USED AS AN ARRAY AS ALL GPIO PORTS ARE ALSO CONNECTED TO ADDRESS LINES */

/*SWITCH BUTTON REGISTERS PORT J*/
#define BUTT1 0x1u
#define BUTT2 0x2u
#define GPIO_J_DIR (*(volatile unsigned int*)(0x40060400))
#define GPIO_J_DEN (*(volatile unsigned int*)(0x4006051c))
#define GPIO_J_DATA_BASE ((volatile unsigned int*)(0x40060000))
#define GPIO_J_PUR (*(volatile unsigned int*)(0x40060510))
#define GPIO_J_CR (*(volatile unsigned int*)(0x40060524))/*commit register*/
#define GPIO_J_LOCK (*(volatile unsigned int*)(0x40060520))



void some_delay(int);

int main(void)
{

    /*INITIALIZING PORT N AND J*/
    CLOCK_GATE_ENABLE |= (0x1u << 12 | 0x1u << 8);
    some_delay(0); /*inserting some delay for hardware initialization*/

    /*LED INITIALIZATION*/
    GPIO_N_DIR |= (LED_ONE|LED_TWO);
    GPIO_N_DEN |= (LED_ONE|LED_TWO);

    /*BUTTON INITIALIZATION*/
    GPIO_J_LOCK = 0x4c4f434b;
    GPIO_J_CR |= (BUTT1 | BUTT2);
    GPIO_J_DIR &= ~(BUTT1 | BUTT2);
    GPIO_J_PUR |= (BUTT1 | BUTT2);
    GPIO_J_DEN |= (BUTT1 | BUTT2);


    GPIO_N_DATA_BASE[LED_ONE] = ~LED_ONE;
    GPIO_N_DATA_BASE[LED_TWO] = ~LED_TWO;

    while(1){

        while(GPIO_J_DATA_BASE[BUTT1]==0){

            GPIO_N_DATA_BASE[LED_ONE] = LED_ONE;

        }
        GPIO_N_DATA_BASE[LED_ONE] = ~LED_ONE;
        while(GPIO_J_DATA_BASE[BUTT2]==0){
            GPIO_N_DATA_BASE[LED_TWO] = LED_TWO;

        }
        GPIO_N_DATA_BASE[LED_TWO] = ~LED_TWO;
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

