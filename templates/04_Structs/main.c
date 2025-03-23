#include <stdint.h>

/* GPIO structure */
typedef struct
{
    volatile uint32_t CRL;  /* offset: 0x00 */
    volatile uint32_t CRH;  /* offset: 0x04 */
    volatile uint32_t IDR;  /* offset: 0x08 */
    volatile uint32_t ODR;  /* offset: 0x0C */
    volatile uint32_t BSRR; /* offset: 0x10 */
    volatile uint32_t BRR;  /* offset: 0x14 */
    volatile uint32_t LCKR; /* offset: 0x18 */

} GPIO_TypeDef;

/* RCC structure */
typedef struct
{
    volatile uint32_t DUMMY[6];
    volatile uint32_t APB2ENR; /* offset: 0x18 */
} RCC_Typedef;

/* Base addresses */
#define RCC_BASE 0x40021000
#define GPIOC_BASE 0x40011000

/* Peripheral pointer definitions */
#define RCC ((RCC_Typedef *)RCC_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)

/* Bit masks for enabling GPIOC */
#define GPIOCEN (1U << 4)

/* Bit mask for Pin 13 */
#define PIN13 (1U << 13)

/* Alias for Pin13 representing LED pin */
#define LED_PIN PIN13

#define PAUSE_DURATION 500
#define DOT_DURATION 500
#define DASH_DURATION 2000

void delay(int ms)
{
    for (int i = 0; i < (ms * 500); i++)
        ;
}

/*
    Note: I'm not sure why setting the 13th pin to 0 seems to enable to LED
    and setting to 1 seems to disable the LED with the ODR register.
*/
void ledOff()
{
    GPIOC->ODR |= LED_PIN;
}

void ledBlink(int duration)
{
    GPIOC->ODR &= ~LED_PIN;
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
        delay(PAUSE_DURATION);

        ledOff();
        delay(10000);

        // GPIOC->ODR |= LED_PIN;

        // GPIOC->ODR ^= LED_PIN;
        // for (int i = 0; i < 100000; i++)
        //     ;
    }
}