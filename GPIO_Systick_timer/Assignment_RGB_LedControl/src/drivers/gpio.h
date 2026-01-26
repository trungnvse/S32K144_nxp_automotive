#ifndef DRIVERS_GPIO_H_
#define DRIVERS_GPIO_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include <stdint.h>
#include "s32k144.h"
/*******************************************************************************
* Define
*******************************************************************************/
typedef enum
{
    Input  = 0U,
    Output = 1U,
} direction_t;

typedef struct
{
    direction_t direction;     /*direction, input/output*/
    uint8_t     logic;         /*default output state, if input, ignore it */
} gpio_config_t;

/**
  * @brief                Write logic of GPIO function
  * GPIO_Type* base       GPIO instant
  * uint8_t pin           pin
  * uint8_t logic         logic - 1/0
  * @return value         None
  */
static inline void GPIO_Write(GPIO_Type* base, uint8_t pin, uint8_t logic)
{
	if(logic)
	    base->PDOR |= (1<<pin);
	else
		base->PDOR &= ~(1<<pin);
}

/**
  * @brief                Write logic of GPIO function
  * GPIO_Type* base       GPIO instant
  * uint8_t pin           pin
  * gpio_config_t* config specific configuration of GPIO
  * @return value         None
  */
void GPIO_Config(GPIO_Type* base, uint8_t pin, gpio_config_t* config);

#endif /* DRIVERS_GPIO_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
