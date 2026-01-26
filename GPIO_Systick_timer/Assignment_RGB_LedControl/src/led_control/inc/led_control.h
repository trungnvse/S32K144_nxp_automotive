#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "systick_config.h"
#include "clock_config.h"
#include "pin_config.h"
#include "core_cm4.h"

/*******************************************************************************
* API
*******************************************************************************/
/**
  * @brief                   Initialize System tick and led pin
  * @return value            0 if successfully, -1 if false
  */
uint8_t Led_control_init();

/**
  * @brief                   change status of led depend on counter
  * uint8_t _red             value of red led
  * uint8_t _green           value of red green
  * uint8_t _blue            value of red blue
  * @return value            None
  */
void Led_control_run(uint8_t _red, uint8_t _green, uint8_t _blue);
#endif /* LED_CONTROL_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
