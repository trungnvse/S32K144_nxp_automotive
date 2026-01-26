/*******************************************************************************
* Include
*******************************************************************************/
#include "pin_config.h"
/*******************************************************************************
* Code
*******************************************************************************/
void BOARD_InitPins()
{
	gpio_config_t config_gpio = {.direction = Output, .logic = 0U};
	port_config_t config_port = {.mux = 1, .pullenable = 0, .pullSelect = 0};

	CLOCK_EnableClock(PCC_PORTD);

	PORT_Config(PORTD, RED_LED, &config_port);
	GPIO_Config(GPIOD, RED_LED, &config_gpio);

	PORT_Config(PORTD, BLUE_LED, &config_port);
	GPIO_Config(GPIOD, BLUE_LED, &config_gpio);

	PORT_Config(PORTD, GREEN_LED, &config_port);
	GPIO_Config(GPIOD, GREEN_LED, &config_gpio);
}

void BOARD_WritePin(status_led status, uint8_t pin)
{

	gpio_config_t config_gpio = {.direction = Output, .logic = status};
	GPIO_Write(GPIOD, pin, config_gpio.logic);
}


/*******************************************************************************
* EOF
*******************************************************************************/
