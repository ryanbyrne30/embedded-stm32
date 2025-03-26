#include "tim.h"
#define TIM2EN (1U << 0)  /* Enable TIM9 in APB2_ENR */
#define CR1_CEN (1U << 0) /* Enable counter TIMx_CR1 */

void tim2_1hz_init(void)
{
    /* Enable clock access to TIM9 */
    RCC->APB1ENR |= TIM2EN;

    /* Set prescaler value (SYSCLK is 8MHz -> Timer => 10kHz clock) */
    TIM2->PSC = 800 - 1;

    /* Set auto-reload value (10kHz clock results in 10,000 ticks per second) */
    TIM2->ARR = 10000 - 1;

    /* Clear counter */
    TIM2->CNT = 0;

    /* Enable timer */
    TIM2->CR1 = CR1_CEN;
}
