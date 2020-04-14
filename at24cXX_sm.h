/**
* \file
* \version 1.0
* \author bazhen.levkovets
* \date 2020 
* \mail bazhen.info(at)gmail.com
*************************************************************************************
* \copyright	Bazhen Levkovets
* \copyright	Brovary, Kyiv region
* \copyright	Ukraine
*
*
*************************************************************************************
*
* \brief
*
*/

#ifndef at24cXX_SM_H_INCLUDED
#define at24cXX_SM_H_INCLUDED

/*
**************************************************************************
*								INCLUDE FILES
**************************************************************************
*/

	#include "main.h"
	#include "gpio.h"
	#include "usart.h"
	#include "i2c.h"

	#include "stdio.h"
	#include <string.h>

	#include "at24cXX_local_config.h"
	#include "boryviter_local_config.h"

/*
**************************************************************************
*								    DEFINES
**************************************************************************
*/

/*
**************************************************************************
*								   DATA TYPES
**************************************************************************
*/

/*
**************************************************************************
*								GLOBAL VARIABLES
**************************************************************************
*/

/*
**************************************************************************
*									 MACRO'S
**************************************************************************
*/

/*
**************************************************************************
*                              FUNCTION PROTOTYPES
**************************************************************************
*/

void At24cXX_Init (void) ;
HAL_StatusTypeDef  Write_to_EEPROM(uint8_t * _str, uint8_t _size_of_str_u8, uint16_t _eeprom_packet_u16);
HAL_StatusTypeDef Read_from_EEPROM(uint8_t * _str, uint8_t _size_of_str_u8, uint16_t _eeprom_packet_u16);

#endif /* at24cXX_SM_H_INCLUDED */

