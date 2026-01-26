#ifndef BOARD_PIN_CONFIG_H_
#define BOARD_PIN_CONFIG_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "s32k144.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
/*******************************************************************************
* Define
*******************************************************************************/
#define RED_LED    15
#define BLUE_LED   0
#define GREEN_LED  16

typedef enum
{
    OFF = 1U,
    ON = 0U,
} status_led;

/**
  * @brief                   Initialize Pin
  * @return value            None
  */
void BOARD_InitPins();

/**
  * @brief                   register handler from other layer
  * status_led status        status of led_pin
  * uint8_t pin              number of pin
  * @return value            None
  */
void BOARD_WritePin(status_led status, uint8_t pin);

#endif /* BOARD_PIN_CONFIG_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
