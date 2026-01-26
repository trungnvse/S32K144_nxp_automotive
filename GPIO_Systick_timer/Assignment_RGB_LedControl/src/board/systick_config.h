#ifndef BOARD_SYSTICK_CONFIG_H_
#define BOARD_SYSTICK_CONFIG_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "stdio.h"
#include <stdint.h>
/*******************************************************************************
* Define
*******************************************************************************/
typedef void (*callback)(uint8_t _argument);

/**
  * @brief                   register handler from other layer
  * callback _callback_func  function callback from other layer
  * @return value            None
  */
void Systick_regis_handler(callback _callback_func);

#endif /* BOARD_SYSTICK_CONFIG_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
