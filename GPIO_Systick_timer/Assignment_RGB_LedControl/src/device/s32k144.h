#ifndef DEVICE_S32K144_H_
#define DEVICE_S32K144_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include <stdint.h>
/*******************************************************************************
* Define
*******************************************************************************/
/*PCC*/
typedef struct {
	volatile uint32_t PCCx[116U];
} PCC_Type;
#define PCC_BASE     (0x40065000UL)
#define PCC          ((PCC_Type *) PCC_BASE)

#define PCC_CGC_MASK    (0x40000000U)
#define PCC_CGC_SHIFT   (30U)
#define PCC_PCCx_CGC(x) (((uint32_t)(((uint32_t)(x)) << PCC_CGC_SHIFT)) & PCC_CGC_MASK)

#define PCC_PORTD 76

/*PORT*/
typedef struct {
	volatile uint32_t PCR[32UL];                           /*Offset: 0x0*/
	volatile uint32_t GPCLR;                               /*Offset: 0x80 */
	volatile uint32_t GPCHR;                               /*Offset: 0x84 */
	volatile uint32_t GICLR;                               /*Offset: 0x88 */
	volatile uint32_t GICHR;                               /*Offset: 0x8C */
             uint8_t RESERVED_0[16];
    volatile uint32_t ISFR;                                /*Offset: 0xA0 */
             uint8_t RESERVED_1[28];
    volatile uint32_t DFER;                                /*Offset: 0xC0 */
    volatile uint32_t DFCR;                                /*Offset: 0xC4 */
    volatile uint32_t DFWR;                                /*Offset: 0xC8 */
} PORT_Type;
#define PORTA_BASE (0x40049000UL)
#define PORTA      ((PORT_Type *) PORTA_BASE)
#define PORTB_BASE (0x4004A000UL)
#define PORTB      ((PORT_Type *) PORTB_BASE)
#define PORTC_BASE (0x4004B000UL)
#define PORTC      ((PORT_Type *) PORTC_BASE)
#define PORTD_BASE (0x4004C000UL)
#define PORTD      ((PORT_Type *) PORTD_BASE)
#define PORTE_BASE (0x4004D000UL)
#define PORTE      ((PORT_Type *) PORTE_BASE)

#define PORT_PCR_MUX_MASK   (0x700U)
#define PORT_PCR_MUX_SHIFT  (8U)
#define PORT_PCR_MUX(x)     (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)

#define PORT_PCR_PE_MASK    (0x2U)
#define PORT_PCR_PE_SHIFT   (1U)
#define PORT_PCR_PE(x)      (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)

#define PORT_PCR_PS_MASK    (0x1U)
#define PORT_PCR_PS_SHIFT   (0U)
#define PORT_PCR_PS(x)      (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)



/*GPIO*/
typedef struct {
	volatile uint32_t PDOR;                                /*Offset: 0x0 */
	volatile uint32_t PSOR;                                /*Offset: 0x4 */
	volatile uint32_t PCOR;                                /*Offset: 0x8 */
	volatile uint32_t PTOR;                                /*Offset: 0xC */
	volatile uint32_t PDIR;                                /*Offset: 0x10 */
	volatile uint32_t PDDR;                                /*Offset: 0x14 */
	volatile uint32_t PIDR;                                /*Offset: 0x18 */
} GPIO_Type;
#define GPIOA_BASE (0x400FF000UL)
#define GPIOA      ((GPIO_Type *) GPIOA_BASE)
#define GPIOB_BASE (0x400FF040UL)
#define GPIOB      ((GPIO_Type *) GPIOB_BASE)
#define GPIOC_BASE (0x400FF080UL)
#define GPIOC      ((GPIO_Type *) GPIOC_BASE)
#define GPIOD_BASE (0x400FF0C0UL)
#define GPIOD      ((GPIO_Type *) GPIOD_BASE)
#define GPIOE_BASE (0x400FF100UL)
#define GPIOE      ((GPIO_Type *) GPIOE_BASE)


