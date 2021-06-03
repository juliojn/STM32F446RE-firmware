#include "system.h"

extern volatile excep_handler_t _excep_handlers[excep_max];

typedef struct
{
    uint32_t ACTLR;             // Auxiliary Control Register
    uint8_t  reserved[0xCF4];   // Bytes de relleno
    uint32_t CPUID;             // CPUID Base Register
    uint32_t ICSR;              // Interrupt Control and State Register
    uint32_t VTOR;              // Vector Table Offset Register
    uint32_t AIRC;              // Application Interrupt and Reset Control
                                // Register
    uint32_t SCR;               // System Control Register
    uint32_t CCR;               // Configuration and Control Register
    uint8_t  SHPR[12];          // System Handler Priority Registers
    uint32_t SHCSR;             // System Handler Control and State Register

    union
    {
        uint32_t CFSR;          // Configurable Fault Status Register
        struct
        {
            uint8_t  MMFSR;     // MemManage Fault Status Register
            uint8_t  BFSR;      // BusFault Status Register
            uint16_t UFSR;      // UsageFault Status Register
        };
    };

    uint32_t HFSR;              // HardFault Status Register
    uint32_t MMFAR;             // MemManage Fault Address Register
    uint32_t BFAR;              // BusFault Address Register
    uint32_t AFSR;              // Auxiliary Fault Status Register
} scb_t;

static volatile scb_t* const scb = SCB_BASE;

inline uint32_t
excep_disable_faultmask ()
{
    uint32_t faultmask;

    asm volatile(
        "mrs    %[faultmask],  FAULTMASK    \n\t"
        "CPSID  f                               "
        : [faultmask]   "=r" (faultmask)
    );

    return faultmask;
}


inline void
excep_enable_faultmask (uint32_t faultmask)
{
    asm volatile(
        "msr    FAULTMASK,  %[faultmask]        "
        :
        : [faultmask]   "r" (faultmask)
    );
}

inline uint32_t
excep_disable_primask ()
{
    uint32_t primask;

    asm volatile(
        "mrs    %[primask],  PRIMASK        \n\t"
        "CPSID  i                               "
        : [primask]   "=r" (primask)
    );

    return primask;
}

inline void
excep_enable_primask (uint32_t primask)
{
    asm volatile(
        "msr    PRIMASK,  %[primask]        "
        :
        : [primask]   "r" (primask)
    );
}

inline void
excep_set_handler (excep_t excep, excep_handler_t handler)
{
    _excep_handlers[excep] = handler;
}

inline excep_handler_t
excep_get_handler (excep_t excep)
{
    return _excep_handlers[excep];
}

void
excep_set_priority(excep_t excep, excep_priority_t priority)
{
    scb->SHPR[excep - 2] = priority;
}


excep_priority_t
excep_get_priority(excep_t excep)
{
    return scb->SHPR[excep - 2];
}
