

/*this code blinks two the LED 
 *connected to port N
 * AMAR SINGH
 */


#define clock_gating_enable  (*((volatile unsigned int*)0x400fe608))
#define GPIO_N_DIR  (*((volatile unsigned int*) 0x40064400))
#define GPIO_N_DEN  (*((volatile unsigned int*) 0x4006451c))
#define GPIO_N_DATA  (*((volatile unsigned int*)0x400643fc))

void some_delay(void);

int main(void)
{


    (clock_gating_enable) |= 0x000001000 ;/*providing clock to GPIO N port*/
    some_delay(); /*above power up takes some time*/

    GPIO_N_DIR |= 0x03;
    GPIO_N_DEN |= 0x03;


    while (1){

       GPIO_N_DATA  |= 0x03;/*switching ON both LEDs*/
        some_delay();
       GPIO_N_DATA  &= ~(0x03);/*switching OFF*/
        some_delay();
      

    }


    return 0;
}


void some_delay (){
    volatile int i;
    for(i = 0; i<200000;i++){


    }

}
