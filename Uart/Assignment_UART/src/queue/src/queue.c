/*******************************************************************************
* Include
*******************************************************************************/
#include "queue.h"
/*******************************************************************************
* Global variable
*******************************************************************************/
char     queue[4][256];
volatile uint16_t   index_queue            = 0;
volatile uint16_t   index_element          = 0;
volatile uint16_t   getting_index_queue    = 0;
volatile uint16_t   getting_index_element  = 0;
volatile uint8_t    numbersof_avai_queue   = 0;
volatile overflow_queue_e_t g_overflow_queue = NOT_OVERFLOW;
/*******************************************************************************
* Prototype
*******************************************************************************/
/**
  * @brief                   add character to queue
  * char _element            character to add to queue
  * @return value            None
  */
void add_element(char _element);
/*******************************************************************************
* CODE
*******************************************************************************/
void init_queue(const uint32_t _baud_rate)
{
	init_uart(_baud_rate);
	register_take_data_from_uart(add_element);
}

void add_element(char _element)
{
    if(_element == '\n')
    {
    	queue[index_queue][index_element] = _element;
    	if(index_queue == 3)
		{
			index_queue = 0;
		}else{
			index_queue++;
		}

		index_element = 0;
		numbersof_avai_queue++;
    }else{
    	queue[index_queue][index_element] = _element;
    	index_element++;
    }

    /* check if queue overflow */
    if(numbersof_avai_queue > 4)
    {
    	g_overflow_queue = OVERFLOW;
    }
}

char* get_queue(overflow_queue_e_t* _overflow_queue)
{
	char* current_queue = NULL;

	if(numbersof_avai_queue > 0)
	{
		current_queue = &(queue[getting_index_queue][0]);
		//numbersof_avai_queue--;
		if(getting_index_queue == 3)
		{
			getting_index_queue = 0;
		}else{
			getting_index_queue++;
		}
	}
	*_overflow_queue = g_overflow_queue;

	return current_queue;
}

void print_status(uint32_t number_line,const char *status)
{
	LPUART1_print_number(number_line);
	LPUART1_send_string(" ");
	LPUART1_send_string(status);
	LPUART1_send_string("\n");
}

/*Function to test*/
void print_data(uint32_t number_line, char* data_string, uint16_t length)
{
	LPUART1_print_number(number_line);
	LPUART1_send_string(" ");
	LPUART1_send_string_v2(data_string, length);
	LPUART1_send_string("\n");
}

void completed_process()
{
	numbersof_avai_queue--;
}
/*******************************************************************************
* EOF
*******************************************************************************/
