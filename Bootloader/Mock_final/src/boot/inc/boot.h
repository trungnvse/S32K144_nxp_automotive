#ifndef BOOT_INC_BOOT_H_
#define BOOT_INC_BOOT_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "parse_srec.h"
#include "queue.h"
#include "flash.h"
#include "status_program.h"
/*******************************************************************************
* Define
*******************************************************************************/

typedef void( *callback_t)(void);

/*******************************************************************************
* API
*******************************************************************************/
/**
 * @brief                     Process and write S-record data to Flash
 * const uint32_t baud_rate   baud_rate UART baud rate for receiving S-record file
 * @return                    Status of programming operation
 */
Status_program_e_t Program_SRecord(const uint32_t baud_rate);

/**
 * @brief                     Jump from bootloader to application
 * @return                    None
 */
void Jump_To_Application(void);


#endif /* BOOT_INC_BOOT_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
