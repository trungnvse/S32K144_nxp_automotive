#ifndef BOOT_INC_STATUS_PROGRAM_H_
#define BOOT_INC_STATUS_PROGRAM_H_
/*******************************************************************************
* Define
*******************************************************************************/
typedef enum Status_program{
	QUEUE_OVERFLOW,
	DATA_INVALID,
	SUCESS,
    ERASE_FAILED,
    PROGRAM_FAILED,
    VERIFY_FAILED
} Status_program_e_t;

#define    address_start_app            0x4000
#define    size_app_sector              16/* or 10 */

#endif /* BOOT_INC_STATUS_PROGRAM_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
