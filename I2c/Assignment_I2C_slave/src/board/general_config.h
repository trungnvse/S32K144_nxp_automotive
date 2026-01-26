#ifndef BOARD_GENERAL_CONFIG_H_
#define BOARD_GENERAL_CONFIG_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "s32k144.h"
/*******************************************************************************
* Define
*******************************************************************************/
/*	we can test frequency of LPIT with FRE_MIN = 1 (1 second) FRE_MAX = 10 (10 second)
 *  and use TEST_EYES = 1
 *  in here, we can see frequency of blink led base on ADC value from master
 * */

#define TEST_EYES              0
#define TEST_LOGIC_ANALYZER    1

#define FRE_CHANGE_ADC         2 /*after 2 seconds, will be change name of ADC channel*/

#define ADC_MAX                (4096U)

#define FRE_MIN                (10000) /*blink led with frequency = 1s to check by eyes*/
#define FRE_MAX                (100000)/*blink led with frequency = 0.1s to check by eyes*/

/*use to check in while loop in main*/
uint8_t extern flat_change;

#endif /* BOARD_GENERAL_CONFIG_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
