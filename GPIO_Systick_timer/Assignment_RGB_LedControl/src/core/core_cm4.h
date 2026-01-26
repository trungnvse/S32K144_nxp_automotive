#ifndef CORE_CORE_CM4_H_
#define CORE_CORE_CM4_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include <stdint.h>
/*******************************************************************************
* Code
*******************************************************************************/
/*SYSTICK*/
typedef struct
{
	volatile uint32_t CTRL;                              /*Offset: 0x000 (R/W)  SysTick Control and Status Register*/
	volatile uint32_t LOAD;                              /*Offset: 0x004 (R/W)  SysTick Reload Value Register*/
	volatile uint32_t VAL;                               /*Offset: 0x008 (R/W)  SysTick Current Value Register*/
	volatile uint32_t CALIB;                             /*Offset: 0x00C (R/ )  SysTick Calibration Register*/
} SysTick_Type;
#define SYSTICK_BASE    (0xE000E010UL)
#define SYSTICK         ((SysTick_Type *) SYSTICK_BASE)

/*SCB*/
typedef struct {
       uint8_t RESERVED_0[8];
    volatile uint32_t ACTLR;                             /*Offset: 0x8 */
       uint8_t RESERVED_1[3316];
    volatile uint32_t CPUID;                             /*Offset: 0xD00 */
    volatile uint32_t ICSR;                              /*Offset: 0xD04 */
    volatile uint32_t VTOR;                              /*Offset: 0xD08 */
    volatile uint32_t AIRCR;                             /*Offset: 0xD0C */
    volatile uint32_t SCR;                               /*Offset: 0xD10 */
    volatile uint32_t CCR;                               /*Offset: 0xD14 */
    volatile uint32_t SHPR1;                             /*Offset: 0xD18 */
    volatile uint32_t SHPR2;                             /*Offset: 0xD1C */
    volatile uint32_t SHPR3;                             /*Offset: 0xD20 */
    volatile uint32_t SHCSR;                             /*Offset: 0xD24 */
    volatile uint32_t CFSR;                              /*Offset: 0xD28 */
    volatile uint32_t HFSR;                              /*Offset: 0xD2C */
    volatile uint32_t DFSR;                              /*Offset: 0xD30 */
    volatile uint32_t MMFAR;                             /*Offset: 0xD34 */
    volatile uint32_t BFAR;                              /*Offset: 0xD38 */
    volatile uint32_t AFSR;                              /*Offset: 0xD3C */
       uint8_t RESERVED_2[72];
    volatile uint32_t CPACR;                             /*Offset: 0xD88 */
       uint8_t RESERVED_3[424];
    volatile uint32_t FPCCR;                             /*Offset: 0xF34 */
    volatile uint32_t FPCAR;                             /*Offset: 0xF38 */
    volatile uint32_t FPDSCR;                            /*Offset: 0xF3C */
} SCB_Type;
#define SCB_BASE    (0xE000E000UL)
#define SCB         ((SCB_Type *)SCB_BASE)

#define SCB_SHPR3_PRI_15_MASK   (0xFF000000U)
#define SCB_SHPR3_PRI_15_SHIFT  (24U)
#define SCB_SHPR3_PRI_15(x)     (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_15_SHIFT))&SCB_SHPR3_PRI_15_MASK)

/*NVIC*/
typedef struct
{
	volatile uint32_t ISER[8U];                          /*Offset: 0x000 (R/W)  Interrupt Set Enable Register*/
    	uint32_t RESERVED0[24U];
    volatile uint32_t ICER[8U];                          /*Offset: 0x080 (R/W)  Interrupt Clear Enable Register*/
    	uint32_t RESERVED1[24U];
    volatile uint32_t ISPR[8U];                          /*Offset: 0x100 (R/W)  Interrupt Set Pending Register*/
        uint32_t RESERVED2[24U];
    volatile uint32_t ICPR[8U];                          /*Offset: 0x180 (R/W)  Interrupt Clear Pending Register*/
        uint32_t RESERVED3[24U];
    volatile uint32_t IABR[8U];                          /*Offset: 0x200 (RO)  Interrupt Active Bit Register*/
        uint32_t RESERVED4[56U];
    volatile uint32_t IPR[60U];                          /*Offset: 0x300 (R/W)  Interrupt Priority Register */
} NVIC_Type;
#define NVIC_BASE       (0xE000E100UL)
#define NVIC            ((NVIC_Type *) NVIC_BASE)


/**
  * @brief                   Configuration Systick timer
  * uint32_t ticks           tick to count
  * @return value            None
  */
static inline uint8_t SYSTICK_Config(uint32_t ticks)
{
	uint8_t reval = 0;

	if ((ticks - 1UL) > 0xFFFFFFUL)
	{
		reval = -1;
	} else{
		/* set reload register */
		SYSTICK->LOAD  = (uint32_t)(ticks - 1UL);
		/*set priority for System tick = 1*/
		SCB->SHPR3 = (SCB->SHPR3 & ~SCB_SHPR3_PRI_15_MASK)
		| SCB_SHPR3_PRI_15((1 << (4)) & 0xFFu);
		/* Load the SysTick Counter Value */
		SYSTICK->VAL   = 0UL;
		/*0b111 - Use processor clock - bit 2, use interrupt - bit 1, enable clock - bit 0*/
		SYSTICK->CTRL  = 7U;

		reval = 0;
	}

	return reval;
}

#endif /* CORE_CORE_CM4_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
