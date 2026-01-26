/*******************************************************************************
* Includes
*******************************************************************************/
#include "flash.h"
#include "S32K144_features.h"
#include "interrupt_manager.h"
#include "parse_srec.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
static flash_ssd_config_t flashSSDConfig;
static volatile status_t  flashStatus;

/*******************************************************************************
* Flash Operations
*******************************************************************************/
status_t Flash_Initialize(void)
{
    status_t reval = STATUS_SUCCESS;

    /* Enable Flash interrupt */
    INT_SYS_InstallHandler(FTFC_IRQn, CCIF_Handler, (isr_t*)0);
    INT_SYS_EnableIRQ(FTFC_IRQn);
    INT_SYS_EnableIRQGlobal();

    /* Disable cache */
    MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x3u);
    MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x3u);

    /* Initialize Flash */
    flashStatus = FLASH_DRV_Init(&Flash_InitConfig0, &flashSSDConfig);
    if (STATUS_SUCCESS != flashStatus)
    {
    	reval = STATUS_ERROR;
    }

    /* Register callback only if init OK */
    if (reval == STATUS_SUCCESS)
    {
        flashSSDConfig.CallBack = (flash_callback_t)CCIF_Callback;
    }

    return reval;
}


Status_program_e_t Flash_EraseAppSectors(void)
{
    Status_program_e_t reval = SUCESS;

    uint32_t erase_addr = address_start_app;
    uint32_t total_size = size_app_sector * FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;

    /* Erase each sector (4KB) */
    while ((total_size > 0) && (reval == SUCESS))
    {
        flashStatus = FLASH_DRV_EraseSector(&flashSSDConfig, erase_addr, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);
        if (STATUS_SUCCESS != flashStatus)
        {
            reval = ERASE_FAILED;
        }
        else
        {
            erase_addr += FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
            total_size -= FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
        }
    }

    /* Verify only if erase OK */
    if (reval == SUCESS)
    {
        flashStatus = FLASH_DRV_VerifySection(&flashSSDConfig,  address_start_app, size_app_sector / FTFx_DPHRASE_SIZE, 1);
        if (STATUS_SUCCESS != flashStatus)
        {
            reval = VERIFY_FAILED;
        }
    }

    return reval;
}

Status_program_e_t Flash_WriteBuffer(uint32_t address, uint8_t* buffer)
{
    Status_program_e_t reval    = SUCESS;
    uint32_t           failAddr = 0;

    /* Program 8 bytes to Flash */
    if (STATUS_SUCCESS != FLASH_DRV_Program(&flashSSDConfig, address, 8,  buffer))
    {
    	reval = PROGRAM_FAILED;
    }

    /* Verify only if program OK */
    if (reval == SUCESS)
    {
        if (STATUS_SUCCESS != FLASH_DRV_ProgramCheck(&flashSSDConfig, address, 8,buffer, &failAddr, 1))
        {
        	reval = VERIFY_FAILED;
        }
    }

    return reval;
}


Status_program_e_t Flash_FlushBuffer(uint32_t current_address, uint8_t* write_buffer, uint8_t buffer_index)
{
    while(buffer_index < 8)
    {
        write_buffer[buffer_index++] = 0xFF;
    }

    /*program buffer to Flash */
    return Flash_WriteBuffer(current_address, write_buffer);
}

Status_program_e_t Flash_ProcessSRecordData(char* ptr_data, uint16_t length_data, uint32_t srec_address,
uint8_t* write_buffer,  uint8_t* buffer_index, uint32_t* current_address, bool* buffer_has_data)
{
    Status_program_e_t reval      = SUCESS;
    uint16_t           num_bytes  = length_data / 2;
    uint16_t           i = 0;
    uint8_t            j = 0;

    for (i = 0; (i < num_bytes) && (reval == SUCESS); i++)
    {
        uint8_t data_byte = convert_8bit(ptr_data[i * 2], ptr_data[i * 2 + 1]);

        /* Check discontinuous address → flush buffer */
        if ((*buffer_has_data == true) &&
            (srec_address != (*current_address + *buffer_index)))
        {
            reval = Flash_FlushBuffer(*current_address,  write_buffer, *buffer_index);

            if (reval == SUCESS)
            {
                *buffer_index    = 0;
                *buffer_has_data = false;
            }
        }

        /* Start new buffer */
        if ((reval == SUCESS) && (*buffer_has_data == false))
        {
            *current_address = (srec_address / 8) * 8;
            *buffer_index    = (uint8_t)(srec_address - *current_address);

            for (j = 0; j < *buffer_index; j++)
            {
                write_buffer[j] = 0xFFU;
            }

            *buffer_has_data = true;
        }

        /* Store byte into buffer */
        if (reval == SUCESS)
        {
            write_buffer[(*buffer_index)++] = data_byte;
        }

        /* Buffer full (8 bytes) */
        if ((reval == SUCESS) && (*buffer_index == 8))
        {
            reval = Flash_WriteBuffer(*current_address, write_buffer);

            if (reval == SUCESS)
            {
                *buffer_index    = 0;
                *buffer_has_data = false;
                *current_address += 8;
            }
        }

        srec_address++;
    }

    return reval;
}


/*******************************************************************************
* Interrupt Handlers
*******************************************************************************/

void CCIF_Handler(void)
{
    FTFx_FCNFG &= (~FTFx_FCNFG_CCIE_MASK);
}

START_FUNCTION_DEFINITION_RAMSECTION
void CCIF_Callback(void)
{
    if ((FTFx_FCNFG & FTFx_FCNFG_CCIE_MASK) == 0u)
    {
        FTFx_FCNFG |= FTFx_FCNFG_CCIE_MASK;
    }
}
END_FUNCTION_DEFINITION_RAMSECTION

/*******************************************************************************
* EOF
*******************************************************************************/
