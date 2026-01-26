#ifndef LPUART1_INC_LPUART1_H_
#define LPUART1_INC_LPUART1_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "S32K144.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/*******************************************************************************
* define
*******************************************************************************/
typedef void (*callback)(char _argument);

/**
  * @brief                   initialize module UART
  * uint32_t baun_rate[in]   baud rate of UART
  * @return value            None
  */
void init_uart(const uint32_t _baud_rate);

/**
  * @brief                   send character to other device through UART
  * char character           character will be sent
  * @return value            None
  */
void send_character(char character);

/**
  * @brief                   register callback function will be called
  * callback _callback_func  callback function will be called
  * @return value            None
  */
void register_take_data_from_uart(callback _callback_func);

/**
  * @brief                   send character to other device through UART
  * const char *data_string  pointer to string data
  * @return value            None
  */
void LPUART1_send_string(const char *data_string);

/**
  * @brief                   send character to other device through UART
  * uint32_t value           value of number
  * @return value            None
  */
void LPUART1_print_number(uint32_t value);

/**
  * @brief                   send character to other device through UART
  * char *data_string        pointer to string data
  * uint16_t length          length of string
  * @return value            None
  */
void LPUART1_send_string_v2(char *data_string, uint16_t length);

#endif /* LPUART1_INC_LPUART1_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
