/*******************************************************************************
* Include
*******************************************************************************/
#include "led_control.h"
/*******************************************************************************
* Global variable
*******************************************************************************/
volatile uint8_t g_red;
volatile uint8_t g_green;
volatile uint8_t g_blue;
/*******************************************************************************
* Prototype
*******************************************************************************/
/**
  * @brief                   change status of led depend on counter
  * uint8_t counter          counter to compare
  * @return value            None
  */
void Led_control_handle(uint8_t counter);
/*******************************************************************************
* CODE
*******************************************************************************/
uint8_t Led_control_init()
{

	uint8_t reval = 0;

	BOARD_InitClock();

	/*Initialize System tick*/
	/*For smooth 8-bit PWM, stick with 256 steps and LOAD = 959 for clean 50 kHz ticks.
	 * T tick = 20us -> T PWM = 5.12ms
	 * */
	reval = SYSTICK_Config(959);

	if(reval == 0)
	{
		/*Initialize led pin*/
		BOARD_InitPins();
	}

	return reval;
}


void Led_control_run(uint8_t _red, uint8_t _green, uint8_t _blue)
{
	Systick_regis_handler(Led_control_handle);
	g_red   = _red;
	g_green = _green;
	g_blue  = _blue;
}

void Led_control_handle(uint8_t counter)
{
	if(g_red > counter)
		BOARD_WritePin(ON, RED_LED);
	else
		BOARD_WritePin(OFF, RED_LED);

	if(g_green > counter)
		BOARD_WritePin(ON, GREEN_LED);
	else
		BOARD_WritePin(OFF, GREEN_LED);

	if(g_blue > counter)
		BOARD_WritePin(ON, BLUE_LED);
	else
		BOARD_WritePin(OFF, BLUE_LED);

}
/*******************************************************************************
* EOF
*******************************************************************************/
