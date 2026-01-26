#ifndef DRIVERS_LPIT_H_
#define DRIVERS_LPIT_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include <stdint.h>
#include "S32K144.h"
/*******************************************************************************
* Define
*******************************************************************************/
#define LPIT_CLOCK_HZ       (48000000U)

typedef struct{
	uint8_t  channel;
	uint8_t  interrupt; /*1- enable 0 - 0 - disable*/
	uint32_t val_counter;
} Lpit_config_t;

static inline void LPIT0_Config(Lpit_config_t* config, uint8_t numberof_lpit)
{
	if(numberof_lpit == 1)
	{
		/*Reset timer*/
		IP_LPIT0->MCR |= LPIT_MCR_SW_RST_MASK;
		IP_LPIT0->MCR &= ~LPIT_MCR_SW_RST_MASK;

	    /*  Enable Module Clock (IP_LPIT0) */
	    IP_LPIT0->MCR = LPIT_MCR_M_CEN_MASK;

		/*Setup timer not in debug and doze mode and enable clock module*/
		IP_LPIT0->MCR |= LPIT_MCR_DBG_EN(1);
		IP_LPIT0->MCR |= LPIT_MCR_DOZE_EN(1);
	}
	/*Setup timer counter in 32-bit periodic counter*/
	IP_LPIT0->TMR[config->channel].TCTRL |= LPIT_TMR_TCTRL_MODE(0);

    /*  Configure Channel */
    IP_LPIT0->TMR[config->channel].TVAL = (config->val_counter) - 1;

    /*  Enable Channel Interrupt */
    if(config->interrupt){
        switch (config->channel){
        	case 0:
        		IP_LPIT0->MIER |= LPIT_MIER_TIE0_MASK;
        		break;
        	case 1:
        		IP_LPIT0->MIER |= LPIT_MIER_TIE1_MASK;
        		break;
        	case 2:
        		IP_LPIT0->MIER |= LPIT_MIER_TIE2_MASK;
        		break;
        	case 3:
        		IP_LPIT0->MIER |= LPIT_MIER_TIE3_MASK;
        		break;
        }
    }
    /*  Start Channel 0 */
	/*Enable timer*/
    switch (config->channel){
    	case 0:
    		IP_LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_0_MASK;
    		break;
    	case 1:
    		IP_LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_1_MASK;
    		break;
    	case 2:
    		IP_LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_2_MASK;
    		break;
    	case 3:
    		IP_LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_3_MASK;
    		break;
    }
}

static inline uint8_t LPIT0_Ch0_InterruptFlag()
{
	uint8_t reval = 0;

	if(IP_LPIT0->MSR & LPIT_MSR_TIF0_MASK)
	{
		reval = 1;
	}

	/*clear flag by w1c*/
	IP_LPIT0->MSR = LPIT_MSR_TIF0_MASK;

	return reval;
}

static inline uint8_t LPIT0_Ch1_InterruptFlag()
{
	uint8_t reval = 0;

	if(IP_LPIT0->MSR & LPIT_MSR_TIF1_MASK)
	{
		reval = 1;
	}

	/*clear flag by w1c*/
	IP_LPIT0->MSR = LPIT_MSR_TIF1_MASK;

	return reval;
}
#endif /* DRIVERS_LPIT_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
