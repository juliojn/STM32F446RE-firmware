/*
 * Transmisión y recepción de un byte usando uart
*/

#include <stdint.h>
#include <float.h>
#include "system.h"

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

// void
// mostrar_mensaje

int
main (void)
{
    char c[2];

    gpio_init();
    usart_init(usart_2, USART2_BAUDRATE, USART2_NAME);

    for (;;)
    {
        led_on();
        pause();
        led_off();
        pause();
        usart_send(usart_2, "hola mundo\r\n", 12);

        usart_send(usart_2, "Inserte dos letras: ", 19);
        usart_receive(usart_2, c, 2);
        usart_send(usart_2, "\r\nLas letras insertadas son: ", 29);
        usart_send(usart_2, c, 2);
        usart_send(usart_2, "\r\n", 2);

    }
}
