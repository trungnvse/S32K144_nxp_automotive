#ifndef BOARD_LPIT_CONFIG_H_
#define BOARD_LPIT_CONFIG_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
#include "Lpit.h"
#include "core_cm4.h"
#include "pin_config.h"
#include "general_config.h"
/*******************************************************************************
* Define
*******************************************************************************/
#define LPIT_CLOCK      (48000000U)

/**
  * @brief                   Initialize LPIT module
  * @return value            None
  */
void BOARD_InitLpit();
#endif /* BOARD_LPIT_CONFIG_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
