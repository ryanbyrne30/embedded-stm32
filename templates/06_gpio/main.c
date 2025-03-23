#include "gpio.h"

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

    int code[3][3] = {
        {DIT, DIT, DIT},
        {DAH, DAH, DAH},
        {DIT, DIT, DIT}};

    while (1)
    {
        led_off(); /* Reset state */

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j > 0)
                {
                    delay(P_DOT);
                }
                int duration = code[i][j];
                blink(duration);
            }
            delay(P_LETTER);
        }
        delay(P_WORD);
    }

    return 0;
}