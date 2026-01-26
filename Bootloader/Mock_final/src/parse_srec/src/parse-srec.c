/*******************************************************************************
* Include
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse_srec.h"
/*******************************************************************************
* Prototype
*******************************************************************************/
/**
 * @brief                   Check validity of one S-record line
 * @param cout_line         Line number (for tracking purposes)
 * @param line              Pointer to S-record line string
 * @param ptr_status        Pointer to store validation status result
 * @return value            None (result stored in ptr_status)
 *                          OK if line is valid
 *                          ERROR_START if line doesn't start with 'S'
 *                          ERROR_TYPE if record type is invalid
 *                          ERROR_HEXA if contains non-hexadecimal characters
 *                          ERROR_COUNT_BYTE if byte count is incorrect
 *                          ERROR_CHECKSUM if checksum verification fails
 */
static void check_line(uint16_t cout_line, char* line, Status_t_enum* ptr_status);

/**
 * @brief                   Check line count in S5/S6 records
 * @param count_line        Current line number in S-record file
 * @param line              Pointer to S-record line (S5 or S6)
 * @return value            Status of line count validation
 *                          OK if line count matches expected value
 *                          ERROR_COUNT_LINE if line count mismatch
 *                          ERROR_HEXA if address contains invalid hex characters
 */
static Status_t_enum Check_count_line(uint16_t count_line, char* line);

/**
 * @brief                   Count number of characters until carriage return
 * @param rest_line         Pointer to string to count
 * @return value            Number of characters before '\r' terminator
 *                          Returns length of data portion (address + data + checksum)
 */
static uint16_t count_byte(char* rest_line);

/**
 * @brief                   Convert two ASCII hex characters to one decimal byte
 * @param hex               Pointer to pointer of hex string (auto-advanced by 2)
 * @param dec               Pointer to store converted decimal value
 * @return value            Status of conversion
 *                          OK if conversion successful
 *                          ERROR_HEXA if characters are not valid hexadecimal
 */
static Status_t_enum hex_to_dec(char** hex, uint8_t* dec);

/**
 * @brief                   Check record type validity and consistency
 * @param line              Pointer to S-record line string
 * @param count_line        Current line number in S-record file
 * @return value            Status of record type validation
 *                          OK if record type is valid and consistent
 *                          ERROR_TYPE if first line is not S0 or invalid type found
 *                          ERROR_TYPE_CONFLICT if mixing S19/S28/S37 formats
 *                          ERROR_COUNT_LINE if S5/S6 count doesn't match
 */
static Status_t_enum Check_type_record(char* line, uint16_t count_line);
/*******************************************************************************
* Code
*******************************************************************************/
srec_line_t_enum parse_srec(char* ptr_srec, char** ptr_data, char** ptr_address, uint16_t* lenght_address, uint16_t* length_data)
{
	char               record_type       = ptr_srec[1];
	srec_line_t_enum   type_line         = line_data;

	if(ptr_srec != NULL)
	{
		* length_data  = count_byte(ptr_srec) - 6;
	}

	switch (record_type)
	{
		case '1':
			type_line = line_data;
			* ptr_address      = (ptr_srec + 4);
			* ptr_data         = (ptr_srec + 4 + LENGHT_ADDRESS_S19);
			* lenght_address   = LENGHT_ADDRESS_S19;
			* length_data      = * length_data - LENGHT_ADDRESS_S19;
			break;
		case '2':
			type_line = line_data;
			* ptr_address      = (ptr_srec + 4);
			* ptr_data         = (ptr_srec + 4 + LENGHT_ADDRESS_S28);
			* lenght_address   = LENGHT_ADDRESS_S28;
			* length_data      = * length_data - LENGHT_ADDRESS_S28;
			break;
		case '3':
			type_line = line_data;
			* ptr_address      = (ptr_srec + 4);
			* ptr_data         = (ptr_srec + 4 + LENGHT_ADDRESS_S37);
			* lenght_address   = LENGHT_ADDRESS_S37;
			* length_data      = * length_data - LENGHT_ADDRESS_S37;
			break;
		case '7':
			type_line = line_end;
			break;
		case '8':
			type_line = line_end;
			break;
		case '9':
			type_line = line_end;
			break;
		default:
			type_line = line_check;
			break;
	}

	return type_line;
}


/*******************************************************************************
* PROGRAM ->  FILE S-RECORD
* CHECK :
* 1 DÒNG S-RECORD
* | S | TYPE | BYTE COUNT | ADDRESS | DATA                             | CHECKSUM |
*   S     1       13          8000    00180020D58000004381000045810000     55
*******************************************************************************/

Status_t_enum check_srec(char* ptr_srec)
{
	Status_t_enum       status       = OK;
	static     uint16_t cout_line    = 0;

	check_line(cout_line, ptr_srec, &status);
	cout_line++;

	return status;
}

