/*
 * Blinking led usando el controlador gpio
*/

#include <stdint.h>
#include "system.h"

gpio_pin_t  led    = PA5;
gpio_pin_t  button = PC13;

void
led_on (void)
{
    gpio_set_pin(led);
}

void
led_off (void)
{
    gpio_clear_pin(led);
}

void
pause (void)
{
    // Valor del contador de pausa
    uint32_t pause_counter = 0x00080000;

    for (int i = pause_counter; i != 0; --i);
}

int
main (void)
{

    // Configuro el pin del led en modo de salida de propósito general
    gpio_set_mode(led,  gpio_mode_output);
    // Configuro el pin del botón en modo de entrada
    gpio_set_mode(button, gpio_mode_input);

    for (;;)
    {
        if (gpio_get_input_pin(button) == 0)
        {
            if (gpio_get_output_pin(led) == 0)
                led_on();
            else
                led_off();

            pause();
        }
    }
}
