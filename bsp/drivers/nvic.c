#include "nvic.h"

extern volatile nvic_handler_t _interrupt_handlers[nvic_src_max];

typedef struct
{
    uint32_t ISER[8];               // Interrupt set-enable register x
    uint8_t reserved_0[0x60];       // Bytes de relleno
    uint32_t ICER[8];               // Interrupt clear-enable register x
    uint8_t reserved_1[0x60];       // Bytes de relleno
    uint32_t ISPR[8];               // Interrupt set-pending register x
    uint8_t reserved_2[0x60];       // Bytes de relleno
    uint32_t ICPR[8];               // Interrupt clear-pending register x
    uint8_t reserved_3[0x60];       // Bytes de relleno
    uint32_t IABR[8];               // Interrupt active bit register x
    uint8_t reserved_4[0xE0];       // Bytes de relleno
    uint8_t IPR[240];               // Interrupt priority register x
    uint8_t reserved_5[0xA10];      // Bytes de relleno
    uint32_t STIR;                  // Software trigger interrupt register
} nvic_regs_t;

static volatile nvic_regs_t* const nvic_regs = NVIC_BASE;

void
nvic_set_handler (nvic_src_t src, nvic_handler_t handler)
{
    _interrupt_handlers[src] = handler;
}

nvic_handler_t
nvic_get_handler(nvic_src_t src)
{
    return _interrupt_handlers[src];
}

void
nvic_set_priority(nvic_src_t src, excep_priority_t priority)
{
    nvic_regs->IPR[src] = priority;
}


nvic_priority_t
nvic_get_priority(nvic_src_t src)
{
    return nvic_regs->IPR[src];
}

void nvic_enable_interrupt(nvic_src_t src)
{
    nvic_regs->ISER[src / 32] = 1 << (src % 32);
}

void nvic_disable_interrupt(nvic_src_t src)
{
    nvic_regs->ICER[src / 32] = 1 << (src % 32);
}

void nvic_force_interrupt(nvic_src_t src)
{
    nvic_regs->ISPR[src / 32] = 1 << (src % 32);
}

void nvic_unforce_interrupt(nvic_src_t src)
{
    nvic_regs->ICPR[src / 32] = 1 << (src % 32);
}
