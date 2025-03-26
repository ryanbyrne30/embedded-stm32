#include "gpio.h"
#include "tim.h"

#define DIT 1      /* Time for dit or dot */
#define DAH 3      /* Time for dah or dash */
#define P_DOT 1    /* Pause for character/dot */
#define P_LETTER 3 /* Pause for letter */
#define P_WORD 7   /* Pause for word */

void delay(int ms)
{
    for (int i = 0; i < (ms * 50000); i++)
        ;
}

void blink(int duration)
{
    led_on();
    delay(duration);
    led_off();
}

int main(void)
{
    led_init();
    tim2_1hz_init();

    while (1)
    {
        led_toggle();
        while (!(TIM2->SR & SR_UIF))
        {
        }
        TIM2->SR &= ~SR_UIF;
    }

    return 0;
}