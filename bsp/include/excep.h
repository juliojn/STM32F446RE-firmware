#ifndef _EXCEP_
#define _EXCEP_

#include <stdint.h>

/*
 * Tipos de fuentes de excepción
 * Primer valor igual a 2 al ser la segunda posición del vector _isr_vector
 */
typedef enum
{
    excep_nmi                   = 0,
    excep_hard_fault,
    excep_mem_manage,
    excep_bus_fault,
    excep_usage_fault,
    excep_svc                   = 9,
    excep_debug_monitor,
    excep_pendsv                = 12,
    excep_systick,
    excep_max
} excep_t;

typedef enum
{
   excep_priority_0             = 0x00,     // Mayor prioridad
   excep_priority_1             = 0x10,
   excep_priority_2             = 0x20,
   excep_priority_3             = 0x30,
   excep_priority_4             = 0x40,
   excep_priority_5             = 0x50,
   excep_priority_6             = 0x60,
   excep_priority_7             = 0x70,
   excep_priority_8             = 0x80,
   excep_priority_9             = 0x90,
   excep_priority_10            = 0xA0,
   excep_priority_11            = 0xB0,
   excep_priority_12            = 0xC0,
   excep_priority_13            = 0xD0,
   excep_priority_14            = 0xE0,
   excep_priority_15            = 0xF0,     // Menor prioridad
} excep_priority_t;

/*
 * Prototipo para los manejadores de excepción
 */
typedef void (* excep_handler_t) (void);

/*
 * Deshabilita todas las excepciones
 * No afecta a la excepción Non-Maskable Interrupt (NMI)
 * @return excep Valor del registro FAULTMASK antes de deshabilitar las
 * excepciones
 */
uint32_t excep_disable_faultmask ();

/*
 * Habilita todas las excepciones
 * No afecta a la excepción Non-Maskable Interrupt (NMI)
 * @param excep Valor del registro FAULTMASK antes de deshabilitar las
 * excepciones
 */
void excep_enable_faultmask  (uint32_t faultmask);

/*
 * Deshabilita todas las excepciones
 * No afecta a las excepciones Non-Maskable Interrupt (NMI) ni a HardFault
 * @return excep Valor del registro PRIMASK antes de deshabilitar las
 * excepciones
 */
uint32_t excep_disable_primask ();

/*
 * Habilita todas las excepciones
 * No afecta a las excepciones Non-Maskable Interrupt (NMI) ni a HardFault
 * @param excep Valor del registro PRIMASK antes de deshabilitar las excepciones
 */
void excep_enable_primask (uint32_t primask);

/*
 * Asigna un manejador de excepción a una excepción
 * @param excep	Tipo de excepción
 * @param handler Manejador de excepción
 */
void excep_set_handler (excep_t excep, excep_handler_t handler);

/*
 * Devuelve un manejador de excepción
 * @param excep	Tipo de excepción
 * @return Manejador de excepción
 */
excep_handler_t excep_get_handler (excep_t excep);

/*
 * Asigna una prioridad a una excepción
 * @param excep	Tipo de excepción
 * @param priority Tipo de prioridad
 */
void excep_set_priority(excep_t excep, excep_priority_t priority);

/*
 * Devuelve una prioridad de excepción
 * @param excep	Tipo de excepción
 * @return Tipo de prioridad
 */
excep_priority_t excep_get_priority(excep_t excep);

#endif  // _EXCEP_
