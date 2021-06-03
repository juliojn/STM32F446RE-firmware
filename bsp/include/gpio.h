#ifndef _GPIO_H_
#define _GPIO_H_

#include "system.h"

typedef enum
{
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,
    PA14, PA15,
    PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13,
    PB14, PB15,
    PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13,
    PC14, PC15,
    PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13,
    PD14, PD15,
    PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, PE12, PE13,
    PE14, PE15,
    PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7, PF8, PF9, PF10, PF11, PF12, PF13,
    PF14, PF15,
    PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13,
    PG14, PG15, PG16,
    PH0, PH1, PH2, PH3, PH4, PH5, PH6, PH7, PH8, PH9, PH10, PH11, PH12, PH13,
    PH14, PH15
} gpio_pin_t;

typedef enum
{
    gpio_a, gpio_b, gpio_c, gpio_d, gpio_e, gpio_f, gpio_g, gpio_h, gpio_max
} gpio_port_t;

typedef enum
{
    gpio_mode_input, gpio_mode_output, gpio_mode_alternate, gpio_mode_analog
} gpio_mode_t;

typedef enum
{
    gpio_output_type_push_pull, gpio_output_type_open_drain
} gpio_output_type_t;

typedef enum
{
    gpio_speed_low, gpio_speed_medium, gpio_speed_fast, gpio_speed_high
} gpio_speed_t;

typedef enum
{
    gpio_pull_no, gpio_pull_up, gpio_pull_down
} gpio_pull_t;

typedef enum
{
    AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12, AF13,
    AF14, AF15, AF_max
} gpio_alternate_function_t;


// typedef enum
// {
//     gpio_no_error, gpio_invalid_paramether
// } gpio_error_t

/*
 *  Inicialización del bus de configuración de los pines de entrada/salida
 */
void gpio_bus_init();

/*
 * Establece el modo del pin seleccionado
 * @param pin   Pin del GPIO a modificar
 * @param mode  Modo a configurar del pin:
 *              gpio_mode_input     Modo de entrada
 *              gpio_mode_output    Modo de salida de propósito general
 *              gpio_mode_alternate Modo alternativo
 *              gpio_mode_analog    Modo analógico
 */
void gpio_set_mode(gpio_pin_t pin, gpio_mode_t mode);

/*
 * Establece el modo de salida del pin seleccionado
 * @param pin   Pin del GPIO a modificar
 * @param type  Modo de salida a configurar del pin:
 *              gpio_output_type_push_pull      Modo push-pull
 *              gpio_output_type_open_drain     Modo drenador abierto
 */
void gpio_set_output_type(gpio_pin_t pin, gpio_output_type_t output_type);

/*
 * Establece la velocidad de salida del pin seleccionado
 * @param pin   Pin del GPIO a modificar
 * @param speed Velocidad de salida a configurar del pin:
 *              gpio_speed_low      Velocidad de salida baja    (Menor valor)
 *              gpio_speed_medium   Velocidad de salida media
 *              gpio_speed_fast     Velocidad de salida rápida
 *              gpio_speed_high     Velocidad de salida alta    (Mayor valor)

 */
void gpio_set_output_speed(gpio_pin_t pin, gpio_speed_t speed);

/*
 * Establece el modo pull_up y pull_down del pin seleccionado
 * @param pin   Pin del GPIO a modificar
 * @param pull  Modo de pull del pin a modificar:
 *              gpio_pull_no    Entrada/salida directa
 *              gpio_pull_up    Modo pull-up
 *              gpio_pull_down  Modo pull-down
 */
void gpio_set_pull_up_pull_down(gpio_pin_t pin, gpio_pull_t pull);

/*
 * Establece el valor de salida del pin seleccionado a 1
 * @param pin   Pin del GPIO a modificar
 */
void gpio_set_pin(gpio_pin_t pin);

/*
 * Establece el valor de salida del pin seleccionado a 0
 * @param pin   Pin del GPIO a modificar
 */
void gpio_clear_pin(gpio_pin_t pin);

/*
 * Establece la función alternativa del pin seleccionado
 * @param pin       Pin del GPIO a modificar
 * @param function  Función del pin
 */
void gpio_set_function_pin (gpio_pin_t pin, gpio_alternate_function_t function);

/*
 * Devuelve el valor de entrada del pin seleccionado
 * @param pin   Pin del GPIO a leer
 * @return valor del pin:
 *              0 en caso de un 0 lógico
 *              Distinto de 0 en caso de un 1 lógico
 */
uint32_t gpio_get_input_pin(gpio_pin_t pin);

/*
 * Devuelve el valor de salida del pin seleccionado
 * @param pin   Pin del GPIO a leer
 * @return valor del pin:
 *              0 en caso de un 0 lógico
 *              Distinto de 0 en caso de un 1 lógico
 */
uint32_t gpio_get_output_pin(gpio_pin_t pin);

#endif  // _GPIO_H_
