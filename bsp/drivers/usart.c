#include "usart.h"

typedef struct
{
    union
    {
        struct
        {
            uint32_t PE         : 1;    // Parity error
            uint32_t FE         : 1;    // Framing error
            uint32_t NF         : 1;    // Noise detected flag
            uint32_t ORE        : 1;    // Overrun error
            uint32_t IDLE       : 1;    // IDLE line detected
            uint32_t RXNE       : 1;    // Read data register not empty
            uint32_t TC         : 1;    // Transmission complete
            uint32_t TXE        : 1;    // Transmit data register empty
            uint32_t LBD        : 1;    // LIN break detection flag
            uint32_t CTS        : 1;    // CTSFLAG
        };
        uint32_t USART_SR;              // Status register
    };

    union
    {
        union
        {
            uint32_t TDR         : 8;   // Transmission data register
            uint32_t RDR         : 8;   // Reception data register

        };
        uint32_t USART_DR;              // Data register
    };

    union
    {
        struct
        {
            uint32_t DIV_Fraction       : 4;    // Fraction of USARTDIV
            uint32_t DIV_Mantissa       : 12;   // Mantissa of USARTDIV
        };
        uint32_t USART_BRR;             // Baud rate register
    };

    union
    {
        struct
        {
            uint32_t SBK        : 1;    // Send break
            uint32_t RWU        : 1;    // Receiver wake up
            uint32_t RE         : 1;    // Receiver enable
            uint32_t TE         : 1;    // Transmitter enable
            uint32_t IDLEIE     : 1;    // IDLE interrupt enable
            uint32_t RXNEIE     : 1;    // RXNE interrupt enable
            uint32_t TCIE       : 1;    // Transmission complete interrupt enable
            uint32_t TXEIE      : 1;    // TXE interrupt enable
            uint32_t PEIE       : 1;    // PE interrupt enable
            uint32_t PS         : 1;    // Parity selection
            uint32_t PCE        : 1;    // Parity control enable
            uint32_t WAKE       : 1;    // Wakeup method
            uint32_t M          : 1;    // Word length
            uint32_t UE         : 1;    // USART enable
            uint32_t            : 1;
            uint32_t OVER8      : 1;    // Oversampling mode
        };
        uint32_t USART_CR1;             // Control register 1
    };

    union
    {
        struct
        {
            uint32_t ADD        : 4;    // Address of the USART node (multiprocesor)
            uint32_t            : 1;
            uint32_t LBDL       : 1;    // lin break detection length
            uint32_t LBDIE      : 1;    // LIN break detection interrupt enable
            uint32_t            : 1;
            uint32_t LBCL       : 1;    // Last bit clock pulse
            uint32_t CPHA       : 1;    // Clock phase
            uint32_t CPOL       : 1;    // Clock parity
            uint32_t CLKEN      : 1;    // Clock enable
            uint32_t STOP       : 2;    // STOP bits
            uint32_t LINEN      : 1;    // LIN mode enable

        };
        uint32_t USART_CR2;             // Control register 2
    };

    union
    {
        struct
        {
            uint32_t EIE        : 1;    // Error interrupt enable
            uint32_t IREN       : 1;    // IrDA mode enable
            uint32_t IRLP       : 1;    // IrDA low-power
            uint32_t HDSEL      : 1;    // Half-duplex selection
            uint32_t NACK       : 1;    // Smartcard NACK enable
            uint32_t SCEN       : 1;    // Smartcard mode enable
            uint32_t DMAR       : 1;    // DMA enable receiver
            uint32_t DMAT       : 1;    // DMA enable transmitter
            uint32_t RTSE       : 1;    // RTS enable
            uint32_t CTSE       : 1;    // CTS enable
            uint32_t CTSIE      : 1;    // CTS interrupt enable
            uint32_t ONEBIT     : 1;    // One sample bit method enable
        };
        uint32_t USART_CR3;             // Control register 3
    };

    union
    {
        struct
        {
            uint32_t PSC        : 8;    // Prescaler value
            uint32_t GT         : 8;    // Guard time value
        };
        uint32_t USART_GTPR;            // Guard time and prescaler register
    };
} usart_regs_t;

static volatile usart_regs_t* const usart_regs[usart_max] =
    {USART1_BASE, USART2_BASE, USART3_BASE, UART4_BASE, UART5_BASE, USART6_BASE};

typedef struct
{
	gpio_pin_t tx,rx;
} usart_pins_t;

static const usart_pins_t usart_pins[usart_max] = {{PA9, PA10}, {PA2, PA3}, {PC10, PC5},
    {PA0, PA1}, {PC12, PD2}, {PC6, PC7}};

