#ifndef FLASH_H_
#define FLASH_H_
/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "sdk_project_config.h"
#include "status_program.h"
/*******************************************************************************
* API
*******************************************************************************/

/**
 * @brief                  Initialize Flash driver with interrupt and callback
 * @return                 STATUS_SUCCESS if initialization successful, STATUS_ERROR otherwise
 */
status_t Flash_Initialize(void);

/**
 * @brief Erase application sectors before programming
 * @return                 SUCESS if erase successful
 *                         ERASE_FAILED if sector erase failed
 *                         VERIFY_FAILED if blank check failed
 */
Status_program_e_t Flash_EraseAppSectors(void);

/**
 * @brief Write data buffer to Flash memory
 *
 * uint32_t address         address Flash address (must be 8-byte aligned)
 * uint8_t* buffer          buffer Pointer to data buffer (8 bytes)
 * @return                  SUCESS if write successful
 *                          PROGRAM_FAILED if programming failed
 *                          VERIFY_FAILED if verification failed
 */
Status_program_e_t Flash_WriteBuffer(uint32_t address, uint8_t* buffer);

/**
 * @brief                    Flush buffered data to Flash
 * uint32_t                  current_address current_address Flash address to write to
 * uint8_t*                  write_buffer write_buffer Data buffer
 * uint8_t buffer_index      buffer_index Current position in buffer (0-8)
 * @return                   SUCESS if flush successful, error code otherwise
 */
Status_program_e_t Flash_FlushBuffer(uint32_t current_address,
                                     uint8_t* write_buffer,
                                     uint8_t buffer_index);

/**
 * @brief                     Process one S-record data line and buffer data
 * char* ptr_data char*       ptr_dataptr_data Pointer to data string (ASCII hex)
 * uint16_t length_data       length_data Length of data string (number of ASCII characters)
 * uint32_t srec_address      srec_address Starting address from S-record
 * uint8_t* write_buffer      write_buffer Data buffer (8 bytes)
 * uint8_t* buffer_index      buffer_index Pointer to current buffer position
 * uint32_t* current_address  current_address Pointer to current Flash write address
 * bool* buffer_has_data      buffer_has_data Pointer to flag indicating buffer has data
 * @return                    SUCESS if processing successful, error code otherwise
 */
Status_program_e_t Flash_ProcessSRecordData(char* ptr_data,
                                            uint16_t length_data,
                                            uint32_t srec_address,
                                            uint8_t* write_buffer,
                                            uint8_t* buffer_index,
                                            uint32_t* current_address,
                                            bool* buffer_has_data);

/**
 * @brief                      Flash Command Complete Interrupt Handler
 */
void CCIF_Handler(void);

/**
 * @brief Flash Command Complete Callback(must be in RAM)
 */
START_FUNCTION_DECLARATION_RAMSECTION
void CCIF_Callback(void)
END_FUNCTION_DECLARATION_RAMSECTION

#endif /* FLASH_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
