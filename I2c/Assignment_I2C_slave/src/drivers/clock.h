#ifndef DRIVERS_CLOCK_H_
#define DRIVERS_CLOCK_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"
/*******************************************************************************
* Define
*******************************************************************************/
static inline void CLOCK_EnableClock(uint8_t port)
{
	IP_PCC->PCCn[port] |= PCC_PCCn_CGC(1);
}

static inline void CLOCK_ChooseSourse(uint8_t port, uint8_t source)
{
	IP_PCC->PCCn[port] &= ~PCC_PCCn_CGC(1);
	IP_PCC->PCCn[port] |= PCC_PCCn_PCS(source);
}

typedef enum
{
    CLK_DISABLE   = 0U,
    CLK_DIV_BY_1  = 1U,
	CLK_DIV_BY_2  = 2U,
	CLK_DIV_BY_4  = 3U,
	CLK_DIV_BY_8  = 4U,
	CLK_DIV_BY_16 = 5U,
	CLK_DIV_BY_32 = 6U,
	CLK_DIV_BY_64 = 7U
} CLK_DIV;

typedef struct
{
    CLK_DIV  div2;
    uint16_t range;
} clock_config_t;

/**
  * @brief                             Initialize clock FIRC
  * const clock_config_t* firc_config  specification configuration of FIRC
  * @return value            None
  */
void CLOCK_InitFIRC(const clock_config_t* firc_config);

/**
  * @brief                             Initialize clock SIRC
  * const clock_config_t* firc_config  specification configuration of SIRC
  * @return value            None
  */
void CLOCK_InitSIRC(const clock_config_t* sirc_config);


#endif /* DRIVERS_CLOCK_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
