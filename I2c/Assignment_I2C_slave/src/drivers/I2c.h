#ifndef DRIVERS_I2C_H_
#define DRIVERS_I2C_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include <stdint.h>
#include "S32K144.h"
/*******************************************************************************
* Define
*******************************************************************************/
typedef struct{
	uint32_t address;
	uint8_t  interrupt; /*1- enable 0 - 0 - disable*/
} I2c_slave_config_t;

static inline void I2C_Config_slave(I2c_slave_config_t* config)
{
    /*  Reset LPI2C0 (IP_LPI2C0) */
    IP_LPI2C0->MCR = LPI2C_MCR_RST_MASK;
    IP_LPI2C0->MCR = 0x00000000;

    /*  Configure Slave Address */
    IP_LPI2C0->SAMR = LPI2C_SAMR_ADDR0(config->address);

    /*  Interrupt Enables */
    if(config->interrupt)
    	IP_LPI2C0->SIER = LPI2C_SIER_RDIE_MASK | LPI2C_SIER_SDIE_MASK;

    /*  Enable Slave Mode */
    IP_LPI2C0->SCR = LPI2C_SCR_SEN_MASK;

}
#endif /* DRIVERS_I2C_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
