#ifndef BOARD_I2C_CONFIG_H_
#define BOARD_I2C_CONFIG_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
#include "I2c.h"
#include "core_cm4.h"
#include "pin_config.h"
#include "Lpit_config.h"
#include "general_config.h"
/*******************************************************************************
* Define
*******************************************************************************/
#define SDA_I2C 2
#define SCL_I2C 3

typedef struct {
    uint16_t adc_value;
    uint16_t times;
} i2c_buffer_t;

/**
  * @brief                   Initialize I2C module
  * @return value            None
  */
void BOARD_InitI2c();

/**
  * @brief                   change channel of ADC
  * @return value            None
  */
static inline void change_adc()
{
	static uint8_t adc_channel = 1;
	adc_channel %= 2;
	__asm volatile ("cpsid i");
    IP_LPI2C0->STDR = adc_channel;
    __asm volatile ("cpsie i");
    adc_channel++;
    flat_change = 0;
}

#endif /* BOARD_I2C_CONFIG_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
