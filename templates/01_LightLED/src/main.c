/*
In order to light up the LED at PC13 we need to do the following:

1. Figure out the base memory address of peripherals (0x40000000)

2. Figure out the base memory address of Port C (GPIOC) from the base address (0x40011000)

3. Figure out the base memory address of the RCC block in order to control enabling/disabling clock functionality for ports (0x40021000)

4. Figure out the memory address of the specific register (RCC_APB2_ENR) that controls clock functionlaty for Port C (bus APB2) (0x40021018)

5. Enable the clock for Port C by setting the value of the register to 1<<4

6. Figure out the memory address of the register (CRH) that controls the mode of GPIOC/Port C (0x40011004)

7. Configure the mode for GPIOC to enable writing to pin 13 of GPIOC

8. Figure of the memory address of the output data register (ODR) (0x4001101C)

9. Set the ODR value for GPIOC to high for pin 13
*/

// User LED is PC13

// Base memory address of peripherals
#define PERIPH_BASE (0x40000000UL)

// GPIOC (Port C) is the block of memory that the target LED is located in
#define GPIOC_OFFSET (0x11000UL)
#define GPIOC (PERIPH_BASE + GPIOC_OFFSET)

// RCC is the base of the memory block that allows for enable/disabling
// the clock for different parts of the processor
#define RCC_OFFSET (0x21000UL)
#define RCC (PERIPH_BASE + RCC_OFFSET)

// RCC_APB2_ENR memory address controls enabling/disabling the clock for APB2 bus on the processor
#define APB2_ENR_OFFSET (0x18UL)
#define RCC_APB2_ENR (*(volatile unsigned int *)(RCC + APB2_ENR_OFFSET))

// CRL/CRH are registers that control the modes of the respective port
#define GPIOC_CRH_OFFSET (0x04UL)
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC + GPIOC_CRH_OFFSET))

// ODR is the Output Data Register which controls the output state
// of a port
#define ODR_OFFSET (0x1CUL)
#define GPIOC_ODR (*(volatile unsigned int *)(GPIOC + ODR_OFFSET))

// BSRR is similar to ODR except that it provides atomic, bit-level
// control for setting/resetting bits
#define GPIOC_BSRR_OFFSET (0x18UL)
#define GPIOC_BSRR (*(volatile unsigned int *)(GPIOC + GPIOC_BSRR_OFFSET))

// bit mask for enabling GPIOC (bit 4)
#define GPIOC_EN_MASK (1U << 4)

#define GPIO_CRH_MODE13 (0x2U << 20)
#define GPIO_CRH_CNF13 (0x3U << 22)

// bit mask for GPIOC pin 13
#define PIN13_MASK (1U << 13)

#define LED_PIN PIN13_MASK

int main(void)
{
    // enable clock access to GPIOC
    RCC_APB2_ENR |= GPIOC_EN_MASK; // sets 4 bit to 1

    // set output mode to push-pull
    GPIOC_CRH &= ~(GPIO_CRH_CNF13);

    // set mode to output mode max 2MHz
    GPIOC_CRH |= GPIO_CRH_MODE13;

    while (1)
    {
        // Set state of pin 13 to output high
        GPIOC_ODR |= LED_PIN;
        // GPIOC_BSRR |= LED_PIN;
    }
}