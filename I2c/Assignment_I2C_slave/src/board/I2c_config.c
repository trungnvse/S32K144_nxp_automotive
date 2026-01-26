/*******************************************************************************
* Include
*******************************************************************************/
#include "I2c_config.h"
/*******************************************************************************
* Global variable
*******************************************************************************/
volatile i2c_buffer_t g_i2c_buffer;
volatile uint8_t g_byte_index = 0;
volatile uint8_t *g_buffer_ptr = (volatile uint8_t *)&g_i2c_buffer;

/*******************************************************************************
* Code
*******************************************************************************/
void BOARD_InitI2c()
{
	port_config_t config_port = {.mux = 3, .pullenable = 1, .pullSelect = 1};
	I2c_slave_config_t config_i2c = {.address = 0x32, .interrupt = 1};

	CLOCK_EnableClock(PCC_PORTA_INDEX);

	CLOCK_ChooseSourse(PCC_LPI2C0_INDEX, 3);/*choose FIRC*/
	CLOCK_EnableClock(PCC_LPI2C0_INDEX);

	PORT_Config(IP_PORTA, SDA_I2C, &config_port);
	PORT_Config(IP_PORTA, SCL_I2C, &config_port);

	I2C_Config_slave(&config_i2c);

	NVIC_EnableInterrupt(LPI2C0_Slave_IRQn, 0x30);

}

void LPI2C0_Slave_IRQHandler(void)
{
	uint32_t new_frequency = 0;
	uint32_t timer_value   = 0;
	uint32_t adc_val       = 0;
    uint32_t I2c_receive_status = IP_LPI2C0->SSR;

    /* Check for Start/Address Match */
    if (I2c_receive_status & LPI2C_SSR_AVF_MASK)
    {
    	IP_LPI2C0->SSR |= LPI2C_SSR_AVF_MASK;
    	//BOARD_WritePin(ON, RED_LED);/*debug by eyes hihi*/
    	BOARD_WritePin(ON, PIN_3);/*debug by logic analyzer*/
    }

    /* Check for Receive Data Full (RDF) */
    if (I2c_receive_status & LPI2C_SSR_RDF_MASK)
    {
        uint8_t data = (uint8_t)(IP_LPI2C0->SRDR & LPI2C_SRDR_DATA_MASK);
        if (g_byte_index < sizeof(i2c_buffer_t))
        {
            g_buffer_ptr[g_byte_index++] = data;
        }
    }


    /* Check for Stop Detect (SDF) */
    if (I2c_receive_status & LPI2C_SSR_SDF_MASK)
    {
    	IP_LPI2C0->SSR |= LPI2C_SSR_SDF_MASK;
    	//BOARD_WritePin(OFF, RED_LED);/*debug by eyes hihi*/
    	BOARD_WritePin(OFF, PIN_3);/*debug by logic analyzer*/

        g_byte_index = 0;

        /* Calculate ADC value */
        adc_val = g_i2c_buffer.adc_value;
        if (adc_val <= ADC_MAX)
        {
            new_frequency = FRE_MIN + ((adc_val * (FRE_MAX - FRE_MIN)) / ADC_MAX);
            timer_value = (LPIT_CLOCK / new_frequency) - 1;
            /*we can stop LPIT before reset timer value*/

            IP_LPIT0->TMR[0].TVAL = timer_value;
        }
    }
}
/*******************************************************************************
* EOF
*******************************************************************************/
