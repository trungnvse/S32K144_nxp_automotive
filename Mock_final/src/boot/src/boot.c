/*******************************************************************************
* Includes
*******************************************************************************/
#include "boot.h"
/*******************************************************************************
* Prototype
*******************************************************************************/

/**
 * @brief                  Set Main Stack Pointer register
 * uint32_t topOfMainStack topOfMainStack Stack pointer value
 */
static void __set_MSP(uint32_t topOfMainStack);

/*******************************************************************************
* Code
*******************************************************************************/
Status_program_e_t Program_SRecord(const uint32_t baud_rate)
{
    Status_program_e_t relvar           = SUCESS;
    overflow_queue_e_t overflow_queue   = NOT_OVERFLOW;
    srec_line_t_enum   type_line        = line_check;
    Status_t_enum      status_srec_line = OK;
    uint32_t           line_counter     = 0;

    char*    ptr_srec       = NULL;
    char*    ptr_data       = NULL;
    char*    ptr_address    = NULL;
    uint16_t length_address = 0;
    uint16_t length_data    = 0;

    uint8_t  write_buffer[8];
    uint8_t  buffer_index    = 0;
    uint32_t current_address = 0;
    uint32_t srec_address    = 0;
    bool     buffer_has_data = false;

    /* Erase sectors */
    relvar = Flash_EraseAppSectors();

    /* Initialize UART queue only if erase OK */
    if (relvar == SUCESS)
    {
        init_queue(baud_rate);
    }

    /* Process S-record lines */
    while ((type_line != line_end) && (relvar == SUCESS))
    {
        ptr_srec = get_queue(&overflow_queue);

        if ((ptr_srec != NULL) && (overflow_queue == NOT_OVERFLOW))
        {
            line_counter++;

            status_srec_line = check_srec(ptr_srec);

            if (status_srec_line == OK)
            {
                type_line = parse_srec(ptr_srec, &ptr_data, &ptr_address, &length_address, &length_data);

                print_status(line_counter, "<<");

                if (type_line == line_data)
                {
                    srec_address = convert_16bit(ptr_address[0],  ptr_address[1], ptr_address[2], ptr_address[3]);

                    relvar = Flash_ProcessSRecordData(ptr_data, length_data, srec_address, write_buffer, &buffer_index,
                                                      &current_address,  &buffer_has_data);
                }
            }
            else
            {
                relvar = DATA_INVALID;
                print_status(line_counter, convert_status_to_string(status_srec_line));
            }

            completed_process();
        }
        else if (overflow_queue == OVERFLOW)
        {
            relvar = QUEUE_OVERFLOW;
        }
        else
        {
            /* wait for more data */
        }
    }

    /* Flush remaining buffered data */
    if ((buffer_has_data == true) && (relvar == SUCESS))
    {
        relvar = Flash_FlushBuffer(current_address, write_buffer, buffer_index);
    }

    if (relvar == SUCESS)
    {
        print_status(line_counter, "Successfully. Finish booting.");
    }

    return relvar;
}


void Jump_To_Application(void)
{
    uint32_t stack_pointer = *(uint32_t*)(address_start_app);      /* SP value */
    uint32_t reset_handler = *(uint32_t*)(address_start_app + 4);  /* PC value */

    /* Disable all interrupts */
    __asm volatile ("cpsid i" : : : "memory");

    /* Set vector table offset */
    S32_SCB->VTOR = (uint32_t)(address_start_app);

    /* Set main stack pointer */
    __set_MSP(stack_pointer);

    /* Thumb mode (Cortex-M requires bit 0 = 1) */
    reset_handler |= 0x01;

    /* Create function pointer and jump to application */
    void (*app_reset)(void) = (void (*)(void))(reset_handler);
    app_reset();

    while(1);
}

/**
 * @brief            Set Main Stack Pointer register
 * uint32_t          topOfMainStack topOfMainStack New stack pointer value
 */
static void __set_MSP(uint32_t topOfMainStack)
{
    __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}

/*******************************************************************************
* EOF
*******************************************************************************/
