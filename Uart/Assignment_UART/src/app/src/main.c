/*******************************************************************************
* Include
*******************************************************************************/
#include "parse_srec.h"
#include "queue.h"
#include "app.h"
#include "lpuart1.h"
/*******************************************************************************
* Prototype
*******************************************************************************/
/**
  * @brief                   program to check and parse S-record through UART
  * @return value            None
  */
Status_program_e_t program();


/*STRUCTURE:
 * ---------------------------------
 *           Application   	       |
 * ---------------------------------
 *     Queue	|   S-rec		   |
 * ---------------------------------
 *            UART				   |
 * ---------------------------------
 *
 * Don't share global variable between layer
 * lower layer call callback function from higher layer(UART call add_element from Queue in interrupt)
 * */
int main()
{
	program(115200);
	return 0;
}

Status_program_e_t program(const uint32_t _baud_rate)
{
	Status_program_e_t relvar           = SUCESS;
    overflow_queue_e_t overflow_queue   = NOT_OVERFLOW;
    srec_line_t_enum   type_line        = line_check;
    Status_t_enum      status_srec_line = OK;

    char*      ptr_srec       = NULL;
    char*      ptr_data       = NULL;
    char*      ptr_address    = NULL;
    uint16_t   lenght_address = 0;
    uint16_t   lenght_data    = 0;

	init_queue(_baud_rate);

	while((type_line != line_end) && (relvar == SUCESS))
	{
    	/* take data from queue */
    	ptr_srec    = get_queue(&overflow_queue);

    	if((ptr_srec != NULL) && (overflow_queue == NOT_OVERFLOW))
    	{
    		static uint32_t line_counter = 0;
    		line_counter++;

    		status_srec_line = check_srec(ptr_srec);
    		if(OK == status_srec_line)
    		{
    			type_line = parse_srec(ptr_srec, &ptr_data, &ptr_address, &lenght_address, &lenght_data);
    			/*S-record line correct*/
    			print_status(line_counter, "<<");
    			if( type_line == line_end)
    			{
    				print_status(line_counter, "Successfully .Finish program.");
    			}
    		}
    		else
    		{
    			/*data invalid - stop program*/
    			relvar = DATA_INVALID;
    			print_status(line_counter, convert_status_to_string(status_srec_line));
    			print_status(line_counter, "Fail .Finish program.");
    		}

    		completed_process();
    	}
    	else if(overflow_queue == OVERFLOW)
    	{
    		/*queue over flow - stop program*/
    		relvar = QUEUE_OVERFLOW;
    	}
    	else
    	{
    		/*queue have no data - wait*/
    	}
	}

	return relvar;
}
/*******************************************************************************
* EOF
*******************************************************************************/
