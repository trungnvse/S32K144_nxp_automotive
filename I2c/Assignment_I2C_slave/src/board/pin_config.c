/*******************************************************************************
* Include
*******************************************************************************/
#include "pin_config.h"
/*******************************************************************************
* Code
*******************************************************************************/
void BOARD_InitPins()
{
	gpio_config_t config_gpio = {.direction = Output, .logic = 1U};
	port_config_t config_port = {.mux = 1, .pullenable = 0, .pullSelect = 0};

	CLOCK_EnableClock(PCC_PORTD_INDEX);

	PORT_Config(IP_PORTD, RED_LED, &config_port);
	GPIO_Config(IP_PTD, RED_LED, &config_gpio);

	PORT_Config(IP_PORTD, BLUE_LED, &config_port);
	GPIO_Config(IP_PTD, BLUE_LED, &config_gpio);

	PORT_Config(IP_PORTD, GREEN_LED, &config_port);
	GPIO_Config(IP_PTD, GREEN_LED, &config_gpio);

	PORT_Config(IP_PORTD, PIN_3, &config_port);
	GPIO_Config(IP_PTD, PIN_3, &config_gpio);

	PORT_Config(IP_PORTD, PIN_4, &config_port);
	GPIO_Config(IP_PTD, PIN_4, &config_gpio);
}

void BOARD_WritePin(status_led status, uint8_t pin)
{

	gpio_config_t config_gpio = {.direction = Output, .logic = status};
	GPIO_Write(IP_PTD, pin, config_gpio.logic);
}

void BOARD_ToggerPin(uint8_t pin)
{
	GPIO_Togger(IP_PTD, pin);
}
/*******************************************************************************
* EOF
*******************************************************************************/

