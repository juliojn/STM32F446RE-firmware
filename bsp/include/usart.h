#ifndef _USART_H_
#define _USART_H_

#include "system.h"

typedef enum
{
    usart_1, usart_2, usart_3, uart_4, uart_5, usart_6, usart_max
} usart_id_t;

/*
 *  Inicialización del bus de configuración de los registros USART
 */
void usart_bus_init ();

void usart_init (usart_id_t usart, uint32_t baudrate, const uint8_t * name);

void usart_send_byte (usart_id_t usart, uint8_t c);

uint8_t usart_receive_byte (usart_id_t usart);

void usart_send (usart_id_t usart, uint8_t * buf, uint32_t size);

void usart_receive (usart_id_t usart, uint8_t * buf, uint32_t size);
#endif  // _USART_H_
