#include "gpio.h"

typedef struct
{
    uint32_t MODER;             // GPIO port mode register
    uint32_t OTYPER;            // GPIO port output type register
    uint32_t OSPEEDR;           // GPIO port output speed register
    uint32_t PUPDR;             // GPIO port pull-up/pull-down register
    uint32_t IDR;               // GPIO port input data register
    uint32_t ODR;               // GPIO port output data register
    uint32_t BSRR;              // GPIO port bit set/reset register
    uint32_t LCKR;              // GPIO port configuration lock register
    uint32_t AFR[2];            // GPIO alternate function registers
    uint8_t reserved[0x3D8];    // bytes de relleno
} gpio_regs_t;

static volatile gpio_regs_t* const gpio_regs[gpio_max] = {GPIOA_BASE,
    GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE, GPIOF_BASE, GPIOG_BASE};

void gpio_bus_init()
{
    // Registro de datos del AHB1 peripheral clock enable register
    // para la apertura de los periféricos del bus AHB1
    volatile uint32_t * rcc_ahb1enr     = (uint32_t *) 0x40023830;
	uint32_t rcc_ahb1enr_mask           = 0x000000FF;

    // Habilito la apertura de los puertos de entrada/salida
    *rcc_ahb1enr |= rcc_ahb1enr_mask;
}

void gpio_set_mode (gpio_pin_t pin, gpio_mode_t mode)
{
    gpio_regs[pin / 16]->MODER &= ~(3    << ((pin % 16) * 2));
    gpio_regs[pin / 16]->MODER |=  (mode << ((pin % 16) * 2));
}

void gpio_set_output_type (gpio_pin_t pin, gpio_output_type_t output_type)
{
    if (gpio_output_type_push_pull == output_type)
        gpio_regs[pin / 16]->OTYPER &= ~(1 << (pin % 16));
    else
        gpio_regs[pin / 16]->OTYPER |=  (1 << (pin % 16));
}

void gpio_set_output_speed (gpio_pin_t pin, gpio_speed_t speed)
{
    gpio_regs[pin / 16]->OSPEEDR &= ~(3     << ((pin % 16) * 2));
    gpio_regs[pin / 16]->OSPEEDR |=  (speed << ((pin % 16) * 2));
}

void gpio_set_pull_up_pull_down (gpio_pin_t pin, gpio_pull_t pull)
{
    gpio_regs[pin / 16]->PUPDR &= ~(3     << ((pin % 16) * 2));
    gpio_regs[pin / 16]->PUPDR |=  (pull << ((pin % 16) * 2));
}

void gpio_set_pin (gpio_pin_t pin)
{
    gpio_regs[pin / 16]->BSRR = 1 << (pin % 16);
}

void gpio_clear_pin (gpio_pin_t pin)
{
    gpio_regs[pin / 16]->BSRR = 1 << ((pin % 16) + 16);
}

void gpio_set_function_pin (gpio_pin_t pin, gpio_alternate_function_t function)
{
    gpio_regs[pin / 16]->AFR[(pin % 16) / 8]  &= ~(0xF      << ((pin % 8) * 4));
    gpio_regs[pin / 16]->AFR[(pin % 16) / 8]  |=  (function << ((pin % 8) * 4));
}

uint32_t gpio_get_input_pin (gpio_pin_t pin)
{
    return gpio_regs[pin / 16]->IDR;
}

uint32_t gpio_get_output_pin(gpio_pin_t pin)
{
    return gpio_regs[pin / 16]->ODR;
}
