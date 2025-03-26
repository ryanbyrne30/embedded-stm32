#include "gpio.h"
#include "stm32f103x6.h"

#define GPIOCEN (1U << 4)
#define LED_BS13 0x20000000 /* Bit set Pin 13 */
#define LED_BR13 0x2000     /* Bit reset Pin 13 */
#define LED_ODR13 0x2000    /* Bit set Pin 13 */

void led_init(void)
{
    /* Enable clock access to GPIOC */
    RCC->APB2ENR |= GPIOCEN;

    /* Set PA13 mode */
    GPIOC->CRH &= 0xFF0FFFFF;
    GPIOC->CRH |= 0x00200000;
}

void led_on(void)
{
    /* Set PC13 high */
    GPIOC->BSRR = LED_BS13;
}

void led_off(void)
{
    /* Set PC13 low */
    GPIOC->BSRR = LED_BR13;
}

void led_toggle(void)
{
    /* Set PC13 low */
    GPIOC->ODR ^= LED_ODR13;
}