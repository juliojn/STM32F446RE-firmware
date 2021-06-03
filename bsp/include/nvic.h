/*
 * Driver para el controlador de interrupciones de la placa STM32F446RE
 */


#ifndef _NVIC_H_
#define _NVIC_H_

#include "system.h"

typedef enum
{
    nvic_src_wwdg = 0,
    nvic_src_pvd,
    nvic_src_tamp_stamp,
    nvic_src_rtc_wkup,
    nvic_src_flash,
    nvic_src_rcc,
    nvic_src_exti_0,
    nvic_src_exti_1,
    nvic_src_exti_2,
    nvic_src_exti_3,
    nvic_src_exti_4,
    nvic_src_dma_1_stream_0,
    nvic_src_dma_1_stream_1,
    nvic_src_dma_1_stream_2,
    nvic_src_dma_1_stream_3,
    nvic_src_dma_1_stream_4,
    nvic_src_dma_1_stream_5,
    nvic_src_dma_1_stream_6,
    nvic_src_adc,
    nvic_src_can_1_tx,
    nvic_src_can_1_rx_0,
    nvic_src_can_1_rx_1,
    nvic_src_can_1_sce,
    nvic_src_exti_9_5,
    nvic_src_tim_1_brk_tim_9,
    nvic_src_tim_1_up_tim_10,
    nvic_src_tim_1_trg_com_tim_11,
    nvic_src_tim_1_cc,
    nvic_src_tim_2,
    nvic_src_tim_3,
    nvic_src_tim_4,
    nvic_src_i2c_1_ev,
    nvic_src_i2c_1_er,
    nvic_src_i2c_2_ev,
    nvic_src_i2c_2_evr,
    nvic_src_spi_1,
    nvic_src_spi_2,
    nvic_src_usart_1,
    nvic_src_usart_2,
    nvic_src_usart_3,
    nvic_src_exti_15_10,
    nvic_src_rtc_alarm,
    nvic_src_otg_fs_wkup,
    nvic_src_tim_8_brk_tim_12,
    nvic_src_tim_8_up_tim_13,
    nvic_src_tim_8_trg_tim_14,
    nvic_src_tim_8_cc,
    nvic_src_dma_1_stream_7,
    nvic_src_fmc,
    nvic_src_sdio,
    nvic_src_tim_5,
    nvic_src_spi_3,
    nvic_src_uart_4,
    nvic_src_uart_5,
    nvic_src_tim_6_dac,
    nvic_src_tim_7,
    nvic_src_dma_2_stream_0,
    nvic_src_dma_2_stream_1,
    nvic_src_dma_2_stream_2,
    nvic_src_dma_2_stream_3,
    nvic_src_dma_2_stream_4,
    nvic_src_can_2_tx               = 63,
    nvic_src_can_2_rx_0,
    nvic_src_can_2_rx_1,
    nvic_src_can_2_sce,
    nvic_src_otg_fs,
    nvic_src_dma_2_stream_5,
    nvic_src_dma_2_stream_6,
    nvic_src_dma_2_stream_7,
    nvic_src_usart_6,
    nvic_src_i2c_3_ev,
    nvic_src_i2c_3_er,
    nvic_src_otg_hs_ep1_out,
    nvic_src_otg_hs_ep1_in,
    nvic_src_otg_hs_wkup,
    nvic_src_otg_hs,
    nvic_src_dcmi,
    nvic_src_fpu                    = 81,
    nvic_src_spi4                   = 84,
    nvic_src_sai_1                  = 87,
    nvic_src_sai_2                  = 91,
    nvic_src_quad_spi,
    nvic_src_hdmi_cec,
    nvic_src_spdif_rx,
    nvic_src_fmpi2c1,
    nvic_src_fmpi2c1_error,
    nvic_src_max
} nvic_src_t;

typedef enum
{
   nvic_priority_0             = 0x00,
   nvic_priority_1             = 0x10,
   nvic_priority_2             = 0x20,
   nvic_priority_3             = 0x30,
   nvic_priority_4             = 0x40,
   nvic_priority_5             = 0x50,
   nvic_priority_6             = 0x60,
   nvic_priority_7             = 0x70,
   nvic_priority_8             = 0x80,
   nvic_priority_9             = 0x90,
   nvic_priority_10            = 0xA0,
   nvic_priority_11            = 0xB0,
   nvic_priority_12            = 0xC0,
   nvic_priority_13            = 0xD0,
   nvic_priority_14            = 0xE0,
   nvic_priority_15            = 0xF0,
} nvic_priority_t;

/*
 * Prototipo para los manejadores de interrupción
 */
typedef void (* nvic_handler_t) (void);

/*
 * Asigna un manejador de interrupción a una interrupción
 * @param src	Fuente de la interrupción
 * @param handler Manejador de interrupción
 */
void nvic_set_handler (nvic_src_t src, nvic_handler_t handler);

/*
 * Devuelve un manejador de interrupción
 * @param src	Fuente de la interrupción
 * @return Manejador de interrupción
 */
nvic_handler_t nvic_get_handler (nvic_src_t src);

/*
 * Asigna una prioridad a una interrupción
 * @param src	Fuente de la interrupción
 * @param priority Tipo de prioridad
 */
void nvic_set_priority (nvic_src_t src, excep_priority_t priority);

/*
 * Devuelve una prioridad de interrupción
 * @param src	Fuente de la interrupción
 * @return Tipo de prioridad
 */
nvic_priority_t nvic_get_priority (nvic_src_t src);

/*
 * Habilita una interrupción
 * @param src	Fuente de la interrupción
 */
void nvic_enable_interrupt (nvic_src_t src);

/*
 * Deshabilita una interrupción
 * @param src	Fuente de la interrupción
 */
void nvic_disable_interrupt (nvic_src_t src);

/*
 * Fuerza una interrupción
 * @param src	Fuente de la interrupción
 */
void nvic_force_interrupt (nvic_src_t src);

/*
 * Deja de forzar una interrupción
 * @param src	Fuente de la interrupción
 */
void nvic_unforce_interrupt (nvic_src_t src);


#endif  // _NVIC_H_