const char* convert_status_to_string(Status_t_enum status)
{
    switch (status)
    {
        case OK:                    return "OK";
        case ERROR_START:           return "ERROR_START";
        case ERROR_TYPE:            return "ERROR_TYPE";
        case ERROR_COUNT_BYTE:      return "ERROR_COUNT_BYTE";
        case ERROR_HEXA:            return "ERROR_HEXA";
        case ERROR_CHECKSUM:        return "ERROR_CHECKSUM";
        case ERROR_COUNT_LINE:      return "ERROR_COUNT_LINE";
        case ERROR_TYPE_CONFLICT:   return "ERROR_TYPE_CONFLICT";
        default:                    return "UNKNOWN_STATUS";
    }
}
/*******************************************************************************
* Static Functions
*******************************************************************************/
static void check_line(uint16_t cout_line, char* line, Status_t_enum* ptr_status)
{
    uint8_t             bytecout       = 0;
    char*               rest_line      = line + 2;
    uint16_t            index          = 0;
    uint8_t             arr_temp[100];
    uint8_t             sum            = 0;
    uint8_t             check_sum      = 0;
    *ptr_status                        = OK;


    if(*line != 'S') /* check start record - CHECK TYPE */
    {
        *ptr_status = ERROR_START;

    }else{
        /* check type record - CHECK TYPE */
        *ptr_status = Check_type_record(line, cout_line);
        if( *ptr_status == OK )
        {
            if(hex_to_dec(&rest_line, &bytecout) == ERROR_HEXA)
            {   /* check hexadecimal  */
                *ptr_status = ERROR_HEXA;

            } else if(count_byte(rest_line) != (bytecout*2))
            {
                *ptr_status = ERROR_COUNT_BYTE;/* check byte count record - CHECK BYTE COUNT  */

            } else{
                rest_line      = &line[2];
                for(index = 0; index < bytecout; index++)
                {
                    if(hex_to_dec(&rest_line, &arr_temp[index]) == ERROR_HEXA)
                    {   /* check hexadecimal  */
                        index = 200;
                        *ptr_status = ERROR_HEXA;

                    }
                    sum += arr_temp[index];
                }

                if( ( *ptr_status == OK) \
                && (hex_to_dec(&rest_line, &check_sum) == ERROR_HEXA) )
                {
                    *ptr_status = ERROR_HEXA; /* check hexadecimal  */

                }


                if((*ptr_status == OK ) && (check_sum != (255-sum)))
                {
                    *ptr_status = ERROR_CHECKSUM;/* check sum record - CHECK SUM */

                }
            }
        }
    }
}

static Status_t_enum Check_type_record(char* line, uint16_t count_line)
{
    uint8_t record_type = *(line+1);
    srec_file_type_t_enum srec_type_current = S19;
    static srec_file_type_t_enum srec_type_before  = S19;
    Status_t_enum relvar = OK;

    if( (count_line == 0) && (record_type != '0') )
    {
        relvar = ERROR_TYPE;

    }

    if(count_line > 0)
    {
        switch (record_type)
        {
    	case '1':
        case '9':
            srec_type_current = S19;
    	    break;
    	case '2':
    	case '8':
    	    srec_type_current = S28;
    		break;
    	case '3':
    	case '7':
    		srec_type_current = S37;
    		break;
    	case '5':
    	case '6':
    	    relvar = Check_count_line(count_line, line);
    	    srec_type_current = srec_type_before;
    	    break;
    	default:
    	    relvar = ERROR_TYPE;

    		break;
    	}

    	if( (count_line > 1) && (srec_type_current != srec_type_before))
        {
            relvar =  ERROR_TYPE_CONFLICT;

        } else{
            srec_type_before = srec_type_current;
        }
    }

    return relvar;
}

static Status_t_enum hex_to_dec(char** hex, uint8_t* dec)
{
    Status_t_enum      relvar      = OK;
    char               character1  = 'A';
    char               character2  = 'B';
    int16_t            temp        = 0;

    character1 = **hex;
    *hex = *hex +1;
    character2 = **hex;
    *hex = *hex + 1;
    temp = convert_8bit(character1,character2);

    if(temp == -1)
    {
        relvar = ERROR_HEXA;
    } else{
        *dec = temp;
    }

    return relvar;
}

static uint16_t count_byte(char* rest_line)
{
    uint16_t index = 0;

    while( rest_line[index] != '\r' )
    {
        index++;
    }

    return index;
}

static Status_t_enum Check_count_line(uint16_t count_line,char* line)
{
    Status_t_enum relvar      = OK;
    uint16_t      count       = 0;
    uint8_t       part1       = 0;
    uint8_t       part2       = 0;
    char*      rest_line   = line + 4;
    static uint16_t count_line_s5_s6 = 0;

    relvar = hex_to_dec(&rest_line, &part1);
    relvar = hex_to_dec(&rest_line, &part2);
    count = part1 << 8 | part2;

    if( count != count_line - 1 - count_line_s5_s6)
    {
        relvar = ERROR_COUNT_LINE;

    }

    count_line_s5_s6++;
    return relvar;
}
/*******************************************************************************
* EOF
*******************************************************************************/
