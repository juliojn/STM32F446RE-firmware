/*
 * Configuración del sistema
 */

#ifndef _SYSTEM_H
#define _SYSTEM_H

#define EXCEPTIONS_ENABLED  0
#define EXCEPTIONS_DISABLED 1

#include "excep.h"
#include "nvic.h"
#include "gpio.h"
#include "usart.h"
#include "dev.h"

// High-speed internal clock
#define HSI_FREQUENCY   16000000

#define NVIC_BASE       ((void *) 0xE000E100)
#define SCB_BASE        ((void *) 0xE000E008)

#define GPIOA_BASE      ((void *) 0x40020000)
#define GPIOB_BASE      ((void *) 0x40020400)
#define GPIOC_BASE      ((void *) 0x40020800)
#define GPIOD_BASE      ((void *) 0x40020C00)
#define GPIOE_BASE      ((void *) 0x40021000)
#define GPIOF_BASE      ((void *) 0x40021400)
#define GPIOG_BASE      ((void *) 0x40021800)
#define GPIOH_BASE      ((void *) 0x40021C00)

#define USART1_BASE     ((void *) 0x40011000)
#define USART2_BASE     ((void *) 0x40004400)
#define USART3_BASE     ((void *) 0x40004800)
#define UART4_BASE      ((void *) 0x40004C00)
#define UART5_BASE      ((void *) 0x40005000)
#define USART6_BASE     ((void *) 0x40011400)

#define USART1_NAME     "/dev/usart1"
#define USART2_NAME     "/dev/usart2"
#define USART3_NAME 	"/dev/usart3"
#define UART4_NAME 		"/dev/uart4"
#define UART5_NAME 		"/dev/uart5"
#define USART6_NAME 	"/dev/usart6"


#define USART1_BAUDRATE     115200
#define USART2_BAUDRATE     115200
#define USART3_BAUDRATE     115200
#define UART4_BAUDRATE      115200
#define UART5_BAUDRATE      115200
#define USART6_BAUDRATE     115200

#define BSP_STDIN       USART2_NAME
#define BSP_STDOUT      USART2_NAME
#define BSP_STDERR      USART2_NAME

#define DEV_MAX         16
#define FD_MAX          16
#endif  // _SYSTEM_H
