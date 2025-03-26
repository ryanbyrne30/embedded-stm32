#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f103x6.h"

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif /* GPIO_H_ */
