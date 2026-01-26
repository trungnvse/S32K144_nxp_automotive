#ifndef DRIVERS_PORT_H_
#define DRIVERS_PORT_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"
/*******************************************************************************
* Define
*******************************************************************************/
typedef struct
{
    uint16_t mux;
    uint16_t pullSelect;
    uint8_t  pullenable;
} port_config_t;

/**
  * @brief               Configuration PORT
  * PORT_Type* base      PORT instant
  * uint8_t pin          pin
  * port_config_t*       specific configuration of PORT
  * @return value        None
  */
static inline void PORT_Config(PORT_Type* base, uint8_t pin, port_config_t* config)
{
	/*configuration port to Alternate function*/
	uint32_t pcr_value = 0;
	pcr_value = PORT_PCR_MUX(config->mux);

	if(config->pullenable)
	{
		pcr_value |= PORT_PCR_PE(1);
		if(config->pullSelect)
			pcr_value |= PORT_PCR_PS(1);
	}

	base->PCR[pin] = pcr_value;
}

#endif /* DRIVERS_PORT_H_ */
/*******************************************************************************
* Include
*******************************************************************************/