void
usart_bus_init ()
{
    // Registro de datos del APB1 peripheral clock enable register
    // para la apertura de los periféricos del bus APB1
    volatile uint32_t * rcc_apb1enr     = (uint32_t *) 0x40023840;
    uint32_t rcc_apb1enr_mask           = 0x001E0000;

    // Registro de datos del APB2 peripheral clock enable register
    // para la apertura de los periféricos del bus APB2
    volatile uint32_t * rcc_apb2enr     = (uint32_t *) 0x40023844;
    uint32_t rcc_apb2enr_mask           = 0x00000030;

    // Habilito la apertura de las interfaces USART_2, USART_3, UART_4 y UART_5
    *rcc_apb1enr |= rcc_apb1enr_mask;
    // Habilito la apertura de las interfaces USART_1 y USART_6
    *rcc_apb2enr |= rcc_apb2enr_mask;
}

void
usart_init (usart_id_t usart, uint32_t baudrate, const uint8_t * name)
{
    gpio_alternate_function_t   function;
    gpio_mode_t                 mode;
    gpio_output_type_t          output_type;
    gpio_speed_t                speed;
    gpio_pull_t                 pull;
    uint32_t usart_div, mantissa, fraction;

    if (usart < uart_4)
        function = AF7;
    else
        function = AF8;

    mode =          gpio_mode_alternate;
    output_type =   gpio_output_type_push_pull;
    speed =         gpio_speed_high;
    pull =          gpio_pull_up;

    gpio_set_function_pin(usart_pins[usart].tx, function);
    gpio_set_mode(usart_pins[usart].tx, mode);
    gpio_set_output_type(usart_pins[usart].tx, output_type);
    gpio_set_output_speed(usart_pins[usart].tx, speed);
    gpio_set_pull_up_pull_down(usart_pins[usart].tx, pull);

    gpio_set_function_pin(usart_pins[usart].rx, function);
    gpio_set_mode(usart_pins[usart].rx, mode);
    gpio_set_output_type(usart_pins[usart].rx, output_type);
    gpio_set_output_speed(usart_pins[usart].rx, speed);
    gpio_set_pull_up_pull_down(usart_pins[usart].rx, pull);

    usart_regs[usart]->M     = 0;    // Longitud de palabra de 8 bits
    usart_regs[usart]->STOP  = 0;    // 1 bit de parada
    usart_regs[usart]->OVER8 = 1;    // Sobremuestreo de 16

    usart_div   = HSI_FREQUENCY / baudrate;
    mantissa    = usart_div / (8 * (2 - usart_regs[usart]->OVER8));
    fraction    = usart_div % (8 * (2 - usart_regs[usart]->OVER8));

    usart_regs[usart]->DIV_Mantissa = mantissa;
    usart_regs[usart]->DIV_Fraction = fraction;
    usart_regs[usart]->LINEN    = 0;    // LIN mode disable
    usart_regs[usart]->CLKEN    = 0;    // Clock disable
    usart_regs[usart]->IREN     = 0;    // IrDA mode disable
    usart_regs[usart]->SCEN     = 0;    // Smartcard mode disable
    usart_regs[usart]->HDSEL    = 0;    // Half-duplex disable

    usart_regs[usart]->UE       = 1;    // USART enabled
    usart_regs[usart]->TE       = 1;    // Transmission enable
    usart_regs[usart]->RE       = 1;    // Reception enable


    // nvic_enable_interrupt(nvic_src_usart_2);
    // usart_regs[usart]->TXEIE = 1;
    // usart_regs[usart]->TCIE = 1;
    // usart_regs[usart]->CTSIE = 1;
    // usart_regs[usart]->IDLE = 1;
    // usart_regs[usart]->RXNEIE = 1;
    // usart_regs[usart]->PEIE = 1;
    // usart_regs[usart]->LBDIE = 1;
    // usart_regs[usart]->FE = 1;

    register_dev(name, usart, NULL, NULL, usart_receive, usart_send, NULL, NULL, NULL);
}

void
usart_send_byte (usart_id_t usart, uint8_t c)
{
    while (!usart_regs[usart]->TXE);
    usart_regs[usart]->TDR = c;
}


void
usart_send (usart_id_t usart, uint8_t * buf, uint32_t size)
{
    for (int i = 0; i < size; ++i)
        usart_send_byte(usart, buf[i]);
}


uint8_t
usart_receive_byte (usart_id_t usart)
{
    while (!usart_regs[usart]->RXNE);
    return usart_regs[usart]->RDR;
}

void
usart_receive (usart_id_t usart, uint8_t * buf, uint32_t size)
{
    for (int i = 0; i < size; ++i)
        buf[i] = usart_receive_byte(usart);
}
