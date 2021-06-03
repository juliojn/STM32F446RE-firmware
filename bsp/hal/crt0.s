@
@ Fichero inicial para la inicialización del runtime de C
@

    .set EXCEPTIONS_DISABLED,     0x1

    .syntax	unified

	.section .startup
	.globl	_isr_vector
_isr_vector:
    .word _stack_top            /* Top of Stack */
    .word _Reset_handler            @ Reset

    .globl	_excep_handlers
    _excep_handlers:
    .word _NMI_handler              @ Non maskable interrupt, Clock Security System
    .word _HardFault_handler        @ All class of fault
    .word _MemManage_handler        @ Memory management
    .word _BusFault_handler         @ Pre-fetch fault, memory access fault
    .word _UsageFault_handler       @ Undefined instruction or illegal state
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word _SVCall_handler           @ System Service call via SWI instruction
    .word _DebugMonitor_handler     @ Debug Monitor
    .word 0                         @ Reserved
    .word _PendSV_handler           @ Pendable request for system service
    .word _Systick_handler          @ System tick timer

    .globl	_interrupt_handlers
    _interrupt_handlers:
    .word _WWDG_handler             @ Window Watchdog interrupt
    .word _PVD_handler              @ PVD through EXTI line detection interrupt
    .word _TAMP_STAMP_handler       @ Tamper and TimeStamp interrupts through the EXTI line
    .word _RTC_WKUP_handler         @ RTC Wakeup interrupt through the EXTI line
    .word _FLASH_handler            @ Flash global interrupt
    .word _RCC_handler              @ RCC global interrupt
    .word _EXTI0_handler            @ EXTI Line0 interrupt
    .word _EXTI1_handler            @ EXTI Line1 interrupt
    .word _EXTI2_handler            @ EXTI Line2 interrupt
    .word _EXTI3_handler            @ EXTI Line3 interrupt
    .word _EXTI4_handler            @ EXTI Line4 interrupt
    .word _DMA1_Stream0_handler     @ DMA1 Stream0 global interrupt
    .word _DMA1_Stream1_handler     @ DMA1 Stream1 global interrupt
    .word _DMA1_Stream2_handler     @ DMA1 Stream2 global interrupt
    .word _DMA1_Stream3_handler     @ DMA1 Stream3 global interrupt
    .word _DMA1_Stream4_handler     @ DMA1 Stream4 global interrupt
    .word _DMA1_Stream5_handler     @ DMA1 Stream5 global interrupt
    .word _DMA1_Stream6_handler     @ DMA1 Stream6 global interrupt
    .word _ADC_handler              @ ADC1, ADC2 and ADC3 global interrupts
    .word _CAN1_TX_handler          @ CAN1 TX interrupts
    .word _CAN1_RX0_handler         @ CAN1 RX0 interrupts
    .word _CAN1_RX1_handler         @ CAN1 RX1 interrupts
    .word _CAN1_SCE_handler         @ CAN1 SCE interrupt
    .word _EXTI9_5_handler          @ EXTI Line[9:5] interrupts
    .word _TIM1_BRK_TIM9_handler    @ TIM1 Break interrupt and TIM9 global interrupt
    .word _TIM1_UP_TIM10_handler    @ TIM1 Update interrupt and TIM10 global interrupt
    .word _TIM1_TRG_COM_TIM11_handler   @ TIM1 Trigger and Commutation interrupts
                                        @ and TIM11 global interrupt
    .word _TIM1_CC_handler          @ TIM1 Capture Compare interrupt
    .word _TIM2_handler             @ TIM2 global interrupt
    .word _TIM3_handler             @ TIM3 global interrupt
    .word _TIM4_handler             @ TIM4 global interrupt
    .word _I2C1_EV_handler          @ I2C1 event interrupt
    .word _I2C1_ER_handler          @ I2C1 error interrupt
    .word _I2C2_EV_handler          @ I2C2 event interrupt
    .word _I2C2_ER_handler          @ I2C2 error interrupt
    .word _SPI1_handler             @ SPI1 global interrupt
    .word _SPI2_handler             @ SPI2 global interrupt
    .word _USART1_handler           @ USART1 global interrupt
    .word _USART2_handler           @ USART2 global interrupt
    .word _USART3_handler           @ USART3 global interrupt
    .word _EXTI15_10_handler        @ EXTI Line[15:10] interrupts
    .word _RTC_Alarm_handler        @ RTC Alarms (A and B) through EXTI line interrupt
    .word _OTG_FS_WKUP_handler      @ USB On-The-Go FS Wakeup through EXTI line interrupt
    .word _TIM8_BRK_TIM12_handler   @ TIM8 Break interrupt and TIM12 global interrupt
    .word _TIM8_UP_TIM13_handler    @ TIM8 Update interrupt and TIM13 global interrupt
    .word _TIM8_TRG_COM_TIM14_handler   @ TIM8 Trigger and Commutation interrupts
                                        @ and TIM14 global interrupt
    .word _TIM8_CC_handler          @ TIM8 Capture Compare interrupt
    .word _DMA1_Stream7_handler     @ DMA1 Stream7 global interrupt
    .word _FMC_handler              @ FMC global interrupt
    .word _SDIO_handler             @ SDIO global interrupt
    .word _TIM5_handler             @ TIM5 global interrupt
    .word _SPI3_handler             @ SPI3 global interrupt
    .word _UART4_handler            @ UART4 global interrupt
    .word _UART5_handler            @ UART5 global interrupt
    .word _TIM6_DAC_handler         @ TIM6 global interrupt,DAC1 and DAC2 underrun error interrupts
    .word _TIM7_handler             @ TIM7 global interrupt
    .word _DMA2_Stream0_handler     @ DMA2 Stream0 global interrupt
    .word _DMA2_Stream1_handler     @ DMA2 Stream1 global interrupt
    .word _DMA2_Stream2_handler     @ DMA2 Stream2 global interrupt
    .word _DMA2_Stream3_handler     @ DMA2 Stream3 global interrupt
    .word _DMA2_Stream4_handler     @ DMA2 Stream4 global interrupt
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word _CAN2_TX_handler          @ CAN2 TX interrupts
    .word _CAN2_RX0_handler         @ CAN2 RX0 interrupts
    .word _CAN2_RX1_handler         @ CAN2 RX1 interrupt
    .word _CAN2_SCE_handler         @ CAN2 SCE interrupt
    .word _OTG_FS_handler           @ USB On The Go FS global interrupt
    .word _DMA2_Stream5_handler     @ DMA2 Stream5 global interrupt
    .word _DMA2_Stream6_handler     @ DMA2 Stream6 global interrupt
    .word _DMA2_Stream7_handler     @ DMA2 Stream7 global interrupt
    .word _USART6_handler           @ USART6 global interrupt
    .word _I2C3_EV_handler          @ I2C3 event interrupt
    .word _I2C3_ER_handler          @ I2C3 error interrupt
    .word _OTG_HS_EP1_OUT_handler   @ USB On The Go HS End Point 1 Out global interrupt
    .word _OTG_HS_EP1_IN_handler    @ USB On The Go HS End Point 1 In global interrupt
    .word _OTG_HS_WKUP_handler      @ USB On The Go HS Wakeup through EXTI interrupt
    .word _OTG_HS_handler           @ USB On The Go HS global interrupt
    .word _DCMI_handler             @ DCMI global interrupt
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word _FPU_handler              @ FPU global interrupt
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word _SPI4_handler             @ SPI 4 global interrupt
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word _SAI1_handler             @ SAI1 global interrupt
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word 0                         @ Reserved
    .word _SAI2_handler             @ SAI2 global interrupt
    .word _QuadSPI_handler          @ QuadSPI global interrupt
    .word _HDMI_CEC_handler         @ HDMI-CEC global interrupt
    .word _SPDIF_Rx_handler         @ SPDIF-Rx global interrupt
    .word _FMPI2C1_handler          @ FMPI2C1 event interrupt
    .word _FMPI2C1_error_handler    @ FMPI2C1 error interrupt

	.text
	.globl	_Reset_handler
	.type	_Reset_handler, %function
