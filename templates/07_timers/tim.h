#ifndef TIM_H_
#define TIM_H_

#include "stm32f103x6.h"
#define SR_UIF (1U << 0)

void tim2_1hz_init(void);

#endif /* TIM_H_ */
