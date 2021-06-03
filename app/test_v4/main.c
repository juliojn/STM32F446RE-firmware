/*
 * Blinking led usando el manejador de excepciones
 */

#include <stdint.h>
#include "system.h"

// Registro de datos del GPIO port A mode register
volatile uint32_t * gpioa_moder     = (uint32_t *) 0x40020000;

// Registro de datos del AHB1 peripheral clock enable register
// para la apertura de los periféricos del bus AHB1
volatile uint32_t * rcc_ahb1enr     = (uint32_t *) 0x40023830;

// Registro de datos del GPIO port A bit set reset register
volatile uint32_t * gpioa_bsrr      = (uint32_t *) 0x40020018;

// Registro de datos del APB1 peripheral clock enable register
volatile uint32_t * rcc_apb1enr     = (uint32_t *) 0x40020040;

// Máscaras de los registros
uint32_t gpioa_moder_mask           = 01 << (2 * 5);
uint32_t rcc_ahb1enr_mask           = 0x000000FF;
uint32_t gpioa_bsrr_set_mask        = 1  << 5;
uint32_t gpioa_bsrr_reset_mask      = 1  << (16 + 5);

// void gpio_init(void) __attribute__((always_inline));
// void led_on(void) __attribute__((always_inline));
// void led_off(void) __attribute__((always_inline));
// void pause(void) __attribute__((always_inline));

void
gpio_init (void)
{
    // Habilito la apertura de los puertos de entrada/salida
    *rcc_ahb1enr |= rcc_ahb1enr_mask;

    // Configuro el pin PA5 en modo de salida de propósito general
    *gpioa_moder |= gpioa_moder_mask;
}

void
led_on (void)
{
    *gpioa_bsrr = gpioa_bsrr_set_mask;
}

void
led_off (void)
{
    *gpioa_bsrr = gpioa_bsrr_reset_mask;
}

void
pause (void)
{
    // Valor del contador de pausa
    uint32_t pause_counter = 0x00040000;

    for (int i = pause_counter; i != 0; --i)
    {
        --pause_counter;
    }
}

void
blinking_led ()
 {
     for (;;)
     {
         led_on();
         pause();
         led_off();
         pause();
     }
 }


int
main (void)
{
    excep_priority_t priority;

    excep_enable_faultmask(EXCEPTIONS_ENABLED);
    gpio_init();
    excep_set_handler(excep_svc, blinking_led);
    excep_set_priority(excep_svc, excep_priority_15);
    priority = excep_get_priority(excep_svc);

    if (excep_priority_15 == priority)
        asm volatile("svc #0");
}
