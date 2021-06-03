/*
 * Transmisión y recepción de un byte usando uart, junto con Newlib
*/

#include <stdint.h>
#include <stdio.h>
#include "system.h"
#include <errno.h>
#include <string.h>
void
gpio_init()
{
    gpio_pin_t  led    = PA5;

    // Configuro el pin del led en modo de salida de propósito general
    gpio_set_mode(led,  gpio_mode_output);
}

void
led_on (void)
{
    gpio_set_pin(PA5);
}

void
led_off (void)
{
    gpio_clear_pin(PA5);
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
    gpio_init();

    for (;;)
    {
        led_on();
        pause();
        led_off();
        pause();
        iprintf("hola mundo\r\n");
    }
}
