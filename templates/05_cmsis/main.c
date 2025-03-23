#include <stdint.h>
#include "stm32f103x6.h"

/* Bit masks for enabling GPIOC */
#define GPIOCEN (1U << 4)

/* Bit mask for Pin 13 */
#define BS13 0x20000000
#define BR13 0x2000

#define PAUSE_DURATION 500
#define DOT_DURATION 500
#define DASH_DURATION 2000

void delay(int ms)
{
    for (int i = 0; i < (ms * 300); i++)
        ;
}

void ledOff()
{
    GPIOC->BSRR = BR13;
}

void ledBlink(int duration)
{
    GPIOC->BSRR = BS13;
    delay(duration);
    ledOff();
}

int main(void)
{
    // Enable clock for GPIOC
    RCC->APB2ENR |= GPIOCEN;

    GPIOC->CRH &= 0xFF0FFFFF;
    GPIOC->CRH |= 0x00200000;

    while (1)
    {
        ledOff();
        /* S */
        ledBlink(DOT_DURATION);
        delay(PAUSE_DURATION);
        ledBlink(DOT_DURATION);
        delay(PAUSE_DURATION);
        ledBlink(DOT_DURATION);
        delay(PAUSE_DURATION);

        /* O */
        ledBlink(DASH_DURATION);
        delay(PAUSE_DURATION);
        ledBlink(DASH_DURATION);
        delay(PAUSE_DURATION);
        ledBlink(DASH_DURATION);
        delay(PAUSE_DURATION);

        /* S */
        ledBlink(DOT_DURATION);
        delay(PAUSE_DURATION);
        ledBlink(DOT_DURATION);
        delay(PAUSE_DURATION);
        ledBlink(DOT_DURATION);

        delay(10000);
    }
}