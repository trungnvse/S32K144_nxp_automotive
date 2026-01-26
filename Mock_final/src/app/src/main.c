/*******************************************************************************
* Includes
*******************************************************************************/
#include "boot.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "S32K144.h"

/*******************************************************************************
* Define
*******************************************************************************/
#define RED_LED_PIN     (15U)
#define BLUE_LED_PIN    (0U)
#define GREEN_LED_PIN   (16U)

#define RED_LED_MASK    (1U << RED_LED_PIN)
#define BLUE_LED_MASK   (1U << BLUE_LED_PIN)
#define GREEN_LED_MASK  (1U << GREEN_LED_PIN)

#define BUTTON_PIN      (12U)
#define BUTTON_MASK     (1U << BUTTON_PIN)

#define BUTTON_PRESSED      (0)
#define BUTTON_NOT_PRESSED  (1)
#define BOOTLOADER_BAUDRATE (9600) /*alway 9600 - if 115200, It will be failed because flash too slow*/

/* Debounce delay */
#define BUTTON_DEBOUNCE_DELAY (50000U)

/*******************************************************************************
* Prototypes
*******************************************************************************/

/**
 * @brief                   Check if boot button is pressed
 * @return value            0 if button pressed (active low)
 *                          1 if button not pressed (pulled high)
 */
static uint8_t is_button_pressed(void);

/**
 * @brief                   Initialize LED GPIOs (PTD0, PTD15, PTD16)
 * @return value            None
 */
static void init_led(void);

/**
 * @brief                   Initialize button GPIO (PTC12) with pull-up
 * @return value            None
 */
static void init_button(void);

/**
 * @brief                   Turn on red LED (turn off others)
 * @return value            None
 */
static void led_red_on(void);

/**
 * @brief                   Turn on blue LED (turn off others)
 * @return value            None
 */
static void led_blue_on(void);

/**
 * @brief                   Turn on green LED (turn off others)
 * @return value            None
 */
static void led_green_on(void);

/**
 * @brief                   Turn off all LEDs
 * @return value            None
 */
static void led_all_off(void);

/**
 * @brief                   Simple delay for button debouncing
 * uint32_t count           Number of loop iterations
 * @return value            None
 */
static void delay(uint32_t count);

/*******************************************************************************
* Main Function
*******************************************************************************/

/*******************************************************************************
* Boot Mode Logic:
* - If button pressed during reset → Enter bootloader mode (flash new firmware)
* - If button not pressed → Jump to application
*
* LED Indicators:
* - Blue LED: Bootloader mode active (receiving firmware)
* - Green LED: Firmware update successful
* - Red LED: Firmware update failed
*******************************************************************************/
int main(void)
{
    Status_program_e_t status = SUCESS;

    init_led();
    init_button();
    led_all_off();

    for(int i = 0; i < 3; i++)
    {
        led_red_on();
        delay(2000000);
        led_all_off();
        delay(2000000);
    }

    delay(1000000);

    /* Check if button is NOT pressed */
    if(is_button_pressed() == BUTTON_NOT_PRESSED)
    {
        Jump_To_Application();
    }
    else
    {
        led_blue_on();

        if(Flash_Initialize() != STATUS_SUCCESS)
        {
            led_red_on();
            while(1)
            {

            }
        }

        status = Program_SRecord(BOOTLOADER_BAUDRATE);

        if(status == SUCESS)
        {
            /* Firmware update successful -  green LED */
            led_green_on();
            delay(1000000);
        }
        else
        {
            /* Firmware update failed -  red LED */
            led_red_on();
            while(1)
            {

            }
        }
    }

    return 0;
}

/*******************************************************************************
* Static function
*******************************************************************************/
static uint8_t is_button_pressed(void)
{
    uint8_t button_state;
    button_state = (PTC->PDIR >> BUTTON_PIN) & 1U;
    uint8_t button_state_confirm = (PTC->PDIR >> BUTTON_PIN) & 1U;

    delay(BUTTON_DEBOUNCE_DELAY);

    if(button_state == 1 && button_state_confirm == 1)
    {
        return BUTTON_PRESSED;
    }

    return BUTTON_NOT_PRESSED;
}

static void led_red_on(void)
{
    PTD->PDOR &= ~RED_LED_MASK;
    PTD->PDOR |= BLUE_LED_MASK;
    PTD->PDOR |= GREEN_LED_MASK;
}


static void led_blue_on(void)
{
    PTD->PDOR |= RED_LED_MASK;
    PTD->PDOR &= ~BLUE_LED_MASK;
    PTD->PDOR |= GREEN_LED_MASK;
}


static void led_green_on(void)
{
    PTD->PDOR |= RED_LED_MASK;
    PTD->PDOR |= BLUE_LED_MASK;
    PTD->PDOR &= ~GREEN_LED_MASK;
}


static void led_all_off(void)
{
    PTD->PDOR |= RED_LED_MASK;
    PTD->PDOR |= BLUE_LED_MASK;
    PTD->PDOR |= GREEN_LED_MASK;
}

static void init_led(void)
{
    PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
    PORTD->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
    PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);
    PORTD->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
    PTD->PDDR |= RED_LED_MASK;
    PTD->PDDR |= BLUE_LED_MASK;
    PTD->PDDR |= GREEN_LED_MASK;
    PTD->PDOR |= RED_LED_MASK;
    PTD->PDOR |= BLUE_LED_MASK;
    PTD->PDOR |= GREEN_LED_MASK;
}

static void init_button(void)
{
    PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC(1);
    PORTC->PCR[BUTTON_PIN] |= PORT_PCR_MUX(1);
    PORTC->PCR[BUTTON_PIN] |= PORT_PCR_PE_MASK;
    PORTC->PCR[BUTTON_PIN] |= PORT_PCR_PS_MASK;
    PTC->PDDR &= ~BUTTON_MASK;
}

static void delay(uint32_t count)
{
    for(volatile uint32_t i = 0; i < count; i++)
    {

    }
}
/*******************************************************************************
* EOF
*******************************************************************************/
