#ifndef QUEUE_INC_QUEUE_H_
#define QUEUE_INC_QUEUE_H_
/*******************************************************************************
* Include
*******************************************************************************/
#include "lpuart1.h"
/*******************************************************************************
* define
*******************************************************************************/
typedef enum overflow_queue{
	OVERFLOW,
	NOT_OVERFLOW,
} overflow_queue_e_t;

/**
  * @brief                              take data from queue
  * overflow_queue_e_t* _overflow_queu  Indicates the status of the queue, overflow or not
  * @return value                       pointer to address of current queue
  */
char* get_queue(overflow_queue_e_t* _overflow_queue);

/**
  * @brief                   initialize queue
  * uint32_t _baud_rate [in] baud rate of UART
  * @return value            None
  */
void init_queue(const uint32_t _baud_rate);

/**
  * @brief                   free a queue, this queue can use to storage another data
  * @return value            None
  */
void completed_process();

/**
  * @brief                   initialize queue
  * uint32_t number_line     number line
  * const char *status       pointer to status string
  * @return value            None
  */
void print_status(uint32_t number_line,const char *status);

/**
  * @brief                   initialize queue
  * uint32_t number_line     number line
  * const char *status       pointer to data string
  * uint16_t length          length of data string
  * @return value            None
  */
void print_data(uint32_t number_line, char* data_string, uint16_t length);

#endif /* QUEUE_INC_QUEUE_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
