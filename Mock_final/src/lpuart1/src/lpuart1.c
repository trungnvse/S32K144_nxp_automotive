/*******************************************************************************
* Includes
*******************************************************************************/
#include "lpuart1.h"
/*******************************************************************************
* Define
*******************************************************************************/
/* Maximum IRQ number for vector table size calculation */
#define FEATURE_INTERRUPT_IRQ_MAX (FTM3_Ovf_Reload_IRQn)

/* External vector table in RAM (for interrupt handler registration) */
extern uint32_t __VECTOR_RAM[((uint32_t)(FEATURE_INTERRUPT_IRQ_MAX)) + 16U + 1U];

/*******************************************************************************
* Global Variables
*******************************************************************************/
/* Temporary storage for received character from UART */
volatile char g_temp;

/* Callback function pointer for handling received data */
volatile callback g_callback_func;

/*******************************************************************************
* Prototype
*******************************************************************************/

/**
 * @brief              Calculate OSR and SBR values for desired baud rate
 * uint32_t clock      clock UART module clock frequency in Hz
 * uint32_t baud       baud Desired baud rate (e.g., 9600, 115200)
 * uint16_t *OSR       OSR Pointer to store calculated Over Sampling Ratio (4-32)
 * uint16_t *SBR       SBR Pointer to store calculated Baud Rate Modulo Divisor (1-8191)
 * return              none
 */
static void cacul_baudrate(uint32_t clock, uint32_t baud, uint16_t *OSR, uint16_t *SBR);

/**
 * @brief                Enable NVIC interrupt for specified IRQ number
 * IRQn_Type irqNumber   irqNumber IRQ number to enable
 */
static void enable_irq(IRQn_Type irqNumber);

/**
 * @brief LPUART1 Receive/Transmit Interrupt Service Routine
 */
void LPUART1_RxTx_IRQHandler(void);

/*******************************************************************************
* Code
*******************************************************************************/
void init_uart(const uint32_t _baud_rate)
{
    uint16_t OSR = 0;
    uint16_t SBR = 0;

    /* Enable clock for Port C */
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1);

    /* Configure PTC6 as LPUART1 RX (Alternative 2) */
    PORTC->PCR[6] |= PORT_PCR_MUX(2);

    /* Configure PTC7 as LPUART1 TX (Alternative 2) */
    PORTC->PCR[7] |= PORT_PCR_MUX(2);

    /* Disable LPUART1 clock before changing source */
    PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;

    /* Select FIRC as clock source (Option 3) */
    PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(3);
    /* Enable LPUART1 clock */
    PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_CGC_MASK;

    /* Set FIRCDIV2 divider to 1*/
    SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1);

    LPUART1->CTRL &= ~LPUART_CTRL_RE_MASK;
    LPUART1->CTRL &= ~LPUART_CTRL_TE_MASK;

    /* Select 8-bit data mode */
    LPUART1->BAUD &= ~LPUART_BAUD_M10_MASK;   /* Clear M10 bit */
    LPUART1->CTRL &= ~LPUART_CTRL_M7_MASK;    /* Clear M7 bit */
    LPUART1->CTRL &= ~LPUART_CTRL_M_MASK;     /* Clear M bit */

    /* Disable parity */
    LPUART1->CTRL &= ~LPUART_CTRL_PE_MASK;

    /* LSB transmitted first */
    LPUART1->STAT &= ~LPUART_STAT_MSBF_MASK;

    /* Receive data not inverted */
    LPUART1->STAT &= ~LPUART_STAT_RXINV_MASK;

    /* Transmit data not inverted */
    LPUART1->CTRL &= ~LPUART_CTRL_TXINV_MASK;

    /* Select 1 stop bit */
    LPUART1->BAUD &= ~LPUART_BAUD_SBNS_MASK;

    /* FIRC clock = 48 MHz */
    cacul_baudrate(48000000, _baud_rate, &OSR, &SBR);
    LPUART1->BAUD &= ~LPUART_BAUD_OSR_MASK;
    LPUART1->BAUD |= LPUART_BAUD_OSR(31);
    LPUART1->BAUD &= ~LPUART_BAUD_SBR_MASK;
    LPUART1->BAUD |= LPUART_BAUD_SBR(156);

    /* Enable receiver, transmitter */
    LPUART1->CTRL |= LPUART_CTRL_RE(1);
    LPUART1->CTRL |= LPUART_CTRL_TE(1);

    LPUART1->CTRL |= LPUART_CTRL_RIE(1);

    enable_irq(LPUART1_RxTx_IRQn);

    /* Register interrupt handler in RAM vector table */
    uint32_t * pVectorRam = (uint32_t *)__VECTOR_RAM;
    pVectorRam[((int32_t)LPUART1_RxTx_IRQn) + 16] = (uint32_t)(&LPUART1_RxTx_IRQHandler);
}

void LPUART1_send_character(char character)
{
    while((LPUART1->STAT & LPUART_STAT_TDRE_MASK) >> LPUART_STAT_TDRE_SHIFT == 0);
    LPUART1->DATA = character;
}

void LPUART1_send_string(const char *data_string)
{
    uint32_t i = 0;

    while (data_string[i] != '\0') {
        LPUART1_send_character(data_string[i]);
        i++;
    }
}

void LPUART1_send_string_v2(char *data_string, uint16_t length)
{
    int index = 0;

    for(index = 0; index < length; index++)
    {
        LPUART1_send_character(data_string[index]);
    }
}

void LPUART1_print_number(uint32_t value)
{
    char buf[10];
    int i = 0;

    if (value == 0) {
        LPUART1_send_character('0');
        return;
    }

    while (value > 0) {
        buf[i++] = (value % 10) + '0';
        value /= 10;
    }

    while (i--) {
        LPUART1_send_character(buf[i]);
    }
}

void register_take_data_from_uart(callback _callback_func)
{
    if(_callback_func != NULL)
    {
        g_callback_func = _callback_func;
    }
}

/*******************************************************************************
* Static Functions
*******************************************************************************/
static void cacul_baudrate(uint32_t clock, uint32_t baud, uint16_t *OSR, uint16_t *SBR)
{
    uint32_t best_err = UINT32_MAX;
    uint32_t best_osr = 0;
    uint32_t best_sbr = 0;
    uint32_t osr      = 0;
    uint64_t denom    = 0;
    uint32_t sbr      = 0;
    uint32_t actual   = 0;
    uint32_t err      = 0;
    uint32_t osr_reg  = 0;

    for (osr_reg = 31; osr_reg >= 4; osr_reg--)
    {
        osr   = osr_reg + 1;
        denom = (uint64_t)baud * osr;
        sbr   = clock / denom;

        if (sbr == 0 || sbr > 0x1FFF) continue;

        for (uint32_t s = sbr; s <= sbr + 1; s++)
        {
            actual = clock / (s * osr);
            err = (baud > actual) ? (baud - actual) : (actual - baud);

            if (err < best_err)
            {
                best_err = err;
                best_osr = osr_reg;
                best_sbr = s;
            }
        }
    }

    *OSR = best_osr;
    *SBR = best_sbr;
}

static void enable_irq(IRQn_Type irqNumber)
{
    S32_NVIC->ISER[(uint32_t)(irqNumber) >> 5U] =
        (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));
}

void LPUART1_RxTx_IRQHandler(void)
{
    g_temp = LPUART1->DATA;

    if(g_temp != '\0')
    {
        g_callback_func(g_temp);
    }
}

/*******************************************************************************
* EOF
*******************************************************************************/