/*SGC*/
typedef struct {
	volatile  uint32_t VERID;
	volatile  uint32_t PARAM;
              uint8_t RESERVED_0[8];
    volatile  uint32_t CSR;
    volatile uint32_t RCCR;
    volatile uint32_t VCCR;
    volatile uint32_t HCCR;
    volatile uint32_t CLKOUTCNFG;
             uint8_t RESERVED_1[220];
    volatile uint32_t SOSCCSR;
    volatile uint32_t SOSCDIV;
    volatile uint32_t SOSCCFG;
             uint8_t RESERVED_2[244];
    volatile uint32_t SIRCCSR;
    volatile uint32_t SIRCDIV;
    volatile uint32_t SIRCCFG;
             uint8_t RESERVED_3[244];
    volatile uint32_t FIRCCSR;
    volatile uint32_t FIRCDIV;
    volatile uint32_t FIRCCFG;
             uint8_t RESERVED_4[756];
    volatile uint32_t SPLLCSR;
    volatile uint32_t SPLLDIV;
    volatile uint32_t SPLLCFG;
} SCG_Type;
#define SCG_BASE     (0x40064000u)
#define SCG          ((SCG_Type *)SCG_BASE)

#define SCG_SIRCCSR_SIRCEN_MASK      (0x1U)
#define SCG_SIRCCSR_SIRCEN_SHIFT     (0U)
#define SCG_SIRCCSR_SIRCEN(x)        (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCEN_SHIFT)) & SCG_SIRCCSR_SIRCEN_MASK)

#define SCG_SIRCDIV_SIRCDIV2_MASK    (0x700U)
#define SCG_SIRCDIV_SIRCDIV2_SHIFT   (8U)
#define SCG_SIRCDIV_SIRCDIV2(x)      (((uint32_t)(((uint32_t)(x)) << SCG_SIRCDIV_SIRCDIV2_SHIFT)) & SCG_SIRCDIV_SIRCDIV2_MASK)

#define SCG_SIRCCFG_RANGE_MASK       (0x1U)
#define SCG_SIRCCFG_RANGE_SHIFT      (0U)
#define SCG_SIRCCFG_RANGE(x)         (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCFG_RANGE_SHIFT)) & SCG_SIRCCFG_RANGE_MASK)

#define SCG_SIRCCSR_SIRCVLD_MASK     (0x1000000U)
#define SCG_SIRCCSR_SIRCVLD_SHIFT    (24U)
#define SCG_SIRCCSR_SIRCVLD(x)       (((uint32_t)(((uint32_t)(x)) << SCG_SIRCCSR_SIRCVLD_SHIFT)) & SCG_SIRCCSR_SIRCVLD_MASK)

#define SCG_FIRCCSR_FIRCEN_MASK      (0x1U)
#define SCG_FIRCCSR_FIRCEN_SHIFT     (0U)
#define SCG_FIRCCSR_FIRCEN(x)        (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCEN_SHIFT)) & SCG_FIRCCSR_FIRCEN_MASK)

#define SCG_FIRCDIV_FIRCDIV2_MASK    (0x700U)
#define SCG_FIRCDIV_FIRCDIV2_SHIFT   (8U)
#define SCG_FIRCDIV_FIRCDIV2(x)      (((uint32_t)(((uint32_t)(x)) << SCG_FIRCDIV_FIRCDIV2_SHIFT)) & SCG_FIRCDIV_FIRCDIV2_MASK)

#define SCG_FIRCCFG_RANGE_MASK       (0x3U)
#define SCG_FIRCCFG_RANGE_SHIFT      (0U)
#define SCG_FIRCCFG_RANGE(x)         (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCFG_RANGE_SHIFT)) & SCG_FIRCCFG_RANGE_MASK)

#define SCG_FIRCCSR_FIRCVLD_MASK     (0x1000000U)
#define SCG_FIRCCSR_FIRCVLD_SHIFT    (24U)
#define SCG_FIRCCSR_FIRCVLD(x)       (((uint32_t)(((uint32_t)(x)) << SCG_FIRCCSR_FIRCVLD_SHIFT)) & SCG_FIRCCSR_FIRCVLD_MASK)

#endif /* DEVICE_S32K144_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
