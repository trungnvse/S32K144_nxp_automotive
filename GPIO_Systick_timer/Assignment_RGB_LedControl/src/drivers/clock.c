/*******************************************************************************
* Include
*******************************************************************************/
#include "clock.h"
/*******************************************************************************
* Code
*******************************************************************************/
void CLOCK_InitFIRC(const clock_config_t* firc_config)
{
	SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(firc_config->div2);
	SCG->FIRCCFG = SCG_FIRCCFG_RANGE(firc_config->range);
	/*default enable -> don't need enable anymore*/
}

void CLOCK_InitSIRC(const clock_config_t* sirc_config)
{
	SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV2(sirc_config->div2);
	SCG->SIRCCFG = SCG_SIRCCFG_RANGE(sirc_config->range);
	/*default enable -> don't need enable anymore*/
}
/*******************************************************************************
* EOF
*******************************************************************************/
