/*
 * Inicialización del HAL
 */

#include <fcntl.h>
#include <unistd.h>
#include "system.h"

void bus_init()
{
    gpio_bus_init();
    usart_bus_init();
}

void io_init()
{
    usart_init(usart_2, USART2_BAUDRATE, USART2_NAME);

    redirect_fd (STDIN_FILENO, BSP_STDIN, O_RDONLY, 0777);
    redirect_fd (STDOUT_FILENO, BSP_STDOUT, O_RDONLY, 0777);
    redirect_fd (STDERR_FILENO, BSP_STDERR, O_RDONLY, 0777);
}

void bsp_init (void)
{
    bus_init();
    io_init();
}