_Reset_handler:
	bl	_start

	.align	4
    .globl	_start
    .type	_start, %function
_start:
    @ Deshabilita las interrupciones
    ldr    r0, =EXCEPTIONS_DISABLED
    msr    FAULTMASK,  r0

    ldr	ip, =bsp_init
    blx	ip			@ Saltamos a la funcion


    ldr	ip, =main
    blx	ip
    bl  .


    .globl	default_Handler
    .type	default_Handler, %function
default_Handler:
	b	.

.macro	default_handler	handler_name
.weak	\handler_name
.set	\handler_name, default_Handler
.endm

default_handler _NMI_handler
default_handler _HardFault_handler
default_handler _MemManage_handler
default_handler _BusFault_handler
default_handler _UsageFault_handler
default_handler _SVCall_handler
default_handler _DebugMonitor_handler
default_handler _PendSV_handler
default_handler _Systick_handler
default_handler _WWDG_handler
default_handler _PVD_handler
default_handler _TAMP_STAMP_handler
default_handler _RTC_WKUP_handler
default_handler _FLASH_handler
default_handler _RCC_handler
default_handler _EXTI0_handler
default_handler _EXTI1_handler
default_handler _EXTI2_handler
default_handler _EXTI3_handler
default_handler _EXTI4_handler
default_handler _DMA1_Stream0_handler
default_handler _DMA1_Stream1_handler
default_handler _DMA1_Stream2_handler
default_handler _DMA1_Stream3_handler
default_handler _DMA1_Stream4_handler
default_handler _DMA1_Stream5_handler
default_handler _DMA1_Stream6_handler
default_handler _ADC_handler
default_handler _CAN1_TX_handler
default_handler _CAN1_RX0_handler
default_handler _CAN1_RX1_handler
default_handler _CAN1_SCE_handler
default_handler _EXTI9_5_handler
default_handler _TIM1_BRK_TIM9_handler
default_handler _TIM1_UP_TIM10_handler
default_handler _TIM1_TRG_COM_TIM11_handler
default_handler _TIM1_CC_handler
default_handler _TIM2_handler
default_handler _TIM3_handler
default_handler _TIM4_handler
default_handler _I2C1_EV_handler
default_handler _I2C1_ER_handler
default_handler _I2C2_EV_handler
default_handler _I2C2_ER_handler
default_handler _SPI1_handler
default_handler _SPI2_handler
default_handler _USART1_handler
default_handler _USART2_handler
default_handler _USART3_handler
default_handler _EXTI15_10_handler
default_handler _RTC_Alarm_handler
default_handler _OTG_FS_WKUP_handler
default_handler _TIM8_BRK_TIM12_handler
default_handler _TIM8_UP_TIM13_handler
default_handler _TIM8_TRG_COM_TIM14_handler
default_handler _TIM8_CC_handler
default_handler _DMA1_Stream7_handler
default_handler _FMC_handler
default_handler _SDIO_handler
default_handler _TIM5_handler
default_handler _SPI3_handler
default_handler _UART4_handler
default_handler _UART5_handler
default_handler _TIM6_DAC_handler
default_handler _TIM7_handler
default_handler _DMA2_Stream0_handler
default_handler _DMA2_Stream1_handler
default_handler _DMA2_Stream2_handler
default_handler _DMA2_Stream3_handler
default_handler _DMA2_Stream4_handler
default_handler _CAN2_TX_handler
default_handler _CAN2_RX0_handler
default_handler _CAN2_RX1_handler
default_handler _CAN2_SCE_handler
default_handler _OTG_FS_handler
default_handler _DMA2_Stream5_handler
default_handler _DMA2_Stream6_handler
default_handler _DMA2_Stream7_handler
default_handler _USART6_handler
default_handler _I2C3_EV_handler
default_handler _I2C3_ER_handler
default_handler _OTG_HS_EP1_OUT_handler
default_handler _OTG_HS_EP1_IN_handler
default_handler _OTG_HS_WKUP_handler
default_handler _OTG_HS_handler
default_handler _DCMI_handler
default_handler _FPU_handler
default_handler _SPI4_handler
default_handler _SAI1_handler
default_handler _SAI2_handler
default_handler _QuadSPI_handler
default_handler _HDMI_CEC_handler
default_handler _SPDIF_Rx_handler
default_handler _FMPI2C1_handler
default_handler _FMPI2C1_error_handler
