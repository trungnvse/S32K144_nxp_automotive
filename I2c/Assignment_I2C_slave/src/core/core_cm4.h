#ifndef CORE_CORE_CM4_H_
#define CORE_CORE_CM4_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"
/*******************************************************************************
* Define
*******************************************************************************/
typedef struct {
  volatile uint32_t ISER[8U];               /* Interrupt Set Enable Register */
  uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /* Interrupt Clear Enable Register */
  uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];               /* Interrupt Set Pending Register */
  uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /* Interrupt Clear Pending Register */
  uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /* Interrupt Active bit Register */
  uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];               /* Interrupt Priority Register */
} S32_NVIC_Type;
#define S32_NVIC_BASE  0xE000E100u
#define S32_NVIC       ((S32_NVIC_Type *)S32_NVIC_BASE)

static inline void NVIC_EnableInterrupt(IRQn_Type number_irq, uint32_t priority)
{
	S32_NVIC->ICPR[number_irq / 32] |= (1U << (number_irq % 32));
    S32_NVIC->ISER[number_irq / 32] |= (1 << (number_irq % 32));
    S32_NVIC->IP[number_irq] = priority;
}



#endif /* CORE_CORE_CM4_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
