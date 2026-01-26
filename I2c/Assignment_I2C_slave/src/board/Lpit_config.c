/*******************************************************************************
* Include
*******************************************************************************/
#include "Lpit_config.h"
/*******************************************************************************
* Global variable
*******************************************************************************/
uint8_t flat_change = 0;/*use to check in while loop in main*/
/*******************************************************************************
* Code
*******************************************************************************/
void BOARD_InitLpit()
{
	Lpit_config_t config_lpit_c0 = {.channel = 0, .interrupt = 1, .val_counter = (LPIT_CLOCK / FRE_MIN)};
	Lpit_config_t config_lpit_c1 = {.channel = 1, .interrupt = 1, .val_counter = (LPIT_CLOCK * FRE_CHANGE_ADC)};

	CLOCK_ChooseSourse(PCC_LPIT_INDEX, 3);/*FIRC*/
	CLOCK_EnableClock(PCC_LPIT_INDEX);

	LPIT0_Config(&config_lpit_c0, 1);
	LPIT0_Config(&config_lpit_c1, 2);

	NVIC_EnableInterrupt(LPIT0_Ch0_IRQn, 0x50);
	NVIC_EnableInterrupt(LPIT0_Ch1_IRQn, 0x30);
}

/**
  * @brief                   toggle pin with frequency LPIT
  * @return value            None
  */
void LPIT0_Ch0_IRQHandler(void)
{
	LPIT0_Ch0_InterruptFlag();/*clear interrupt flat*/

#if TEST_LOGIC_ANALYZER
	BOARD_WritePin(ON, PIN_4);
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    BOARD_WritePin(OFF, PIN_4);
#endif

#if TEST_EYES
	BOARD_ToggerPin(GREEN_LED);/*To test frequency of LPIT*/
#endif
}

/**
  * @brief                   turn on flat in interrupt of LPIT
  * @return value            None
  */
void LPIT0_Ch1_IRQHandler(void)
{
	LPIT0_Ch1_InterruptFlag();/*clear interrupt flat*/
	flat_change = 1;
}
/*******************************************************************************
* EOF
*******************************************************************************/
