/*******************************************************************************
* Include
*******************************************************************************/
#include "clock.h"
/*******************************************************************************
* Define
*******************************************************************************/
void CLOCK_InitFIRC(const clock_config_t* firc_config)
{
	IP_SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(firc_config->div2);
	IP_SCG->FIRCCFG = SCG_FIRCCFG_RANGE(firc_config->range);
	/*default enable -> don't need enable anymore*/
}

void CLOCK_InitSIRC(const clock_config_t* sirc_config)
{
	IP_SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV2(sirc_config->div2);
	IP_SCG->SIRCCFG = SCG_SIRCCFG_RANGE(sirc_config->range);
	/*default enable -> don't need enable anymore*/
}
/*******************************************************************************
* EOF
*******************************************************************************/

